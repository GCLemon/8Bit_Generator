//////////////////////////////////////////////////
//
//    preprocessor.hpp
//    MMLソースコードのマクロ展開やエラー検出を行う
//

#ifndef preprocessor_hpp
#define preprocessor_hpp

#include "../header/global.hpp"

namespace retro_sound
{
    struct macro
    {
        string key;
        string val;
        string arg;
    };

    class preprocessor
    {
    private:
        ifstream reader;
        string code;
        vector<macro> macros;

    public:
        preprocessor(string path);
        ~preprocessor();
        void read_file_all();
        void detect_error();
        void expand_macro();
        string get_final_code();
    };
}

#endif