//////////////////////////////////////////////////
//
//    8bit.hpp
//

#ifndef eight_bit
#define eight_git

#include <cmath>    // 数学系のあれこれ
#include <fstream>  // ファイル入出力周り
#include <iostream> // 標準入出力周り
#include <regex>    // 正規表現
#include <string>   // 文字列
#include <vector>   // 動的配列

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
    // 音長
    int length;

    // 始点の音階
    int scale;
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
    ifstream reader;

public:
    text_reader(string path);

    score read();
};


// 楽譜情報をwavファイルに落とし込むクラス
class wave_writer
{
private:
    ofstream writer;

public:
    wave_writer(string path);

    void write(score score);
};

double get_freq(int scale); // 周波数を求める

ubyte square_2(double x); // 50.0%パルス
ubyte square_4(double x); // 25.0%パルス
ubyte square_8(double x); // 12.5%パルス
ubyte triangle(double x); // 三角波
ubyte noise(double x);    // ノイズ

#endif

/* 
 * <ToDo>
 * 
 * 5/21(火)
 * ・簡単な楽譜を作成し,それを解析した結果を標準出力で表示する
 * ・解析した結果をwavファイルに出力する
 * 
 */