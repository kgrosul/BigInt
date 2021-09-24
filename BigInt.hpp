#include <iostream>
#include <vector>


using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::max;
using std::swap;


class BigInteger {
private:
    vector<int> digits_;
    int sign_;

    static BigInteger _abs(BigInteger x) {
        x.sign_ = 1;
        return x;
    }


    void _normalize() {
        if (digits_.back() < 0) {
            sign_ ^= 1;
            digits_.back() = abs(digits_.back());
        }
        int zeroCounter = 0;
        for (int i = int(digits_.size() - 1); i >= 0; --i) {
            if (digits_[i] == 0)
                zeroCounter++;
            else
                break;
        }
        digits_.resize(max(1, int(digits_.size()) - zeroCounter));

        if (int(digits_.size()) == 1 && digits_[0] == 0)
            sign_ = 1;

    }

    BigInteger _div2() {
        BigInteger result = *this;
        for (int i = this->digits_.size() - 1; i >= 0; --i) {
            if (i > 0 && result.digits_[i] % 2 == 1) {
                result.digits_[i - 1] += 10;
            }
            result.digits_[i] /= 2;
        }
        result._normalize();
        return result;
    }

    bool isZero() const {
        return digits_.size() == 1 && digits_[0] == 0;
    }

public:
    BigInteger() {
        digits_.push_back(0);
        sign_ = 1;
    }

    BigInteger(int x) {
        if (x < 0)
            sign_ = 0;
        else
            sign_ = 1;
        x = abs(x);
        while (x > 0) {
            digits_.push_back(x % 10);
            x /= 10;
        }
        if (digits_.empty())
            digits_ = {0};
    }

    BigInteger(string s) {
        if (s.size() == 0) {
            s.push_back('0');
        }
        if (s[0] == '-')
            sign_ = 0;
        else
            sign_ = 1;
        bool firstSymbolIsNotDigit;
        firstSymbolIsNotDigit = s[0] == '-' || s[0] == '+' ? true : false;
        digits_.resize(s.size() - int(firstSymbolIsNotDigit));

        for (auto i = int(firstSymbolIsNotDigit); i < int(s.size()); ++i) {
            digits_[i - int(firstSymbolIsNotDigit)] = int(s[i] - '0');
        }
        for (int i = 0; i < int(digits_.size()) / 2; ++i)
            swap(digits_[i], digits_[int(digits_.size()) - 1 - i]);

        _normalize();
    }

    string toString() const {
        string stringOfBigInteger;
        for (int i = int(digits_.size()) - 1; i >= 0; --i)
            stringOfBigInteger += char('0' + digits_[i]);

        if (sign_ == 0)
            stringOfBigInteger = "-" + stringOfBigInteger;
        return stringOfBigInteger;
    }

    bool operator<(BigInteger const &other) const {
        if (this->sign_ < other.sign_)
            return true;
        if (this->sign_ > other.sign_)
            return false;
        if (this->sign_ > 0) {
            if (this->digits_.size() < other.digits_.size())
                return true;
            if (this->digits_.size() > other.digits_.size())
                return false;
            for (int i = int(other.digits_.size()) - 1; i >= 0; --i) {
                if (this->digits_[i] < other.digits_[i])
                    return true;
                if (this->digits_[i] > other.digits_[i])
                    return false;
            }

            return this->digits_.back() < other.digits_.back();
        } else {
            BigInteger first = *this;
            BigInteger second = other;
            first.sign_ = 1;
            second.sign_ = 1;
            return (second < first);
        }
    }

    inline bool operator==(BigInteger const &other) const {
        return ((*this).sign_ == other.sign_) && ((*this).digits_ == other.digits_);
    }

    inline bool operator==(int other) const {
        return (*this) == BigInteger(other);
    }

    inline bool operator!=(BigInteger const &other) const {
        return !((*this) == other);
    }

    inline bool operator!=(int other) const {
        BigInteger otherBigInt = BigInteger(other);
        return (*this) != otherBigInt;
    }

    inline bool operator<(int other) const {
        return (*this) < BigInteger(other);
    }

    inline bool operator<=(BigInteger const &other) const {
        return (*this < other || *this == other);

    }

    inline bool operator<=(int other) const {
        return (*this) <= BigInteger(other);
    }

    inline bool operator>(BigInteger const &other) const {
        return !((*this) <= other);
    }

