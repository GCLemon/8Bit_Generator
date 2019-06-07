#include "../header/8bit.hpp"

wave_writer::wave_writer(string path)
{
    // インスタンスを代入
    writer = ofstream(path, ios::binary);

    // ファイルを開くことに失敗した場合は
    // プログラムを終了させる
    if(writer.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

// ファイルポインタが指定された位置を超えたか
#define isover(point) (point) * tempo / 2646000.0 > (position + n.length).to_double()

void wave_writer::write(score score)
{
    writer.seekp(44);

    double   tempo = 120;
    rational position = { 0, 1 };

    uint  file_point = 0;
    int   note_count  = 0;
    int   octave = 4;

    while(true)
    {
        // ファイルに書き込む値を取得
        note n = score.square_a[note_count];
        double f = n.play ? get_freq(n.scale) : 0;
        ubyte v = 5000 * square_4(file_point / 44100.0 * f);

        // 音符の末端の約17ms前に差し掛かったら
        // 音符を区切る
        if(isover(file_point + 256)) v = (ubyte)5000;

        // ファイルに書き込み
        writer.write((char*)&v, 1);

        // ファイルポインタをインクリメント
        ++file_point;

        // 現在のファイルポインタのカウンタから拍子を導出した時
        // 音符の末端を過ぎていたら
        if(isover(file_point))
        {
            ++note_count;
            position += n.length;
            if(note_count >= score.square_a.size())
            {
                break;
            }
        }
    }

    writer.seekp(0);

    // RIFFヘッダ
    char riff[] = { 'R', 'I', 'F', 'F' };
    writer.write(riff, 4);

    // ファイルサイズ
    file_point += 36;
    writer.write((char*)&file_point, 4);

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
    file_point -= 36;
    writer.write((char*)&file_point, 4);

    // ファイルを閉じる
    writer.close();
}