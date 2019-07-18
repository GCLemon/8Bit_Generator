#include "../header/global.hpp"
#include "../header/text_reader.hpp"

using namespace retro_sound;

text_reader::text_reader(string path)
{
    reader = ifstream(path);

    if(reader.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

map<TRACK, queue<string>> text_reader::read()
{
    // 分断した文字列を格納する辞書型
    map<TRACK, queue<string>> split_string;
    split_string.insert(make_pair(TRACK::A, queue<string>()));
    split_string.insert(make_pair(TRACK::B, queue<string>()));
    split_string.insert(make_pair(TRACK::C, queue<string>()));
    split_string.insert(make_pair(TRACK::D, queue<string>()));

    // トークンを検出するための正規表現
    const regex token(t_str +"|"+ n_str +"|"+ o_str +"|"+ r_str +"|"+ l_str +"|"+ v_str
                      +"|"+ at_i_str +"|"+ at_m_str);

    // ファイルから読み取った行
    string read_line = "";

    // 現在のトラック
    TRACK current_track = TRACK::A;

    // 読み取った行それぞれについて処理
    while(getline(reader, read_line))
    {
        // 文字列の先頭・末尾を取得
        auto b = begin(read_line);
        auto e = end(read_line);

        // 検出したトークンを押し込む
        for(sregex_iterator i(b, e, token), end; i != end; ++i)
        {
            string token_str = (*i).str();
            if(regex_match(token_str, regex(t_str)))
                switch(token_str[0])
                {
                    case 'A': current_track = TRACK::A; break;
                    case 'B': current_track = TRACK::B; break;
                    case 'C': current_track = TRACK::C; break;
                    case 'D': current_track = TRACK::D; break;
                }
            else
                split_string.at(current_track).push(token_str);
        }
    }

    // 分断された文字列が4つのキューになって戻される
    return split_string;
}