    inline bool operator>(int other) const {
        return (*this) > BigInteger(other);
    }

    inline bool operator>=(BigInteger const &other) const {
        return !((*this) < other);
    }

    inline bool operator>=(int other) const {
        return (*this) >= BigInteger(other);
    }

    BigInteger &operator=(BigInteger const &other) {
        if (this == &other)
            return *this;
        this->sign_ = other.sign_;
        this->digits_ = other.digits_;
        return *this;
    }

    BigInteger &operator+=(BigInteger const &other) {
        *this = *this + other;
        return *this;

    }


    BigInteger operator+(BigInteger const &other) const {
        BigInteger sumThis = (*this);
        BigInteger sumOther = other;
        if (sumThis.sign_ == sumOther.sign_) {
            while (sumThis.digits_.size() < sumOther.digits_.size()) {
                sumThis.digits_.push_back(0);
            }

            while (sumThis.digits_.size() > sumOther.digits_.size()) {
                sumOther.digits_.push_back(0);
            }

            for (int i = 0; i < int(sumOther.digits_.size()) - 1; ++i) {
                sumThis.digits_[i] += sumOther.digits_[i];
                if (sumThis.digits_[i] > 9) {
                    sumThis.digits_[i + 1] += sumThis.digits_[i] / 10;
                    sumThis.digits_[i] %= 10;
                }

            }
            sumThis.digits_.back() += sumOther.digits_.back();
            while (sumThis.digits_.back() > 9) {
                sumThis.digits_.push_back(sumThis.digits_[sumThis.digits_.size() - 1] / 10);
                sumThis.digits_[sumThis.digits_.size() - 2] %= 10;
            }

        } else {
            if (_abs(sumThis) < _abs(sumOther)) {
                swap(sumThis, sumOther);
            }
            for (int i = 0; i < int(sumOther.digits_.size()); ++i) {
                sumThis.digits_[i] -= sumOther.digits_[i];
                if (sumThis.digits_[i] < 0) {
                    sumThis.digits_[i] += 10;
                    sumThis.digits_[i + 1] -= 1;
                }
            }
            for (auto i = int(sumOther.digits_.size()); i < int(sumThis.digits_.size()); ++i) {
                if (sumThis.digits_[i] < 0) {
                    sumThis.digits_[i] += 10;
                    sumThis.digits_[i + 1] -= 1;
                }
            }

            while (sumThis.digits_.back() == 0 && sumThis.digits_.size() > 1) {
                sumThis.digits_.pop_back();
            }
        }

        sumThis._normalize();

        return sumThis;
    }

    inline BigInteger operator+(int other) const {
        return (*this) + BigInteger(other);
    }


    BigInteger &operator-=(BigInteger const &other) {
        *this = *this - other;
        return *this;
    }

    BigInteger operator-(BigInteger const &other) const {
        BigInteger result = (*this);
        result = result + (-other);
        return result;

    }

    BigInteger operator-() const {
        BigInteger result = *this;
        if (!result.isZero())
            result.sign_ ^= 1;
        return result;
    }

    BigInteger operator++(int) {
        BigInteger copy = (*this);
        (*this) += 1;
        this->_normalize();
        return copy;
    }

    BigInteger operator*(BigInteger const &other) const {
        if (this->digits_.size() == 1 && this->digits_[0] == 0)
            return BigInteger(0);

        if (other.digits_.size() == 1 && other.digits_[0] == 0)
            return BigInteger(0);
        BigInteger result;
        result.digits_.assign(this->digits_.size() + other.digits_.size() + 1, 0);
        for (int i = 0; i < int(this->digits_.size()); ++i) {
            for (int j = 0; j < int(other.digits_.size()); ++j) {
                result.digits_[i + j] += this->digits_[i] * other.digits_[j];
            }
        }
        for (int i = 0; i < int(result.digits_.size()) - 1; ++i) {
            result.digits_[i + 1] += result.digits_[i] / 10;
            result.digits_[i] %= 10;
        }
        if(!result.isZero())
            result.sign_ = 1 - (this->sign_ ^ other.sign_);
        result._normalize();
        return result;
    }

    inline BigInteger operator*(int other) const {
        return (*this) * BigInteger(other);
    }

