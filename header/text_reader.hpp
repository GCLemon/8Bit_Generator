//////////////////////////////////////////////////
//
//    text_reader.hpp
//    読み込んだ MML ソースコードの解析を行う
//

#ifndef text_reader_hpp
#define text_reader_hpp

#include "../header/global.hpp"

using namespace std;

namespace retro_sound
{
    class text_reader
    {
    private:
        string final_code;

    public:
        text_reader(string final_code);
        map<TRACK, queue<string>> read();
    };
}

#endif