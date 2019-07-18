#include "../header/wave_writer.hpp"

using namespace retro_sound;

void wave_writer::write_wave(queue<note> score, queue<tempo_change> change)
{
    // 読み込み用ストリームを開く
    ifstream reader(path, ios::binary);

    uint   point = 0;   // ファイルポインタ
    double beat  = 0;   // 拍
    double tempo = 120; // テンポ

    // ファイルの位置を合わせる
    writer.seekp(44);
    if(!reader.fail()) reader.seekg(44);

    // 入力されたキューが空なら処理を終える
    if(score.empty()) return;

    // 音符の情報を取り出す
    note note = score.front();

    while(!score.empty())
    {
        // 定義
        #define pos note.position.to_double()
        #define len note.length.to_double()

        // 周波数を求める
        double freq = get_freq(note.scale);

        // ファイルに書き込む値
        ubyte velocity = note.volume / 2 * (*note.sound)(point / 44100.0 * freq);

        // ファイルに書き込み
        ubyte v = 0;
        if(!reader.fail())
            reader.read((char*)&v, 1);
        velocity += v;
        writer.write((char*)&velocity, 1);

        // 拍を進める前にテンポを変更
        if(!change.empty())
            if(change.front().position * 4 <= beat)
            {
                tempo = change.front().after_tempo;
                change.pop();
            }

        // ファイルに書き込み & 拍を進める
        ++point;
        beat += tempo / 2646000.0;

        // キューから音符の情報を取り出す
        double end = (pos + len) * 4;
        if(beat > end)
        {
            score.pop();
            note = score.front();
        }
    }

    // point_max を更新
    if(point_max < point) point_max = point;

    // 読み込み用ストリームを閉じる
    reader.close();
}