#include "BigReal.h"


string convertToString(double value) {
    stringstream ss;
    ss << setprecision(numeric_limits<double>::digits10 + 1) << value;
    return ss.str();
}


BigReal::BigReal(double realNumber) {
   this->realNumber = convertToString(realNumber);

}


BigReal::BigReal(string s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            PointPos = i;
            s.erase(i, 1);
            break;
        }
    }
    RealBigWhole.setNumber(s);
    signReal = RealBigWhole.sign();
    s.insert(PointPos, ".");
    realNumber = s;
}


BigReal::BigReal(BigDecimalInt bigInteger) {
    RealBigWhole = bigInteger;
    RealBigDecimal.setNumber("0");
    PointPos = bigInteger.size();
}


BigReal::BigReal(const BigReal &other) {
    RealBigWhole = other.RealBigDecimal;
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
    } else if (this->RealBigWhole == anotherReal.RealBigWhole) {

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

    } else {
        return false;
    }
}


bool BigReal::operator<(BigReal anotherReal) {
    return (!(*this > anotherReal) and !(*this == anotherReal));
}


int BigReal::size() {
    return RealBigWhole.size();
}


int BigReal::sign() {
    return RealBigDecimal.sign();
}


ostream &operator<<(ostream &out, BigReal &num) {
    out << num.realNumber;
    return out;
}


istream &operator>>(istream &in, BigReal& num) {
    in >> num.realNumber;
    return in;
}

BigReal &BigReal::operator=(BigReal &other) {
    this->realNumber = other.realNumber;
    this->signReal = other.signReal;
    this->PointPos = other.PointPos;
}

















