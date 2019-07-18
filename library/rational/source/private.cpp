#include "../header/rational.hpp"

#define d denominator
#define n numerator

int abs(int x) { return x < 0 ? -x : x; }

// 絶対値の最大公約数
int rational::mcd_abs(int x, int y)
{
    x = abs(x); y = abs(y);

    while(x % y != 0)
    {
        int tmp_x = x;
        x = y;
        y = tmp_x % y;
    }

    return y;
}

// 絶対値の最小公倍数
int rational::mcm_abs(int x, int y)
{
    return abs(x) * abs(y) / mcd_abs(x, y);
}

// 約分
rational rational::reduce(rational x)
{
    int mcd = mcd_abs(x.n, x.d);
    if(x.d < 0) mcd *= -1;
    return { x.n / mcd, x.d / mcd };
}