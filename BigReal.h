//
// Created by dell on 10/31/2022.
//

#ifndef BIGREAL2_BIGREAL_H
#define BIGREAL2_BIGREAL_H


#include <bits/stdc++.h>
#include "BigDecimalIntClass.h"
using namespace std;


class BigReal {
private:
    string realNumber;
    BigDecimalInt RealBigWhole;
    int PointPos = 0;
    char signReal;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    int size();
    int sign();
    friend ostream& operator << (ostream& out, BigReal& num);
    friend istream& operator >> (istream& out, BigReal& num);
};


#endif //BIGREAL2_BIGREAL_H
