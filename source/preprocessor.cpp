#include "../header/preprocessor.hpp"

using namespace retro_sound;

preprocessor::preprocessor(string path)
{
    reader = ifstream(path);

    if(reader.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

preprocessor::~preprocessor()
{
    reader.close();
}

void preprocessor::read_file_all()
{
    istreambuf_iterator<char> it(reader);
    istreambuf_iterator<char> end;
    code = string(it, end);
    code += "\n";
}

void preprocessor::expand_macro()
{
    regex macro("\\s*(\\\\.+)\\s*=\\s*\"(.+)\"\n");
    for(sregex_iterator i(begin(code), end(code), macro), end; i != end; ++i)
    {
        // マクロのキーと値を取得
        string macro_str = (*i)[0].str();
        string macro_key = (*i)[1].str();
        string macro_val = (*i)[2].str();

        // マクロの重複を検出
        if(macros.count(macro_key))
        {
            cerr << "Redefinition : " << macro_key << endl;
            exit(-1);
        }

        // 読み込み済みマクロの登録
        macros[macro_key] = macro_val;
        macro_keys.push_back(macro_key);
    }

    // マクロ部分の削除
    code = regex_replace(code, macro, "");

    bool replace_occur = true;
    while(replace_occur)
    {
        replace_occur = false;

        for(string macro_key : macro_keys)

            // キーが見つかった場合はすぐに置換する
            if(code.find(macro_key) != string::npos)
            {
                replace_occur = true;

                size_t pos = code.find(macro_key);
                while (pos != string::npos)
                {
                    code = code.replace(pos, macro_key.length(), macros[macro_key]);
                    pos = code.find(macro_key);
                }
            }
    }
}

void preprocessor::detect_error()
{
    // トークンを検出するための正規表現
    const regex token(at_k_str +"|"+ at_i_str +"|"+ at_m_str +"|"+
        t_str +"|"+ n_str +"|"+ o_str +"|"+ r_str +"|"+ l_str +"|"+ v_str);

    const regex word(at_k_str +"|"+ at_i_str +"|"+ at_m_str +"|"+
        t_str +"|"+ n_str +"|"+ o_str +"|"+ r_str +"|"+ l_str +"|"+ v_str + "|\\S+");

    auto b = begin(code);
    auto e = end(code);

    for(sregex_iterator i(b, e, word), end; i != end; ++i)
    {
        string word_str = (*i).str();

        if(!regex_match(word_str, token))
        {
            cerr << "Error occured near \"" << word_str << "\"." << endl;
            exit(-1);
        }
    }
}

string preprocessor::get_final_code()
{
    return code;
}