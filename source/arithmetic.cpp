#include "../header/rational.hpp"

#define d denominator
#define n numerator

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