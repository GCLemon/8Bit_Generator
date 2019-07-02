#include "../header/8bit.hpp"

// 周波数を求める
double get_freq(int scale)
{
    return 27.5 * pow(2, scale / 12.0);
}

// 50%パルス
double wave_square_2(double x)
{
    double i;
    x = modf(x, &i);
    if(x < 0) ++x;
    return (x <= 0.5) ? 0 : 1;
}

// 25%パルス
double wave_square_4(double x)
{
    double i;
    x = modf(x, &i);
    if(x < 0) ++x;
    return (x <= 0.25) ? 0 : 1;
}

// 12.5%パルス
double wave_square_8(double x)
{
    double i;
    x = modf(x, &i);
    if(x < 0) ++x;
    return (x <= 0.125) ? 0 : 1;
}

// 三角波
double wave_triangle(double x)
{
    double i;
    x = modf(x, &i);
    if(x < 0) ++x;
    return 1 * (1 - abs(2 * x - 1));
}