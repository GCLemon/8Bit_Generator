#include "../header/8bit.hpp"

text_reader::text_reader(string path)
{
    // インスタンスを代入
    reader = ifstream(path);

    // ファイルを開くことに失敗した場合は
    // プログラムを終了させる
    if(reader.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

void text_reader::read()
{
    // 読み込んだ行を格納する
    string read_line = "";

    // 音符に関する正規表現
    string n_str = "([a-g,r])([+,-,^,v]*)([0-9]*)";
    string o_str = "[<,>]|o([0-9])";

    // トークンを検出する正規表現オブジェクト
    regex n_re(n_str);
    regex o_re(o_str);
    regex token_regex(n_str + "|" + o_str);

    // テキストファイルの各行について処理
    while(getline(reader, read_line))
    {
        // 文字列の先頭と終端を取得
        auto bg = begin(read_line), en = end(read_line);

        // tokenにて指定された正規表現にマッチするもの全てに対して処理
        for(sregex_iterator i(bg, en, token_regex), end; i != end; ++i)
        {
            // マッチした文字列を取得
            string token_str = (*i).str();

            // サブマッチの結果を格納する
            smatch submatches;

            // 検出したトークンが音符を表していた場合
            if(regex_match(token_str, submatches, n_re)) add_note(submatches);
            
            // 検出したトークンが音符を表していた場合
            if(regex_match(token_str, submatches, o_re)) set_octave(submatches);
        }
    }
}

void text_reader::add_note(smatch submatches)
{
    // 音長
    rational length = { 1, default_length };

    // 音符を作成する
    note note = { position, length, default_octave * 12, true };

    // 音名にあたるものがあれば
    if(submatches[1].str() != "")
    {
        switch(submatches[1].str()[0])
        {
            // 文字が音符だった場合
            case 'a': note.scale += a; break;
            case 'b': note.scale += b; break;
            case 'c': note.scale += c; break;
            case 'd': note.scale += d; break;
            case 'e': note.scale += e; break;
            case 'f': note.scale += f; break;
            case 'g': note.scale += g; break;

            // 文字が休符だった場合
            case 'r': note.play = false; break;
        }
    }

    // 音高を変更する記号があれば
    if(submatches[2].str() != "")
    {
        // 休符に半音記号はつかない
        if(submatches[1].str()[0] == 'r')
        {
            cerr << "cannot use sharp or flat with rest" << endl;
            exit(-1);
        }

        // 半音にあたる文字それぞれに対して処理
        for(char c : submatches[2].str())
        {
            switch(c)
            {
                case '+': ++note.scale;     break;
                case '-': --note.scale;     break;
                case '^': note.scale += 12; break;
                case 'v': note.scale -= 12; break;
            }
        }
    }

    // 音長を変更する記号があれば
    if(submatches[3].str() != "")

        // 音長を指定する
        length = { 1, stoi(submatches[3].str()) };

    // 指定された音長だけ音符の位置を進める
    position += length;
    note.length = length;

    // 音符の内容を標準出力に表示
    cout << "音高 : " << note.scale << "\t音長 : " << length.to_double() << endl;

    // 音符を楽譜オブジェクトに格納する
    raw_score.square_a.push_back(note);
}

void text_reader::set_octave(smatch submatches)
{
    // 検出したトークンの1文字目が
    switch(submatches[0].str()[0])
    {
        // 大なり記号ならばオクターブを上げる
        case '<' : ++default_octave; break;

        // 小なり記号ならばオクターブを下げる
        case '>' : --default_octave; break;

        // oならば指定されたオクターブに設定
        case 'o' : 
            if(submatches[1].str() != "")
                default_octave = stoi(submatches[1].str());
    }
}

score text_reader::get_score() { return raw_score; }