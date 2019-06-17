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
    string n_str = "([a-g])([+,-,^,v]*)(([+,-]?[0-9]+)*)([/,_,.]*)(:([+,-])?([0-9]+))?";
    string r_str = "r(([+,-]?[0-9]+)*)([/,_,.]*)";
    string o_str = "[<,>]|o([0-9]+)";
    string l_str = "l([0-9]+)";
    string v_str = "v([0-9]+)";

    // トークンを検出する正規表現オブジェクト
    regex n_re(n_str);
    regex r_re(r_str);
    regex o_re(o_str);
    regex l_re(l_str);
    regex v_re(v_str);
    regex token_regex(n_str + "|" + r_str + "|" + o_str + "|" + l_str + "|" + v_str);

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

            // 検出したトークンが休符を表していた場合
            if(regex_match(token_str, submatches, r_re)) add_rest(submatches);
            
            // 検出したトークンが音高を表していた場合
            if(regex_match(token_str, submatches, o_re)) set_octave(submatches);

            // 検出したトークンが音長を表していた場合
            if(regex_match(token_str, submatches, l_re)) set_length(submatches);

            // 検出したトークンが音量を表していた場合
            if(regex_match(token_str, submatches, v_re)) set_volume(submatches);
        }
    }
}

void text_reader::add_note(smatch submatches)
{
    // 音長
    rational length = { 1, default_length };

    // 音符を作成する
    note note = { position, length, default_octave * 12, default_volume };

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
        }
    }

    // 音高を変更する記号があれば
    if(submatches[2].str() != "")
    {
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
    {
        // 音長を0にする
        length = { 0, 4 };

        // マッチした部分を抜き出す
        string formula = submatches[3].str();

        string s = "";
        bool plus = true;

        // マッチした部分のそれぞれの文字に対して処理
        for(char c : formula)
        {
            switch(c)
            {
                // +だった場合
                case '+':
                    // 音長を変更する
                    length += { plus ? 1 : -1, stoi(s) };
                    plus = true;
                    s = "";
                    break;

                // -だった場合
                case '-':
                    // 音長を変更する
                    length += { plus ? 1 : -1, stoi(s) };
                    plus = false;
                    s = "";
                    break;

                // 数字だった場合,文字列に数字を加える
                default: s += c;
            }
        }

        // 最後に音長を変更する
        length += { plus ? 1 : -1, stoi(s) };
    }

    // 音長を変更する記号があれば
    if(submatches[5].str() != "")
    {
        // 音長にあたる文字それぞれに対して処理
        for(char c : submatches[5].str())
        {
            switch(c)
            {
                case '_': length *= 2; break;
                case '/': length /= 2; break;
                case '.': length *= { 3, 2 }; break;
            }
        }
    }

    // 音量を変更する記号があれば
    if(submatches[6].str() != "")
    {
        switch(submatches[7].str()[0])
        {
            case '+': note.volume += stoi(submatches[8].str()); break;
            case '-': note.volume -= stoi(submatches[8].str()); break;
            default : note.volume  = stoi(submatches[8].str()); break;
        }
    }

    // 指定された音長だけ音符の位置を進める
    position += length;
    note.length = length;

    // 音符の内容を標準出力に表示
    std::cout
        << "音高 : " << note.scale
        << "\t音長 : " << length.to_double()
        << std::endl;

    // 音符を楽譜オブジェクトに格納する
    raw_score.square_a.push_back(note);
}

void text_reader::add_rest(smatch submatches)
{
    // 音長
    rational length = { 1, default_length };

    // 休符を作成する
    note note = { position, length, 0, 0 };

    // 音長を変更する記号があれば
    if(submatches[1].str() != "")
    {
        // 検出した文字列の1つ目のサブマッチの1文字目が+ないし-だった場合
        if(submatches[1].str()[0] == '+' || submatches[1].str()[0] == '-')
        {
            // エラーメッセージを出力し,プログラムを終了させる
            cerr << "cannot use sharp or flat with rest" << endl;
            exit(-1);
        }

        // 音長を0にする
        length = { 0, 4 };

        // マッチした部分を抜き出す
        string formula = submatches[1].str();

        string s = "";
        bool plus = true;

        // マッチした部分のそれぞれの文字に対して処理
        for(char c : formula)
        {
            switch(c)
            {
                // +だった場合
                case '+':
                    // 音長を変更する
                    length += { plus ? 1 : -1, stoi(s) };
                    plus = true;
                    s = "";
                    break;

                // -だった場合
                case '-':
                    // 音長を変更する
                    length += { plus ? 1 : -1, stoi(s) };
                    plus = false;
                    s = "";
                    break;

                // 数字だった場合,文字列に数字を加える
                default: s += c;
            }
        }

        // 最後に音長を変更する
        length += { plus ? 1 : -1, stoi(s) };
    }

    // 音長を変更する記号があれば
    if(submatches[3].str() != "")
    {
        // 音長にあたる文字それぞれに対して処理
        for(char c : submatches[3].str())
        {
            switch(c)
            {
                case '_': length *= 2; break;
                case '/': length /= 2; break;
                case '.': length *= { 3, 2 }; break;
            }
        }
    }

    // 指定された音長だけ音符の位置を進める
    position += length;
    note.length = length;

    // 音符の内容を標準出力に表示
    std::cout
        << "音高 : " << note.scale
        << "\t音長 : " << length.to_double()
        << std::endl;

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

void text_reader::set_length(smatch submatches)
{
    // 指定された音長を設定
    default_length = stoi(submatches[1].str());
}

void text_reader::set_volume(smatch submatches)
{
    // 指定された音量を設定
    default_volume = stoi(submatches[1].str());
}

score text_reader::get_score() { return raw_score; }