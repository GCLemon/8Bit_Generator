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
    regex macro_def ("\\s*\\\\([^\\{,\\}]+)\\s*(\\{(.+)\\})?\\s*=\\s*\"(.+)\"\n");
    for(sregex_iterator i(begin(code), end(code), macro_def), end; i != end; ++i)
    {
        // マクロのキーと値を取得
        string macro_key = (*i)[1].str();
        string macro_val = (*i)[3].str();
        string macro_arg = (*i)[4].str();

        // マクロの重複を検出
        for(macro m : macros)
            if(m.key == macro_key)
            {
                cerr << "Redefinition : " << macro_key << endl;
                exit(-1);
            }

        // 読み込み済みマクロの登録
        macros.push_back({macro_key, macro_arg, macro_val});
    }

    // マクロ部分の削除
    code = regex_replace(code, macro_def, "");

    bool replace_occur = true;

    while(replace_occur)
    {
        replace_occur = false;

        for(macro m : macros)
        {
            // 引数ありマクロの処理
            if(m.arg != "")
            {
                regex macro_call("\\s*\\\\" + m.key + "\\s*\\{([^\\{\\}]+)\\}");
                for(sregex_iterator i(begin(code), end(code), macro_call), end; i != end; ++i)
                {
                    replace_occur = true;

                    // マクロの引数を取得
                    string macro_arg = (*i)[1].str();
                    string macro_val = m.val;

                    // マクロ引数の置換
                    if(macro_arg != "")
                    {
                        size_t pos = macro_val.find(m.arg);
                        while (pos != string::npos)
                        {
                            macro_val = macro_val.replace(pos, m.arg.length(), macro_arg);
                            pos = macro_val.find(m.arg);
                        }
                    }

                    code = code.replace((*i).position(), (*i).length(), macro_val);
                }
            }
            
            // 引数なしマクロの処理
            else
            {
                regex macro_call("\\s*\\\\" + m.key);
                for(sregex_iterator i(begin(code), end(code), macro_call), end; i != end; ++i)
                {
                    replace_occur = true;
                    code = code.replace((*i).position(), (*i).length(), m.val);
                }
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