#include "../header/preprocessor.hpp"
#include "../header/text_reader.hpp"
#include "../header/score_builder.hpp"
#include "../header/wave_writer.hpp"
#include "../header/global.hpp"

using namespace retro_sound;

void halt(string message)
{
    cout << message << endl;
    exit(-1);
}

int main(int argc, char** argv)
{
    regex format_i(".+\\.mml");
    regex format_o(".+\\.wav");

    if(argc <= 1)
        halt("以下のように入力してください.\n\n./8bit [-o <出力ファイル>] <入力ファイル>\n");

    string file_i = "";
    string file_o = "";
    
    if(strcmp(argv[1], "-o") == 0)
    {
        if(argc <= 3)
            halt("以下のように入力してください.\n\n./8bit [-o <出力ファイル>] <入力ファイル>\n");

        if(!regex_match(argv[2], format_o))
            halt("出力ファイルのフォーマットが正しくありません.\n");

        if(!regex_match(argv[3], format_i))
            halt("入力ファイルのフォーマットが正しくありません.\n");

        file_i = argv[3];
        file_o = argv[2];
    }
    else
    {
        if(!regex_match(argv[1], format_i))
            halt("入力ファイルのフォーマットが正しくありません.\n");

        file_i = argv[1];
        file_o = argv[1];
        int l = file_i.length();
        file_o.replace(l - 4, 4, ".wav");
    }

    create_random();
    
    preprocessor processor(file_i);
    processor.read_file_all();
    processor.expand_macro();
    processor.detect_error();

    text_reader reader(processor.get_final_code());
    wave_writer writer(file_o);
    
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