#ifndef global_hpp
#define global_hpp

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <string>

#include "../header/rational.hpp"

using namespace std;

namespace retro_sound
{
    //////////////////////////////////////////////////
    //
    //    トークンを検出するための正規表現
    //

    const string t_str = "[A-D]";
    const string n_str = "([a-g])([+,-,^,v]*)(([+,-]?[0-9]+)*)([/,_,.]*)(:([+,-])?([0-9]+))?";
    const string r_str = "r(([+,-]?[0-9]+)*)([/,_,.]*)";
    const string o_str = "[<,>]|o([0-9]+)";
    const string l_str = "l([0-9]+)";
    const string v_str = "v([0-9]+)";
    const string at_i_str = "@i([0-9]+)";
    const string at_m_str = "@m([0-9]+(\\.[0-9]+)?)";

    //////////////////////////////////////////////////
    //
    //    音波を生成するための関数
    //

    double get_freq(int scale);     // 周波数を求める

    double wave_square_2(double x); // 50.0%パルス
    double wave_square_4(double x); // 25.0%パルス
    double wave_square_8(double x); // 12.5%パルス
    double wave_triangle(double x); // 三角波
    double wave_noise(double x);    // ノイズ

    //////////////////////////////////////////////////
    //
    //    列挙型
    //

    // トラック
    enum TRACK { A, B, C, D };

    // 音階
    enum scale { c = -9, d = -7, e = -5, f = -4, g = -2, a = 0, b = 2 };

    // 半音
    enum half { flat = -1, natural = 0, sharp = 1 };

    //////////////////////////////////////////////////
    //
    //    構造体
    //

    // 音符の情報を持つ型
    struct note
    {
        rational position;
        rational length;

        int scale;
        int volume;

        double (*sound)(double);
    };

    // 速度変化に関する情報を持つ型
    struct tempo_change
    {
        rational position;
        double after_tempo;
    };
}

#endif