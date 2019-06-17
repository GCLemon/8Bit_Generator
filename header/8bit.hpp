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


// 音符の情報を持つ型
struct note
{
    rational positon; // 音符の位置
    rational length;  // 音長

    // 始点の音階
    int scale;

    // 音を鳴らすか
    bool play;
};


// 楽譜の情報を持つ型
struct score
{
    vector<note> square_a; // 矩形波トラックA
    vector<note> square_b; // 矩形波トラックB
    vector<note> triangle; // 三角波トラック
    vector<note> noise;    // ノイズトラック
};


// テキストを読み込んで楽譜情報を解析するクラス
class text_reader
{
private:

    // 入力ファイルストリーム
    ifstream reader;

    // デフォルトの音長・オクターブ
    int default_length = 4;
    int default_octave = 4;

    // 音符の位置
    rational position = { 0, 4 };

    // 楽譜オブジェクト
    score raw_score =
    {
        vector<note>(),
        vector<note>(),
        vector<note>(),
        vector<note>()
    };

    void add_note(smatch submathces);   // 楽譜に音符を追加する
    void set_octave(smatch submatches); // オクターブを変更する
    void set_length(smatch submatches);

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

    uint  file_point = 0; // ファイルのポインタ
    int   note_count = 0; // scoreオブジェクト内の楽譜のリスト番号

    // 出力ファイルストリーム
    ofstream writer;

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

    // ファイルポインタが指定された位置を超えたか
    bool isover(uint point, note note);

public:

    // コンストラクタ
    wave_writer(string path);

    // wavファイルに出力する
    void write(score score);
};

double get_freq(int scale); // 周波数を求める

double square_2(double x); // 50.0%パルス
double square_4(double x); // 25.0%パルス
double square_8(double x); // 12.5%パルス
double triangle(double x); // 三角波
double noise(double x);    // ノイズ

#endif