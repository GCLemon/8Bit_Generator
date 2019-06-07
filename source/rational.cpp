#include "../header/rational.hpp"

#define d denominator
#define n numerator

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

// 加算
rational rational::operator+ (rational x)
{
    rational y = *this;
    return reduce({ x.d * y.n + x.n * y.d , x.d * y.d });
}

// 減算
rational rational::operator- (rational x)
{
    rational y = *this;
    return reduce({ x.d * y.n - x.n * y.d , x.d * y.d });
}

// 乗算
rational rational::operator* (rational x)
{
    rational y = *this;
    return reduce({ x.n * y.n, x.d * y.d });
}

// 除算
rational rational::operator/ (rational x)
{
    rational y = *this;
    return reduce({ x.d * y.n, x.n * y.d });
}

// 整数との加算
rational rational::operator+ (int x)
{
    rational y = *this;
    return reduce({ y.n + x * y.d , y.d });
}

// 整数との減算
rational rational::operator- (int x)
{
    rational y = *this;
    return reduce({ y.n - x * y.d , y.d });
}

// 整数との乗算
rational rational::operator* (int x)
{
    rational y = *this;
    return reduce({ y.n * x, y.d });
}

// 整数との除算
rational rational::operator/ (int x)
{
    rational y = *this;
    return reduce({ y.n, y.d * x });
}

// 加算 & 代入
rational rational::operator+= (rational x)
{
    *this = *this + x;
    return reduce(*this);
}

// 減算 & 代入
rational rational::operator-= (rational x)
{
    *this = *this - x;
    return reduce(*this);
}

// 乗算 & 代入
rational rational::operator*= (rational x)
{
    *this = *this * x;
    return reduce(*this);
}

// 除算 & 代入
rational rational::operator/= (rational x)
{
    *this = *this / x;
    return reduce(*this);
}

// 整数との加算 & 代入
rational rational::operator+= (int x)
{
    *this = *this + x;
    return reduce(*this);
}

// 整数との減算 & 代入
rational rational::operator-= (int x)
{
    *this = *this - x;
    return reduce(*this);
}

// 整数との乗算 & 代入
rational rational::operator*= (int x)
{
    *this = *this * x;
    return reduce(*this);
}

// 整数との除算 & 代入
rational rational::operator/= (int x)
{
    *this = *this / x;
    return reduce(*this);
}

// インクリメント
rational rational::operator++ ()
{
    *this += 1;
    return reduce(*this);
}

// デクリメント
rational rational::operator-- ()
{
    *this -= 1;
    return reduce(*this);
}

// 等価判定
bool rational::operator== (rational x)
{
    rational y = reduce(*this);
             x = reduce(x    );

    return y.n == x.n && y.d == x.d;
}

// 不等判定
bool rational::operator!= (rational x)
{
    return !(x == *this);
}

// 大なり判定
bool rational::operator<  (rational x)
{
    rational y = reduce(*this);
             x = reduce(x    );

    return y.n * x.d < y.d * x.n;
}

// 小なり判定
bool rational::operator>  (rational x)
{
    rational y = reduce(*this);
             x = reduce(x    );

    return y.n * x.d > y.d * x.n;
}

// 等号付き大なり判定
bool rational::operator<= (rational x)
{
    return !(x > *this);
}

// 等号付き小なり判定
bool rational::operator>= (rational x)
{
    return !(x < *this);
}

// 等価判定
bool rational::operator== (int x)
{
    rational y = *this;
    return y.n == x * y.d;
}

// 不等判定
bool rational::operator!= (int x)
{
    rational y = *this;
    return y.n != x * y.d;
}

// 大なり判定
bool rational::operator<  (int x)
{
    rational y = *this;
    return y.n < x * y.d;
}

// 小なり判定
bool rational::operator>  (int x)
{
    rational y = *this;
    return y.n > x * y.d;
}

// 等号付き大なり判定
bool rational::operator<= (int x)
{
    rational y = *this;
    return y.n <= x * y.d;
}

// 等号付き小なり判定
bool rational::operator>= (int x)
{
    rational y = *this;
    return y.n >= x * y.d;
}

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