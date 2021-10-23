#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>

const int BASE = 10000;
const int BUCKET = 4;
const double PI = acos(-1);

class TBigInt{
private:
    std::vector<int> bigNum;
    size_t count;
    size_t size;
public:
    // Constructor
    TBigInt(std::string& str);
    TBigInt();
    TBigInt(int num);
    // Destructor
    ~TBigInt();
    // IO funсtion
    TBigInt operator+(const TBigInt&);
    TBigInt operator-(const TBigInt&);
    TBigInt operator*(const TBigInt&);
    TBigInt operator/(const TBigInt&);
    TBigInt Power(TBigInt& r);
    bool operator>(const TBigInt&) const;
    bool operator<(const TBigInt&) const;
    bool operator==(const TBigInt&) const;
    TBigInt& operator/=(const int&);
    friend std::ostream& operator<<(std::ostream& os, const TBigInt& num);
    friend std::string Expand(std::string& str);
  //  friend void Multiply(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& res);
//    friend void FFT(std::vector<std::complex<double>>&a, bool invert);
    TBigInt operator*=(const TBigInt &elem);
    void DeleteZeros();
};

