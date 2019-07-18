#include "../header/wave_writer.hpp"

using namespace retro_sound;

void wave_writer::write_head()
{
    writer.seekp(0);

    // RIFFヘッダ
    char riff[] = { 'R', 'I', 'F', 'F' };
    writer.write(riff, 4);

    // ファイルサイズ
    point_max += 36;
    writer.write((char*)&point_max, 4);

    // WAVEヘッダ
    char wave[] = { 'W', 'A', 'V', 'E' };
    writer.write(wave, 4);

    // fmtヘッダ
    char fmt[] = { 'f', 'm', 't', ' ' };
    writer.write(fmt, 4);

    // fmtチャンクのサイズ
    uint chank_size = 16;
    writer.write((char*)&chank_size, 4);

    // フォーマットPCM
    short sh = 1;
    writer.write((char*)&sh, 2);

    // チャンネル数
    sh = 1;
    writer.write((char*)&sh, 2);

    // サンプリング周波数
    int i = 44100;
    writer.write((char*)&i, 4);

    // ビットレート
    i = 44100;
    writer.write((char*)&i, 4);

    // ブロックサイズ
    sh = 1;
    writer.write((char*)&sh, 2);

    // サンプルサイズ
    sh = 8;
    writer.write((char*)&sh, 2);

    // dataヘッダ
    char data[] = { 'd', 'a', 't', 'a' };
    writer.write(data, 4);

    // 波データのサイズ
    point_max -= 36;
    writer.write((char*)&point_max, 4);
}