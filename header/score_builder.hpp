//////////////////////////////////////////////////
//
//    score_builder.hpp
//    解析内容をもとに譜面情報を作成する
//

#ifndef score_builder_hpp
#define score_builder_hpp

#include "../header/global.hpp"

using namespace std;

namespace retro_sound
{
    class score_builder
    {
    private:
        int length = 4;
        int octave = 4;
        int volume = 100;

        int key[7] = {
            half::natural,
            half::natural,
            half::natural,
            half::natural,
            half::natural,
            half::natural,
            half::natural
        };

        rational position = { 0, 4 };

        // 音色
        double (*sound)(double) = wave_square_4;

        // 音符やテンポの変化
               queue<note>          score;
        static vector<tempo_change> change;

        // vector に追加せずに保留している音符
        note note_hold= { position, { 1, length }, 0, 0, 0, 0, 0, sound };
        bool note_holding = false;

        void add_note  (smatch submathces);
        void add_rest  (smatch submathces);

        void set_octave(smatch submatches);
        void set_length(smatch submatches);
        void set_volume(smatch submatches);
        void set_sound (smatch submatches);
        void set_tempo (smatch submatches);
        void set_key   (smatch submatches);

    public:
        static queue<tempo_change> get_tempo_change();
        queue<note> convert(queue<string> note_str);
    };
}

#endif