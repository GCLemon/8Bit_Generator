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
    string line;
    while(getline(reader, line)) code += line;
}

void preprocessor::expand_macro()
{
    regex macro("(\\\\.+)\\s?=\\s?\"(.+)\"");
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

    cout << code << endl;
}

void preprocessor::detect_error()
{

}

string preprocessor::get_final_code()
{
    return code;
}