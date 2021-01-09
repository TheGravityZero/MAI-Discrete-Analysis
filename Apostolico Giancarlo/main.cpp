#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cctype>
#include "preprocessing.hpp"
#include "search.hpp"


int main() {
    // Используется для скорости чтения
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string pattern, input, word;
    // Получаем первую строку паттрена
    std::getline(std::cin, input);
    // удаляем перенос корретки
    if (input.back() == '\n') {
        input.pop_back();
    }
    // Переводим в нижний регистр
    std::for_each(input.begin(), input.end(), [](char &c) {
        c = std::tolower(c);
    });
    // Использование как поток данных строку
    std::stringstream patternSS(input);
    int wordsInPattern = 0;
    while (patternSS >> word) {
        pattern += word + " ";
        wordsInPattern++;
    }
    // Удаляем последний пробел
    if (!pattern.empty()) {
        pattern.pop_back();    
    }

    std::string text;
    std::vector<std::vector<int>> info;

    int lineCnt = 1, wordCnt = 1, endWord = 0, startWord = 0;
    // Построчно собираем информацию о словах теста и форматируем текст
    while (std::getline(std::cin, input)) {
        bool first = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == ' ') {
                // Пропускаем пробелы после добавления информации о слове в таблицу info
                if (first) {
                    continue;
                } else {
                    /* В таблицу с информацией о тексте помещаем номер строки, номер, слова,
                    позиции начала и конца слова.*/
                    info.push_back(std::move(std::vector<int>{lineCnt, wordCnt, endWord - 1, startWord}));
                    text += " ";
                    endWord++;
                    startWord = endWord;
                    first = true;
                    wordCnt++;
                }
            } else {
                first = false;
                endWord++;
                text += std::tolower(input[i]);
                // Если мы дошли до конца строки, то добавляем информацию о слове в таблицу info.
                if (i == input.size() - 1) {
                    info.push_back(std::move(std::vector<int>{lineCnt, wordCnt, endWord - 1, startWord}));
                    text += " ";
                    endWord++;
                    startWord = endWord;
                }
            }
        }
        lineCnt++;
        wordCnt = 1;
    }

    if (!text.empty()) {
        text.pop_back();
    }

    std::vector<int> nFunction(pattern.size()), LFunction, lFunction;
    std::vector<std::vector<int>> rFunction(27);

    Preprocessing(nFunction, LFunction, lFunction, rFunction, pattern);
    Search(text, pattern, info, nFunction, LFunction, lFunction, rFunction , wordsInPattern);

    return 0;
}
