#include "../header/8bit.hpp"

wave_writer::wave_writer(string path)
{
    // インスタンスを代入
    writer = ofstream(path, ios::binary);
    reader = ifstream(path, ios::binary);

    // ファイルを開くことに失敗した場合は
    // プログラムを終了させる
    if(writer.fail() || reader.fail())
    {
        cerr << "File open failed." << endl;
        exit(-1);
    }
}

void wave_writer::write(score score)
{
    // 楽譜をセットする
    raw_score = score;

    write_wave();   // 波データを書き込む
    write_header(); // ファイルヘッダを書き込む
}

void wave_writer::write_header()
{
    writer.seekp(0);

    uint filesize = max(max(file_point_a, file_point_b), file_point_c);

    // RIFFヘッダ
    char riff[] = { 'R', 'I', 'F', 'F' };
    writer.write(riff, 4);

    // ファイルサイズ
    filesize += 36;
    writer.write((char*)&filesize, 4);

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
    filesize -= 36;
    writer.write((char*)&filesize, 4);

    // ファイルを閉じる
    writer.close();
}

void wave_writer::write_wave()
{
    note_count = 0;
    write_square_a();
    note_count = 0;
    write_square_b();
    note_count = 0;
    write_triangle();
}

void wave_writer::write_square_a()
{
    writer.seekp(44);

    if(raw_score.square_a.size() == 0) return;

    while(true)
    {
        // ファイルに書き込む値を取得

        // 音符の情報を取得
        note note = raw_score.square_a[note_count];

        // 音高から周波数を計算
        double freq = get_freq(note.scale);

        // 書き込むバイト数値を計算
        ubyte volume = note.volume / 2;
        switch(note.sound)
        {
            case instrument::square_2:
                volume *= wave_square_2(file_point_a / 44100.0 * freq);
                break;
            case instrument::square_4:
                volume *= wave_square_4(file_point_a / 44100.0 * freq);
                break;
            case instrument::square_8:
                volume *= wave_square_8(file_point_a / 44100.0 * freq);
                break;
            case instrument::triangle:
                volume *= wave_triangle(file_point_a / 44100.0 * freq);
                break;
            case instrument::noise:
                break;
        }

        // 音符の末端の約17ms前に差し掛かったら
        // 音符を区切る
        if(isover(file_point_a + 256, note)) volume = 0;

        // ファイルに書き込み
        writer.write((char*)&volume, 1);

        // ファイルポインタをインクリメント
        ++file_point_a;

        // 現在のファイルポインタのカウンタから拍子を導出した時
        // 音符の末端を過ぎていたら
        if(isover(file_point_a, note))
        {
            ++note_count;
            if(note_count >= raw_score.square_a.size())
            {
                break;
            }
        }
    }
}

void wave_writer::write_square_b()
{
    writer.seekp(44);
    reader.seekg(44);

    if(raw_score.square_b.size() == 0) return;

    while(true)
    {
        // ファイルに書き込む値を取得

        // 音符の情報を取得
        note note = raw_score.square_b[note_count];

        // 音高から周波数を計算
        double freq = get_freq(note.scale);

        // 書き込むバイト数値を計算
        ubyte volume = note.volume / 2;
        switch(note.sound)
        {
            case instrument::square_2:
                volume *= wave_square_2(file_point_b / 44100.0 * freq);
                break;
            case instrument::square_4:
                volume *= wave_square_4(file_point_b / 44100.0 * freq);
                break;
            case instrument::square_8:
                volume *= wave_square_8(file_point_b / 44100.0 * freq);
                break;
            case instrument::triangle:
                volume *= wave_triangle(file_point_b / 44100.0 * freq);
                break;
            case instrument::noise:
                break;
        }

        // 音符の末端の約17ms前に差し掛かったら
        // 音符を区切る
        if(isover(file_point_b + 256, note)) volume = 0;

        // ファイルに書き込み
        ubyte v;
        reader.read((char*)&v, 1);
        volume += v;
        writer.write((char*)&volume, 1);

        // ファイルポインタをインクリメント
        ++file_point_b;

        // 現在のファイルポインタのカウンタから拍子を導出した時
        // 音符の末端を過ぎていたら
        if(isover(file_point_b, note))
        {
            ++note_count;
            if(note_count >= raw_score.square_b.size())
            {
                break;
            }
        }
    }
}

void wave_writer::write_triangle()
{
    writer.seekp(44);
    reader.seekg(44);

    if(raw_score.triangle.size() == 0) return;

    while(true)
    {
        // ファイルに書き込む値を取得

        // 音符の情報を取得
        note note = raw_score.triangle[note_count];

        // 音高から周波数を計算
        double freq = get_freq(note.scale);

        // 書き込むバイト数値を計算
        ubyte volume = note.volume / 2;
        switch(note.sound)
        {
            case instrument::square_2:
                volume *= wave_square_2(file_point_c / 44100.0 * freq);
                break;
            case instrument::square_4:
                volume *= wave_square_4(file_point_c / 44100.0 * freq);
                break;
            case instrument::square_8:
                volume *= wave_square_8(file_point_c / 44100.0 * freq);
                break;
            case instrument::triangle:
                volume *= wave_triangle(file_point_c / 44100.0 * freq);
                break;
            case instrument::noise:
                break;
        }

        // 音符の末端の約17ms前に差し掛かったら
        // 音符を区切る
        if(isover(file_point_c + 256, note)) volume = 0;

        // ファイルに書き込み
        ubyte v;
        reader.read((char*)&v, 1);
        volume += v;
        writer.write((char*)&volume, 1);

        // ファイルポインタをインクリメント
        ++file_point_c;

        // 現在のファイルポインタのカウンタから拍子を導出した時
        // 音符の末端を過ぎていたら
        if(isover(file_point_c, note))
        {
            ++note_count;
            if(note_count >= raw_score.triangle.size())
            {
                break;
            }
        }
    }
}

bool wave_writer::isover(uint point, note note)
{
    // ビート数を計算
    rational beat1 = { (int)point * tempo, 2646000 };
    rational beat2 = (note.positon + note.length) * 4;

    return beat1 > beat2;
}