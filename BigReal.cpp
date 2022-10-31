#include "BigReal.h"


BigReal::BigReal(string s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.')
            PointPos = i;
    }
    RealBigWhole.setNumber(s.substr(0, PointPos));                     // Put the half before dot in BigDecimal type

    RealBigDecimal.setNumber(s.substr(PointPos + 1, s.size() - PointPos - 1));      // Put the half after dot in BigDecimal type

}


BigReal::BigReal(BigDecimalInt bigInteger) {
    RealBigWhole = bigInteger;
    RealBigDecimal.setNumber("0");
    PointPos = bigInteger.size();
}


bool BigReal::operator==(BigReal anotherReal) {

    if (this->RealBigWhole == anotherReal.RealBigWhole and this->RealBigDecimal == anotherReal.RealBigDecimal) {
        return true;
    } else {
        return false;
    }

}


bool BigReal::operator>(BigReal anotherReal) {

    if (this->RealBigWhole > anotherReal.RealBigWhole) {
        return true;
    }


    else if (this->RealBigWhole == anotherReal.RealBigWhole) {

        int diff_length = 0;

        if (this->RealBigDecimal.size() > anotherReal.RealBigDecimal.size()) {

            string dec = anotherReal.RealBigDecimal.getNumber();
            diff_length = (this->RealBigDecimal.size() - anotherReal.RealBigDecimal.size());

            for (int i = 0; i < diff_length; i++) {
                dec += '0';
            }
            if (this->RealBigDecimal.getNumber() > dec) {

                return true;
            }
        }


        if (this->RealBigDecimal.size() < anotherReal.RealBigDecimal.size()) {

            string dec = this->RealBigDecimal.getNumber();
            diff_length = (anotherReal.RealBigDecimal.size() - this->RealBigDecimal.size());

            for (int i = 0; i < diff_length; i++) {
                dec += '0';
            }


            if (anotherReal.RealBigDecimal.getNumber() < dec) {
                return true;
            }

        }

    }

    else {
        return false;
    }
}


bool BigReal::operator<(BigReal anotherReal) {
    return (!( *this > anotherReal ) and !(*this == anotherReal));
}














