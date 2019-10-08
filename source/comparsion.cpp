#include "../header/rational.hpp"

#define d denominator
#define n numerator

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

// 大なり判定
bool rational::operator<  (float x)
{
    float y = (float)n / (float)d;
    return y < x;
}

// 小なり判定
bool rational::operator>  (float x)
{
    float y = (float)n / (float)d;
    return y > x;
}

// 等号付き大なり判定
bool rational::operator<= (float x)
{
    float y = (float)n / (float)d;
    return y <= x;
}

// 等号付き小なり判定
bool rational::operator>= (float x)
{
    float y = (float)n / (float)d;
    return y >= x;
}

// 大なり判定
bool rational::operator<  (double x)
{
    double y = (double)n / (double)d;
    return y < x;
}

// 小なり判定
bool rational::operator>  (double x)
{
    double y = (double)n / (double)d;
    return y > x;
}

// 等号付き大なり判定
bool rational::operator<= (double x)
{
    double y = (double)n / (double)d;
    return y <= x;
}

// 等号付き小なり判定
bool rational::operator>= (double x)
{
    double y = (double)n / (double)d;
    return y >= x;
}