//////////////////////////////////////////////////
//
//    rational.hpp
//


#ifndef rational_hpp
#define rational_hpp

#include <math.h>
#include <sstream>
#include <string>

using namespace std;

//////////////////////////////////////////////////
//
//    有理数型
//

struct rational
{
private:

    //////////////////////////////////////////////////
    //
    //    絶対値の最大公約数・最小公倍数
    //

    int mcd_abs(int x, int y);
    int mcm_abs(int x, int y);

    //////////////////////////////////////////////////
    //
    //    約分
    //

    rational reduce(rational x);

public:

    //////////////////////////////////////////////////
    //
    //    分子・分母
    //

    int numerator;
    int denominator;

    //////////////////////////////////////////////////
    //
    //    有理数型の演算子の定義
    //

    // 算術演算
    rational operator+ (rational x);
    rational operator- (rational x);
    rational operator* (rational x);
    rational operator/ (rational x);

    // 整数型との算術演算
    // (long, short, char　などへの対応も予定)
    rational operator+ (int x);
    rational operator- (int x);
    rational operator* (int x);
    rational operator/ (int x);

    // 代入演算
    rational operator+= (rational x);
    rational operator-= (rational x);
    rational operator*= (rational x);
    rational operator/= (rational x);

    // 整数型との代入演算
    // (long, short, char　などへの対応も予定)
    rational operator+= (int x);
    rational operator-= (int x);
    rational operator*= (int x);
    rational operator/= (int x);

    // インクリメント・デクリメント
    rational operator++ ();
    rational operator-- ();

    // 比較演算
    bool operator== (rational x);
    bool operator!= (rational x);
    bool operator<  (rational x);
    bool operator>  (rational x);
    bool operator<= (rational x);
    bool operator>= (rational x);

    // 整数型との比較演算
    // (long, short, char　などへの対応も予定)
    bool operator== (int x);
    bool operator!= (int x);
    bool operator<  (int x);
    bool operator>  (int x);
    bool operator<= (int x);
    bool operator>= (int x);

    bool operator<  (float x);
    bool operator>  (float x);
    bool operator<= (float x);
    bool operator>= (float x);

    bool operator<  (double x);
    bool operator>  (double x);
    bool operator<= (double x);
    bool operator>= (double x);

    // 整数・小数に変換する
    int    to_int();
    float  to_float();
    double to_double();
    string to_string();
};

#endif