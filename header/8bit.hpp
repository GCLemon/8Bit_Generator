//////////////////////////////////////////////////
//
//    8bit.hpp
//

#ifndef eight_bit
#define eight_git

#include <cmath>        // 数学系のあれこれ
#include <fstream>      // ファイル入出力周り
#include <iostream>     // 標準入出力周り
#include <regex>        // 正規表現
#include <string>       // 文字列
#include <vector>       // 動的配列

#include "rational.hpp" // 自作の有理数型

using namespace std;


typedef char           byte;   // 1バイト整数(文字)
typedef unsigned char  ubyte;  // 符号なし1バイト整数
typedef unsigned short ushort; // 符号なし2バイト整数
typedef unsigned int   uint;   // 符号なし4バイト整数
typedef unsigned long  ulong;  // 符号なし8バイト整数


// トラック
enum track
{
    Square_A, // 矩形波トラックA
    Square_B, // 矩形波トラックB
    Triangle, // 三角波トラック
    Noise     // ノイズトラック
};

// 音階
enum scale
{
    c = -9, // ド
    d = -7, // レ
    e = -5, // ミ
    f = -4, // ファ
    g = -2, // ソ
    a = 0,  // ラ
    b = 2,  // シ
};

// 半音
enum half
{
    flat = -1,   // ♭
    natural = 0, // 普通の音
    sharp = 1    // ♯
};

// 音の種類
enum instrument
{
    square_2, // 50%パルス
    square_4, // 25%パルス
    square_8, // 12.5%パルス
    triangle, // 三角波
    noise     // ノイズ
};


// 音符の情報を持つ型
struct note
{
    instrument sound; // 音の種類

    rational positon; // 音符の位置
    rational length;  // 音長

    int scale;  // 音階
    int volume; // 音量
};

// 楽譜の情報を持つ型
struct score
{
    vector<note> square_a; // 矩形波トラックA
    vector<note> square_b; // 矩形波トラックB
    vector<note> triangle; // 三角波トラック
    vector<note> noise;    // ノイズトラック
};

// トラックごとのデフォルト値
struct default_value
{
    int default_length = 4;
    int default_octave = 4;
    int default_volume = 100;

    // 音符の位置
    rational position = { 0, 4 };

    instrument default_sound = instrument::square_4;
};


// テキストを読み込んで楽譜情報を解析するクラス
class text_reader
{
private:

    // 入力ファイルストリーム
    ifstream reader;

    // デフォルトの音長・オクターブ
    default_value square_a = { 4, 4, 100, {0, 4}, instrument::square_4 };
    default_value square_b = { 4, 4, 100, {0, 4}, instrument::square_4 };
    default_value triangle = { 4, 4, 100, {0, 4}, instrument::triangle };
    default_value noise;


    // 楽譜オブジェクト
    score raw_score =
    {
        vector<note>(),
        vector<note>(),
        vector<note>(),
        vector<note>()
    };

    void add_note  (smatch submathces, track track); // 楽譜に音符を追加する
    void add_rest  (smatch submathces, track track); // 楽譜に休符を追加する
    void set_octave(smatch submatches, track track); // オクターブを変更する
    void set_length(smatch submatches, track track); // 音長を変更する
    void set_volume(smatch submatches, track track); // 音量を変更する

    void set_instrument(smatch submatches, track track);

public:

    // コンストラクタ
    text_reader(string path);

    // テキストファイルから楽譜に変換する
    void read();

    // 楽譜を取得する
    score get_score();
};


// 楽譜情報をwavファイルに落とし込むクラス
class wave_writer
{
private:

    int   tempo = 120; // テンポ[bpm.]

    uint  file_point_a = 0; // ファイルのポインタ
    uint  file_point_b = 0;
    uint  file_point_c = 0;
    int   note_count = 0; // scoreオブジェクト内の楽譜のリスト番号

    // ファイルストリーム
    ofstream writer;
    ifstream reader;

    // 楽譜オブジェクト
    score raw_score =
    {
        vector<note>(),
        vector<note>(),
        vector<note>(),
        vector<note>()
    };

    void write_header(); // ヘッダを書き込む
    void write_wave();   // 波データを書き込む

    void write_square_a();
    void write_square_b();
    void write_triangle();

    // ファイルポインタが指定された位置を超えたか
    bool isover(uint point, note note);

public:

    // コンストラクタ
    wave_writer(string path);

    // wavファイルに出力する
    void write(score score);
};

double get_freq(int scale); // 周波数を求める

double wave_square_2(double x); // 50.0%パルス
double wave_square_4(double x); // 25.0%パルス
double wave_square_8(double x); // 12.5%パルス
double wave_triangle(double x); // 三角波
double wave_noise(double x);    // ノイズ

#endif