#include "BigReal.h"

//Function to keep the decimal without rounding
//The compiler rounds the number ex: 60.9999999777

string convertToString(double value) {
    stringstream ss;
    ss << setprecision(numeric_limits<double>::digits10 + 1) << value;
    return ss.str();
}


BigReal::BigReal(double realNumber) {
    this->realNumber = convertToString(realNumber);     // call convertToString
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
    signReal = RealBigWhole.getSign();
    this->realNumber.insert(PointPos, ".");
}


BigReal::BigReal(string s) {

    if (s[0] == '-' || s[0] == '+') {
        signReal = s[0];
        s.erase(0, 1);
    } else
        signReal = '+';
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            PointPos = i;
            s.erase(i, 1);
            break;
        }
    }
    RealBigWhole.setNumber(signReal + s);
    if (!PointPos) {
        PointPos = RealBigWhole.size();
    }
    signReal = RealBigWhole.getSign();
    s.insert(PointPos, ".");
    realNumber = s;

}


BigReal::BigReal(BigDecimalInt bigInteger) {
    RealBigWhole = bigInteger;
    PointPos = bigInteger.size();
    signReal = bigInteger.getSign();
    realNumber = bigInteger.getNumber();
}


BigReal::BigReal(const BigReal &other) {
    RealBigWhole = other.RealBigWhole;
    realNumber = other.realNumber;
    signReal = other.signReal;
    PointPos = other.PointPos;
}


bool BigReal::operator==(BigReal anotherReal) {
    if (this->signReal == anotherReal.signReal && this->realNumber == anotherReal.realNumber)
        return true;
    return false;
}


bool BigReal::operator>(BigReal anotherReal) {

    // compare signs first

    if (this->signReal == '+' && anotherReal.signReal == '-')
        return true;
    else if (this->signReal == '-' && anotherReal.signReal == '+')
        return false;
    else if (this->signReal == '+' && anotherReal.signReal == '+') {

        //As they are both positive the farther the point the greater the number   12.1 > 2.1
        if (this->PointPos > anotherReal.PointPos)
            return true;

        else if (this->PointPos == anotherReal.PointPos)          // Compare two strings
            return this->realNumber > anotherReal.realNumber;
        else
            return false;
    } else {

        //Both are negative so invert the positive
        //Number with nearer point is larger -1.2 > 12.2
        if (this->PointPos < anotherReal.PointPos)
            return true;

        else if (this->PointPos == anotherReal.PointPos)         // Compare two strings
            return this->realNumber < anotherReal.realNumber;
        else
            return false;
    }
}


bool BigReal::operator<(BigReal anotherReal) {
    return (!(*this > anotherReal) && !(*this == anotherReal));
}


int BigReal::size() {
    return RealBigWhole.size();
}


int BigReal::sign() {
    if (signReal == '+')
        return 1;
    else
        return 0;
}


ostream &operator<<(ostream &out, BigReal &num) {
    if (num.signReal == '-')
        out << num.signReal << num.realNumber;
    else
        out << num.realNumber;
    return out;
}


istream &operator>>(istream &in, BigReal &num) {
    string tmp;
    in >> tmp;
    if (tmp[0] == '-' || tmp[0] == '+') {
        num.signReal = tmp[0];
        tmp.erase(tmp[0], 1);
    } else
        num.signReal = '+';
    num.realNumber = tmp;
    return in;
}


BigReal &BigReal::operator=(BigReal &other) {
    this->realNumber = other.realNumber;
    this->RealBigWhole = other.RealBigWhole;
    this->signReal = other.signReal;
    this->PointPos = other.PointPos;
}


BigReal &BigReal::operator=(BigReal &&other) {
    this->realNumber = other.realNumber;
    this->RealBigWhole = other.RealBigWhole;
    this->signReal = other.signReal;
    this->PointPos = other.PointPos;
}