    BigInteger operator/(BigInteger const &other) const {
        BigInteger thisBigInteger = (*this);
        int sign = 1 - (this->sign_ ^ other.sign_);
        thisBigInteger.sign_ = 1;
        BigInteger left(0);
        BigInteger right = thisBigInteger + 1;
        while (right - left > 1) {
            BigInteger middle = left + right;
            middle = middle._div2();
            BigInteger result = middle * other;
            result.sign_ = 1;
            if (result <= thisBigInteger) {
                left = middle;
            } else {
                right = middle;
            }
        }
        left.sign_ = sign;
        left._normalize();
        return left;
    }

    inline BigInteger operator/(int other) const {
        return (*this) / BigInteger(other);
    }


    BigInteger &operator/=(BigInteger const &other) {
        BigInteger multiplier = (*this);
        (*this) = multiplier / other;
        return *this;
    }

    BigInteger &operator/=(int other) {
        BigInteger multiplier = (*this);
        (*this) = multiplier / BigInteger(other);
        return *this;
    }

    BigInteger operator--(int) {
        BigInteger copy = (*this);
        (*this) -= 1;
        this->_normalize();
        return copy;
    }

    BigInteger &operator++() {
        (*this) += 1;
        this->_normalize();
        return (*this);
    }

    BigInteger &operator--() {
        (*this) -= 1;
        this->_normalize();
        return (*this);
    }

    inline bool operator&&(BigInteger const &other) const {
        return bool(*this) && bool(other);
    }

    inline bool operator||(BigInteger const &other) const {
        return bool(*this) || bool(other);
    }

    inline bool operator&&(int other) const {
        return bool(*this) && bool(other);
    }

    inline bool operator||(int other) const {
        return bool(*this) || bool(other);
    }


    inline bool operator&&(bool other) const {
        return bool(*this) && other;
    }

    inline bool operator||(bool other) const {
        return bool(*this) || other;
    }


    inline BigInteger &operator*=(BigInteger const &other) {
        (*this) = (*this) * other;
        return *this;
    }

    BigInteger operator%(BigInteger const &other) const {
        BigInteger tmp = *this;
        return *this - ((*this / other) * other);
    }

    BigInteger operator%(int other) const {
        return (*this) % BigInteger(other);
    }

    BigInteger &operator%=(BigInteger const &other) {
        BigInteger multiplier = (*this);
        (*this) = multiplier % other;

        return *this;
    }

    explicit operator bool() const {
        return !this->isZero();
    }
};


istream &operator>>(istream &cin, BigInteger &number) {
    string stringNumber;
    cin >> stringNumber;
    number = BigInteger(stringNumber);
    return cin;
}

ostream &operator<<(ostream &cout, const BigInteger  &number) {
    cout << number.toString();
    return cout;
}

BigInteger operator+(int first, BigInteger const &second) {
    BigInteger firstBigInteger = BigInteger(first);
    firstBigInteger += second;
    return firstBigInteger;
}

BigInteger operator-(int first, BigInteger const &second) {
    BigInteger firstBigInteger = BigInteger(first);
    firstBigInteger -= second;
    return firstBigInteger;
}

inline bool operator==(int first, BigInteger const &second) {
    return BigInteger(first) == second;
}

inline bool operator!=(int first, BigInteger const &second) {
    return BigInteger(first) != second;
}

inline bool operator<=(int first, BigInteger const &second) {
    return BigInteger(first) <= second;

}

inline bool operator>=(int first, BigInteger const &second) {
    return BigInteger(first) >= second;
}

inline bool operator>(int first, BigInteger const &second) {
    return BigInteger(first) > second;
}

inline bool operator<(int first, const BigInteger &second) {
    return (BigInteger(first) < second);
}

inline bool operator&&(int first, BigInteger const &second) {
    return bool(first) && bool(second);
}

inline bool operator||(int first, BigInteger const &second) {
    return bool(first) || bool(second);
}

inline bool operator&&(bool first, BigInteger const &second) {
    return first && bool(second);
}


inline bool operator||(bool first, BigInteger const &second) {
    return first || bool(second);
}

inline BigInteger operator*(int first, BigInteger const &second) {
    return second * BigInteger(first);
}


inline BigInteger operator/(int first, BigInteger const &second) {
    return BigInteger(first) / second;
}

inline BigInteger operator%(int first, BigInteger const &second) {
    return BigInteger(first) % second;
}
