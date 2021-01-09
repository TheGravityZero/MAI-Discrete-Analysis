#pragma once
#include <vector>
#include "n_function.hpp"
#include <string>

template<typename T>
std::vector<T> LBigFunction(const std::string &s, std::vector<T> &v) {
    if (s.size() == 0) {
        return v;
    }
    std::vector<T> l(s.size());
    for (int j = 0; j < s.size() - 1; j++) {
        if (v[j] == 0) {
            continue;
        } 
        int i = s.size() - v[j];
        l[i] = j + 1;
    }

    return l;
}

template<typename T>
std::vector<T> LLittleFunction(const std::string &s, std::vector<T> &v) {
    if (s.size() == 0) {
        return v;
    }
    std::vector<T> l(s.size());
    for (int i = s.size() - 1; i >= 0; i--) {
        int j = (s.size() - 1) - i;
        if (v[j] == j + 1) {
            l[i] = j + 1;
        } else {
            if (i == s.size() - 1) {
                l[i] = 0;
            } else {
                l[i] = l[i + 1];
            }
        }
    }
    
    return l;
}

template<typename T>
void RFunction(const std::string &s, std::vector<std::vector<T>> &v) {
    if (s.size() == 0) {
        return;
    }
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ' ') {
            v[v.size() - 1].push_back(i);
        } else {
            v[s[i] - 97].push_back(i);
        }
    } 
}


template<class T>
using Vector = std::vector<T>;
void Preprocessing(Vector<int> &n, Vector<int> &bigL, Vector<int> &littleL,
                   Vector<Vector<int>> &r, const std::string &pattern) {
    NFunction(pattern, n);
    bigL = LBigFunction(pattern, n);
    littleL = LLittleFunction(pattern, n);
    RFunction(pattern, r);
}