BigReal BigReal::operator+(BigReal other) {

    BigDecimalInt tmp, sumD;
    string s;

    // Handle zeros make both have same length after the decimal point
    if (this->RealBigWhole.size() - this->PointPos > other.RealBigWhole.size() - other.PointPos) {
        int diff = (this->RealBigWhole.size() - this->PointPos) - (other.RealBigWhole.size() - other.PointPos);
        s = other.realNumber;
        s.erase(other.PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        sumD = this->RealBigWhole + tmp;
    } else if (this->RealBigWhole.size() - this->PointPos < other.RealBigWhole.size() - other.PointPos) {
        int diff = (other.RealBigWhole.size() - other.PointPos) - (this->RealBigWhole.size() - this->PointPos);
        s = this->realNumber;
        s.erase(this->PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        sumD = tmp + other.RealBigWhole;

    } else {
        sumD = this->RealBigWhole + other.RealBigWhole;
    }

    //Handle if the returned sum should have a leading zero ex: 1.9 + -1.3 = (0.)6
    if (this->RealBigWhole.getNumber()[0] == '0' && other.RealBigWhole.getNumber()[0] == '0' && sumD.size() == 1) {
        sumD.setNumber(sumD.getNumber().insert(0, 1, '0'));
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }
    if (this->RealBigWhole.getNumber()[0] == '0' && other.RealBigWhole.getNumber()[0] == '0' &&
        sumD.size() != 1) {
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }

    //Handle if the returned sum is different in length
    //if sum.size is larger move the point to the right          ps. maximum carry size is 1
    int pos = max(other.PointPos, this->PointPos);
    if (sumD.size() > max(tmp.size(), max(other.size(), this->size())))
        pos++;

    //if  sum is less shift the point left difference times
    else if (sumD.size() < max(tmp.size(), max(other.size(), this->size())))
        pos -= max(tmp.size(), max(other.size(), this->size())) - sumD.size();

    //ex: 1.9 + -1.3 = (0.)6
    if (pos == 0) {
        sumD.setNumber(sumD.getNumber().insert(0, 1, '0'));
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    } else {
        BigReal sum(sumD.getNumber().insert(pos, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }
}


BigReal::BigReal(BigReal &&other) {
    RealBigWhole = other.RealBigWhole;
    realNumber = other.realNumber;
    signReal = other.signReal;
    PointPos = other.PointPos;
}


BigReal BigReal::operator-(BigReal other) {

    // same as the + operator nothing different

    BigDecimalInt tmp, sumD;
    string s;

    if (this->RealBigWhole.size() - this->PointPos > other.RealBigWhole.size() - other.PointPos) {
        int diff = (this->RealBigWhole.size() - this->PointPos) - (other.RealBigWhole.size() - other.PointPos);
        s = other.realNumber;
        s.erase(other.PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        sumD = this->RealBigWhole - tmp;
    } else if (this->RealBigWhole.size() - this->PointPos < other.RealBigWhole.size() - other.PointPos) {
        int diff = (other.RealBigWhole.size() - other.PointPos) - (this->RealBigWhole.size() - this->PointPos);
        s = this->realNumber;
        s.erase(this->PointPos, 1);
        s.insert(s.length(), diff, '0');
        tmp.setNumber(s);
        sumD = tmp - other.RealBigWhole;
    } else {
        sumD = this->RealBigWhole - other.RealBigWhole;
    }

    if (this->RealBigWhole.getNumber()[0] == '0' && other.RealBigWhole.getNumber()[0] == '0' && sumD.size() == 1) {
        sumD.setNumber(sumD.getNumber().insert(0, 1, '0'));
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }
    if (this->RealBigWhole.getNumber()[0] == '0' && other.RealBigWhole.getNumber()[0] == '0' &&
        sumD.size() != 1) {
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }
    int pos = max(other.PointPos, this->PointPos);
    if (sumD.size() > max(tmp.size(), max(other.size(), this->size())))
        pos++;
    else if (sumD.size() < max(tmp.size(), max(other.size(), this->size())))
        pos -= max(tmp.size(), max(other.size(), this->size())) - sumD.size();
    if (pos == 0) {
        sumD.setNumber(sumD.getNumber().insert(0, 1, '0'));
        BigReal sum(sumD.getNumber().insert(1, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    } else {
        BigReal sum(sumD.getNumber().insert(pos, 1, '.'));
        sum.signReal = sumD.getSign();
        return sum;
    }
}

















