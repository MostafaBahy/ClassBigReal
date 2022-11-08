#include "BigReal.h"


string convertToString(double value) {
    stringstream ss;
    ss << setprecision(numeric_limits<double>::digits10 + 1) << value;
    return ss.str();
}


BigReal::BigReal(double realNumber) {
    this->realNumber = convertToString(realNumber);
    for (int i = 0; i < this->realNumber.size(); ++i) {
        if (this->realNumber[i] == '.') {
            PointPos = i;
            this->realNumber.erase(i, 1);
            break;
        }
    }
    if (!PointPos) {
        PointPos = RealBigWhole.size();
    }
    RealBigWhole.setNumber(this->realNumber);
    signReal = RealBigWhole.sign();
    this->realNumber.insert(PointPos, ".");
}


BigReal::BigReal(string s) {
    bool sign = false;
    if (s[0] == '-' || s[0] == '+') {
        sign = true;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            PointPos = i;
            s.erase(i, 1);
            break;
        }
    }
    RealBigWhole.setNumber(s);
    if (!PointPos) {
        PointPos = RealBigWhole.size();
        if (sign) PointPos++;
    }
    signReal = RealBigWhole.sign();
    s.insert(PointPos, ".");
    realNumber = s;

}


BigReal::BigReal(BigDecimalInt bigInteger) {
    RealBigWhole = bigInteger;
    PointPos = bigInteger.size();
    signReal = bigInteger.sign();
}


BigReal::BigReal(const BigReal &other) {
    RealBigWhole = other.RealBigWhole;
    realNumber = other.realNumber;
    signReal = other.signReal;
    PointPos = other.PointPos;
}


bool BigReal::operator==(BigReal anotherReal) {
    BigDecimalInt tmp;
    string s;
    if (this->RealBigWhole.size() > anotherReal.RealBigWhole.size() &&
        (this->PointPos == this->RealBigWhole.size() || anotherReal.PointPos == anotherReal.RealBigWhole.size())) {
        int diff = this->RealBigWhole.size() - anotherReal.RealBigWhole.size();
        s = anotherReal.realNumber;
        s.erase(anotherReal.PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        return (this->RealBigWhole == tmp && this->PointPos == anotherReal.PointPos);
    } else if (this->RealBigWhole.size() < anotherReal.size()&&
               (this->PointPos == this->RealBigWhole.size() || anotherReal.PointPos == anotherReal.RealBigWhole.size())) {
        int diff = anotherReal.RealBigWhole.size() - this->RealBigWhole.size();
        s = this->realNumber;
        s.erase(this->PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        return (tmp == anotherReal.RealBigWhole && this->PointPos == anotherReal.PointPos);
    }
    return (this->RealBigWhole == anotherReal.RealBigWhole && this->PointPos == anotherReal.PointPos);
}


bool BigReal::operator>(BigReal anotherReal) {
    BigDecimalInt tmp;
    string s;
    if (this->RealBigWhole.size() > anotherReal.RealBigWhole.size()&&
        (this->PointPos == this->RealBigWhole.size() || anotherReal.PointPos == anotherReal.RealBigWhole.size())) {
        int diff = this->RealBigWhole.size() - anotherReal.RealBigWhole.size();
        s = anotherReal.realNumber;
        s.erase(anotherReal.PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        if (this->sign() == 0 && anotherReal.sign() == 0)
            return ((this->RealBigWhole > tmp || this->RealBigWhole == tmp) &&
                    this->PointPos < anotherReal.PointPos);
        else if (this->sign() && anotherReal.sign())
            return ((this->RealBigWhole > tmp || this->RealBigWhole == tmp) &&
                    this->PointPos > anotherReal.PointPos);
    } else if (this->RealBigWhole.size() < anotherReal.size()&&
               (this->PointPos == this->RealBigWhole.size() || anotherReal.PointPos == anotherReal.RealBigWhole.size())) {
        int diff = anotherReal.RealBigWhole.size() - this->RealBigWhole.size();
        s = this->realNumber;
        s.erase(this->PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        if (this->sign() == 0 && anotherReal.sign() == 0)
            return ((tmp > anotherReal.RealBigWhole || tmp == anotherReal.RealBigWhole) &&
                    this->PointPos < anotherReal.PointPos);
        else if (this->sign() && anotherReal.sign())
            return ((tmp > anotherReal.RealBigWhole || tmp == anotherReal.RealBigWhole) &&
                    this->PointPos > anotherReal.PointPos);
    }
    if (this->sign() == 0 && anotherReal.sign() == 0)
        return ((this->RealBigWhole > anotherReal.RealBigWhole || this->RealBigWhole == anotherReal.RealBigWhole) &&
                this->PointPos < anotherReal.PointPos);
    else if (this->sign() && anotherReal.sign())
        return ((this->RealBigWhole > anotherReal.RealBigWhole || this->RealBigWhole == anotherReal.RealBigWhole) &&
                this->PointPos > anotherReal.PointPos);
}


bool BigReal::operator<(BigReal anotherReal) {
    return (!(*this > anotherReal) && !(*this == anotherReal));
}


int BigReal::size() {
    return RealBigWhole.size() + 1;
}


int BigReal::sign() {
    return RealBigWhole.sign();
}


ostream &operator<<(ostream &out, BigReal &num) {
    out << num.realNumber;
    return out;
}


istream &operator>>(istream &in, BigReal &num) {
    in >> num.realNumber;
    return in;
}


BigReal &BigReal::operator=(BigReal &other) {
    this->realNumber = other.realNumber;
    this->signReal = other.signReal;
    this->PointPos = other.PointPos;
}

















