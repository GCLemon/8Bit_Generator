//////////////////////////////////////////////////
//
//    wave_writer.hpp
//    作成した楽譜情報をもとに WAV ファイルを作成する
//

#ifndef wave_writer_hpp
#define wave_writer_hpp

#include "../header/global.hpp"

using namespace std;

typedef unsigned int  uint;
typedef unsigned char ubyte;

namespace retro_sound
{
    class wave_writer
    {
    private:
        double tempo = 120;

        static uint point_max;

        ofstream writer;

        string path;

    public:
        wave_writer(string path);
        void write_wave(queue<note> score, queue<tempo_change> change);
        void write_head();
        ~wave_writer();
    };
}

#endif