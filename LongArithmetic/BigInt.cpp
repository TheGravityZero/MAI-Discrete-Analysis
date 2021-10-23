
#include <vector>
#include <string>
#include "BigInt.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>


TBigInt ZERO(0);
TBigInt ONE(1);
TBigInt TWO(2);


std::string Expand(std::string& str){
    std::string tmp(str.size(), '\0');
    for (int i = 0, j = str.size() - 1; i < static_cast<int>(str.size()); ++i, --j){
        tmp[i] = str[j];
    }
    return tmp;
}

void TBigInt::DeleteZeros()
{
    while (bigNum.size() > 1 && !bigNum.back())
        bigNum.pop_back();
}


TBigInt::TBigInt() = default;

TBigInt::TBigInt(std::string& str){
    if(str[0] == '0'){
        int i = 1;
        for (;str[i] == '0'; ++i);
        str = (i == (int) str.size()) ? "0" : str.substr(i);
    }
    bigNum.clear();
    for (int i = str.size() - 1; i >= 0; i -= BUCKET) {
        int start = i - BUCKET + 1;
        start = (start < 0) ? 0 : start;
        int end = i - start + 1;
        bigNum.push_back(stoi(str.substr(start, end)));
    }
}


TBigInt::TBigInt(int num) {
    do{
        this->bigNum.push_back(num % BASE);
        num /= BASE;
    } while (num != 0);
}


TBigInt::~TBigInt(){

}

TBigInt TBigInt::operator+(const TBigInt &elem){
    TBigInt res;
    int carry = 0;
    for (int i = 0; i < static_cast<int>(std::max(bigNum.size(), elem.bigNum.size())) || carry; ++i) {
        int fst = i < static_cast<int>(bigNum.size()) ? bigNum[i] : 0;
        int sec = i < static_cast<int>(elem.bigNum.size()) ? elem.bigNum[i] : 0;
        res.bigNum.push_back(fst + sec + carry);
        carry = res.bigNum.back() >= BASE;
        if (carry)
            res.bigNum.back() -= BASE;
    }
    res.DeleteZeros();
    return res;
}
TBigInt TBigInt::operator-(const TBigInt& elem){
    TBigInt res;
    int carry = 0;
    for (int i = 0; i < (int) bigNum.size() || carry; ++i) {
        int fst = i < static_cast<int>(bigNum.size()) ? bigNum[i] : 0;
        int sec = i < static_cast<int>(elem.bigNum.size()) ? elem.bigNum[i] : 0;
        res.bigNum.push_back(fst - sec - carry);
        carry = res.bigNum.back() < 0;
        if (carry)
            res.bigNum.back() += BASE;
    }
    res.DeleteZeros();
    return res;
}

TBigInt TBigInt::operator*(const TBigInt &elem){
    TBigInt res;
    int size1 = static_cast<int>(bigNum.size());
    int size2 = static_cast<int>(elem.bigNum.size());
    res.bigNum.resize(size1 + size2);
    for (int i = 0; i < size1; ++i) {
        int carry = 0;
        for (int j = 0; j < size2 || carry; ++j) {
            int snd = j < size2 ? elem.bigNum[j] : 0;
            res.bigNum[i + j] += bigNum[i] * snd + carry;
            carry = res.bigNum[i + j] / BASE;
            res.bigNum[i + j] -= carry * BASE;
        }
    }
    res.DeleteZeros();
    return res;
}
/*void FFT(std::vector<std::complex<double>>& a, bool invert) {
	
    int n = (int) a.size();
	
    if (n == 1){
        return;
    }
	std::vector<std::complex<double>> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	FFT (a0, invert);
	FFT (a1, invert);

	double ang = 2*PI/n * (invert ? -1 : 1);
	std::complex<double> w(1),  wn (cos(ang), sin(ang));
	for (int i=0; i < n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

void Multiply(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& res) {
	std::vector<std::complex<double>> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < std::max(a.size(), b.size()))
        n = n * 2;
	n *= 2;
	fa.resize (n),  fb.resize (n);
	FFT(fa, false);
    FFT(fb, false);
	for (size_t i=0; i < n; ++i)
		fa[i] *= fb[i];
	FFT(fa, true);
	res.resize(n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);
    
    int carry = 0;
    for (int i = 0; i < (int) n; ++i) {
        res[i] += carry;
        carry = res[i] / BASE;
        res[i] %= BASE;
    }
}*/

TBigInt TBigInt::operator/(const TBigInt &elem){
    TBigInt res;
    TBigInt q = TBigInt(0);
    res.bigNum.resize(bigNum.size());
    for (int i = (int) bigNum.size() - 1; i >= 0; --i) {
        q.bigNum.insert(q.bigNum.begin(), bigNum[i]);
        if (!q.bigNum.back())
            q.bigNum.pop_back();
        int x = 0, l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            TBigInt cur = TBigInt(m) * elem;
            if ((cur < q) || (cur == q)) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        res.bigNum[i] = x;
        q = q - TBigInt(x) * elem;
    }
    res.DeleteZeros();
    return res;
}

TBigInt& TBigInt::operator/=(const int& t){
    for(int i = 0; i < (int) this->bigNum.size(); ++i){
        this->bigNum[i] = this->bigNum[i] / t;
    }
    return *this;
}

TBigInt TBigInt::Power(TBigInt& n){
    TBigInt res(1);
    TBigInt tmp = TBigInt(0);
    while (!(n == tmp)) {
        if (n.bigNum[0] % 2){
            res = res * (*this);
            n = n - ONE;
        }else{
            (*this) = (*this) * (*this);
            n = n / TWO;
        }
    }
    return res;
}


bool TBigInt::operator<(const TBigInt &elem) const
{
    if (bigNum.size() != elem.bigNum.size())
        return bigNum.size() < elem.bigNum.size();
    return std::lexicographical_compare(bigNum.rbegin(), bigNum.rend(), elem.bigNum.rbegin(), elem.bigNum.rend());
}

bool TBigInt::operator>(const TBigInt &elem) const
{
    if (bigNum.size() != elem.bigNum.size())
        return bigNum.size() > elem.bigNum.size();
    return std::lexicographical_compare(elem.bigNum.rbegin(), elem.bigNum.rend(), bigNum.rbegin(), bigNum.rend());
}

bool TBigInt::operator==(const TBigInt& elem) const{
    return this->bigNum == elem.bigNum;
}




std::ostream& operator<<(std::ostream& os, const TBigInt& num){
    if (num.bigNum.empty())
        return os;
    else {
            os << num.bigNum.back();
            // следующие числа нам нужно печатать группами по BASE
            // поэтому сохраним текущий символ-заполнитель, в конце восстанавливаем
            char old_fill = os.fill('0');
            for (long long i = static_cast<long long>(num.bigNum.size()) - 2; i >= 0; --i) {
                    os << std::setfill('0') << std::setw(BUCKET) << num.bigNum[i];
            }

            os.fill(old_fill);
    }
        return os;
}