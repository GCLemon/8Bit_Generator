#include "../header/text_reader.hpp"
#include "../header/score_builder.hpp"
#include "../header/wave_writer.hpp"

using namespace retro_sound;

int main()
{
    text_reader reader("test.mml");
    wave_writer writer("test.wav");
    
    auto score_str = reader.read();

    auto score_a = score_builder().convert(score_str.at(TRACK::A));
    auto score_b = score_builder().convert(score_str.at(TRACK::B));
    auto score_c = score_builder().convert(score_str.at(TRACK::C));
    auto score_d = score_builder().convert(score_str.at(TRACK::D));
    auto tempo_change = score_builder::get_tempo_change();

    writer.write_wave(score_a, tempo_change);
    writer.write_wave(score_b, tempo_change);
    writer.write_wave(score_c, tempo_change);
    writer.write_wave(score_d, tempo_change);
    writer.write_head();
}