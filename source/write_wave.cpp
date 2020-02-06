#include "../header/wave_writer.hpp"

using namespace retro_sound;

void wave_writer::write_wave(queue<note> score, queue<tempo_change> change)
{
    // 読み込み用ストリームを開く
    ifstream reader(path, ios::binary);

    uint   point = 0;     // ファイルポインタ
    double beat  = 0;     // 拍
    double tempo = 120;   // テンポ
    double freq_time = 0; // 経過速度を考慮した時間

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
        double pos = note.position;
        double len = note.length;

        // 音高・音量を求める
        double m = (beat * 0.25 - pos) / len;
        double scale = (double)note.start_scale * (1 - m) + (double)note.end_scale * m;
        double volume = (double)note.start_volume * (1 - m) + (double)note.end_volume * m;

        // 周波数を求める
        double freq = get_freq(scale);

        // ファイルに書き込む値
        ubyte velocity = volume / 2 * (*note.sound)(freq_time);
        if(beat > (pos + len * note.length_time) * 4) velocity = 0;
        freq_time += freq / 44100.0;

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

        // 拍を進める
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