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

score text_reader::read()
{
    // 読み込んだ行を格納する
    string read_line = "";

    regex n_re("([a-g,r])([+,-,^,v]*)([0-9]*)");
    regex o_re("[<,>]|o([0-9])");
    regex token_re("[a-g,r][+,-,^,v]*[0-9]*|[<,>]|o[0-9]");

    // 楽譜オブジェクト
    vector<note> score;

    int d_length = 4; // デフォルトの音長
    int d_octave = 4; // デフォルトのオクターブ

    // テキストファイルの各行について処理
    while(getline(reader, read_line))
    {
        // イテレータの設定
        auto bg = begin(read_line);
        auto en = end(read_line);
        sregex_iterator it(bg, en, token_re), end;

        // token_reに指定した正規表現に
        // マッチするものすべてに対して処理
        for(; it != end; ++it)
        {
            // 文字列の取得
            string token = (*it).str();

            // サブマッチの結果
            smatch submatches;

            // 検出したトークンが音符だったら
            if(regex_match(token, submatches, n_re))
            {
                // 音符の構造体を作成 
                note note { { 4, d_length }, d_octave * 12, true };

                cout << submatches[0].str() << endl;

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

                // 半音にあたるものがあれば
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

                // 音長にあたるものがあれば
                if(submatches[3].str() != "")
                {
                    // 指定された音長だけ音符の位置を進める
                    note.length = { 4, stoi(submatches[3].str()) };
                }

                // 音符の内容を標準出力に表示
                cout << "音高 : " << note.scale << "\t音長 : " << note.length.to_double() << endl;

                // 音符を楽譜オブジェクトに格納する
                score.push_back(note);
            }

            // 検出したトークンが音高関係のものだった場合
            else if(regex_match(token, submatches, o_re))
            {
                switch(submatches[0].str()[0])
                {
                    // 大なり記号ならばオクターブを上げる
                    case '<' : ++d_octave; break;

                    // 小なり記号ならばオクターブを下げる
                    case '>' : --d_octave; break;

                    // oならば指定されたオクターブに設定
                    case 'o' : 
                        if(submatches[1].str() != "")
                        {
                            d_octave = stoi(submatches[1].str());
                        }
                }
            }
        }
    }

    // 最後に楽譜の構造体を返す
    return { score };
}