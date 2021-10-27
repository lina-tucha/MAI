/*Хренникова Ангелина
Лабораторная работа №6*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

const int BASE = 10000;
const int DIGIT_LENGTH = 4;

class TBigInt {
private:
    std::vector<int> bigInt;

public:
    TBigInt(int value);
    TBigInt(const std::string& value);
    int GetDigit(int id) const;
    void SetDigit(int position, int value);
    TBigInt operator+(const TBigInt& other) const;
    TBigInt operator-(const TBigInt& other) const;
    TBigInt operator*(const TBigInt& other) const;
    TBigInt operator/(const TBigInt& other) const;
    TBigInt Pow(TBigInt& first);
    void Shift(int sh);
    void DeleteZeros();
    operator unsigned long long();
    friend int Compare(const TBigInt& first, const TBigInt& second);
    bool operator<(const TBigInt& other) const;
    bool operator>(const TBigInt& other) const;
    bool operator==(const TBigInt& other) const;
    friend std::ostream& operator<<(std::ostream& out, TBigInt num);
};

TBigInt::TBigInt(int value) {
    if (value == 0) {
        bigInt.push_back(0);
    } else {
        for (int i = value; i > 0; i /= BASE) {
            bigInt.push_back(i % BASE);
        }
    }
}

TBigInt::TBigInt(const std::string& value) {
    for (int i = value.length() - 1; i >= 0; i -= DIGIT_LENGTH) {
        int curDigit = 0;
        int curDegree = 1;
        for (int j = 0; j < DIGIT_LENGTH && i >= j; ++j) {
            curDigit += (value[i - j] - '0') * curDegree;
            curDegree *= 10;
        }
        bigInt.push_back(curDigit);
    }
    DeleteZeros();
}

void TBigInt::DeleteZeros() {
    while (bigInt.size() > 1 && bigInt.back() == 0) {
        bigInt.pop_back();
    }
}

int TBigInt::GetDigit(int id) const {
    if (id >= bigInt.size()) {
        return 0;
    }
    if (id < 0) {
        throw std::logic_error("Wrong id");
    }
    return bigInt[id];
}

void TBigInt::SetDigit(int position, int value) {
    if (position > bigInt.size() - 1) {
        bigInt.resize(position + 1);
    }
    bigInt[position] = value;
}

TBigInt TBigInt::operator+(const TBigInt& other) const {
    int newSize = std::max(bigInt.size(), other.bigInt.size()) + 1;
    TBigInt res(0);
    res.bigInt.resize(newSize);
    int tmp;
    int k = 0;
    for (int i = 0; i < newSize - 1; ++i) {
        tmp = GetDigit(i) + other.GetDigit(i) + k;
        k = tmp / BASE;
        res.SetDigit(i, tmp % BASE);

    }
    if (k != 0) {
        res.SetDigit(newSize - 1, k);
    }
    res.DeleteZeros();
    return res;
}

TBigInt TBigInt::operator-(const TBigInt& other) const {
    if (*this < other) {
        throw std::logic_error("Error");
    }
    int newSize = bigInt.size();
    TBigInt res(0);
    res.bigInt.resize(newSize);
    int k = 0;
    int tmp;
    for (int i = 0; i < newSize; ++i) {
        tmp = GetDigit(i) - other.GetDigit(i) - k;
        k = (tmp < 0);
        if (k) {
            tmp += BASE;
        }
        res.SetDigit(i, tmp);
    }
    res.DeleteZeros();
    return res;
}

TBigInt TBigInt::operator*(const TBigInt& other) const {
    int newSize = bigInt.size() + other.bigInt.size();
    TBigInt res(0);
    res.bigInt.resize(newSize);
    for (int j = 0; j < other.bigInt.size(); ++j) {
        if (other.bigInt[j] == 0) {
            continue;
        }
        int k = 0;
        for (int i = 0; i < bigInt.size(); ++i) {
            int tmp = GetDigit(i) * other.GetDigit(j) + k + res.GetDigit(i + j);
            k = tmp / BASE;
            res.SetDigit(i + j, tmp % BASE);
        }
        if (k) {
            res.SetDigit(j + bigInt.size(), k);
        }
    }
    res.DeleteZeros();
    return res;
}

TBigInt TBigInt::operator/(const TBigInt& other) const {
    TBigInt res(0);
    if (other.GetDigit(0) == 0 && other.bigInt.size() == 1) {
        throw std::logic_error("Error");
    }
    int n = other.bigInt.size();
    if (*this < other) {
        return res;
    }
    int m = bigInt.size() - n;
    int d = BASE / (other.GetDigit(n - 1) + 1);
    TBigInt u = *this;
    std::string s1 = std::to_string(d);
    TBigInt tmp1(s1);
    u = u * tmp1;
    u.bigInt.push_back(0);
    TBigInt v = other;
    v = v * tmp1;
    res.bigInt.resize(m + 1);
    TBigInt qv(0);
    unsigned long long q;
    unsigned long long r;
    for (int j = m; j >= 0; j--) {
        q = ((unsigned long long)u.GetDigit(j + n) * BASE + u.GetDigit(n + j - 1)) / v.GetDigit(n - 1);
        r = ((unsigned long long)u.GetDigit(j + n) * BASE + u.GetDigit(n + j - 1)) - v.GetDigit(n - 1) * q;
        while ((q == BASE || (q * v.GetDigit(n - 2)) > (BASE * r + u.GetDigit(j + n - 2))) && r < BASE) {
            q -= 1;
            r += v.GetDigit(n - 1);
        }
        qv = v;
        std::string s2 = std::to_string(q);
        TBigInt tmp2(s2);
        qv = qv * tmp2;
        qv.Shift(j);
        if (u < qv) {
            u.bigInt.push_back(1);
            q -= 1;
        }
        u = u - qv;
        res.SetDigit(j, q);
    }
    while (res.bigInt.size() > 1 && res.bigInt.back() == 0) {
        res.bigInt.pop_back();
    }
    res.DeleteZeros();
    return res;
}

TBigInt::operator unsigned long long() {
    unsigned long long out = 0;
    for (int i = 0; i < bigInt.size(); i++) {
        out += (unsigned long long)GetDigit(i) * (unsigned long long)pow(BASE, i);
    }
    return out;
}

void TBigInt::Shift(int sh) {
    if (bigInt.size() == 1 && GetDigit(0) == 0) {
        return;
    }
    TBigInt new_num(0);
    new_num.bigInt.resize(bigInt.size() + sh, 0);
    copy(bigInt.begin(), bigInt.end(), new_num.bigInt.begin() + sh);
    std::swap(new_num, *this);
}

TBigInt TBigInt::Pow(TBigInt& other) {
    TBigInt res(1), zero(0), one(1), two(2);
    if (*this == zero && other == zero) {
        throw std::logic_error("Error");
    }
    while (other > zero) {
        if (other.GetDigit(0) % 2 == 1) {
            res = res * (*this);
            other = other - one;
        } else {
            (*this) = (*this) * (*this);
            other = other / two;
        }
    }
    return res;
}

int Compare(const TBigInt& first, const TBigInt& second) {
    if (first.bigInt.size() < second.bigInt.size()) {
        return 1;
    }
    else if (first.bigInt.size() > second.bigInt.size()) {
        return -1;
    }
    for (size_t i = first.bigInt.size(); i > 0; i--) {
        if (first.bigInt[i - 1] < second.bigInt[i - 1]) {
            return 1;
        }
        else if (first.bigInt[i - 1] > second.bigInt[i - 1]) {
            return -1;
        }
    }
    return 0;
}

bool TBigInt::operator<(const TBigInt& other) const {
    return (Compare(*this, other) == 1 ? true : false);
}

bool TBigInt::operator>(const TBigInt& other) const {
    return (Compare(*this, other) == -1 ? true : false);
}

bool TBigInt::operator==(const TBigInt& other) const {
    return (Compare(*this, other) == 0 ? true : false);
}

std::ostream& operator<<(std::ostream& out, TBigInt num) {
    if (num.bigInt.size() == 0) {
        out << 0;
    } else {
        out << num.GetDigit(num.bigInt.size() - 1);
        for (int i = num.bigInt.size() - 2; i >= 0; --i) {
            out << std::setfill('0') << std::setw(DIGIT_LENGTH) << num.GetDigit(i);
        }
    }
    return out;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    TBigInt zero(0), one(1);
    std::string firstOp, secondOp;
    char s;
    while (std::cin >> firstOp >> secondOp >> s) {
        TBigInt first(firstOp);
        TBigInt second(secondOp);
        if (s == '+') {
            std::cout << first + second << "\n";
        } else if (s == '-') {
            try {
                std::cout << first - second << "\n";
            }
            catch (std::logic_error& e) {
                std::cout << e.what() << "\n";
            }
        } else if (s == '*') {
            std::cout << first * second << "\n";
        } else if (s == '/') {
            try {
                std::cout << first / second << "\n";
            }
            catch (std::logic_error& e) {
                std::cout << e.what() << "\n";
            }
        } else if (s == '^') {
            try {
                std::cout << first.Pow(second) << "\n";
            } 
            catch (std::logic_error& e) {
                std::cout << e.what() << "\n";
            }
        } else if (s == '<') {
            std::cout << (first < second ? "true" : "false") << "\n";
        } else if (s == '>') {
            std::cout << (first > second ? "true" : "false") << "\n";
        } else if (s == '=') {
            std::cout << (first == second ? "true" : "false") << "\n";
        } else {
            std::cout << "Error\n";
        }
    }
}