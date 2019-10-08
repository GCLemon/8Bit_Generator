#include "../header/rational.hpp"

#define d denominator
#define n numerator

// int 型に変換
int rational::to_int()
{
    return n / d;
}

// float 型に変換
float rational::to_float()
{
    return (float)n / (float)d;
}

// double 型に変換
double rational::to_double()
{
    return (double)n / (double)d;
}

string rational::to_string()
{
    ostringstream n_str;
    ostringstream d_str;
    n_str << n; d_str << d;
    return n_str.str() + " / " + d_str.str();
}