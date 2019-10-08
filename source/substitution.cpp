#include "../header/rational.hpp"

#define d denominator
#define n numerator

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