#pragma once
#include <string>
#include <vector>
#include <iostream>

void Search(const std::string &text, const std::string &pattern, const std::vector<std::vector<int>> &info,
            std::vector<int> &n, std::vector<int> &bigL, std::vector<int> &littleL, std::vector<std::vector<int>> &r, int wordsInPattern) {
    // фиксируем позицию последнего символа паттерна
    int k = pattern.size() - 1;
    // массив для позиции вхождения паттерна в текст
    std::vector<int> entry;
    // массив для подсчёта того, сколько символов совпадёт, если приложить к позиции текста конец паттерна
    std::vector<int> m(text.size());
    while (k < text.size()) {
        // i отвечает за позицию в паттерне
        int i = pattern.size() - 1;
        // h отвечает за позицию в тексте
        int h = k;
        while (true) {
            // если m[h] неопределён или равен 0
            if (m[h] == 0) {
                // если сравниваемые сисволы совпадают
                if (text[h] == pattern[i]) {
                    // если дошли до начала паттерна
                    if (i == 0) {
                        entry.push_back(k); // сообщаем о вхождении
                        m[k] = pattern.size(); // подстрока совпадает с образцом
                        // такой сдвиг, что префикс образца должен совпасть с суффиксом
                        if (pattern.size() > 2) {
                            k += pattern.size() - littleL[1];
                        } else {
                            k++;
                        }
                        break;
                    } else { // если  i > 0 сравниваем следующие символы
                        h--;
                        i--;
                    }
                } else { // несовпадение
                    m[k] = k - h;
                    // нахождение хорошего суффикса
                    int maxSuff;
                    if (i == pattern.size() - 1) { // если не совпал последний символ
                        maxSuff = 1;
                    } else {
                        if (bigL[i + 1] > 0) {
                            maxSuff = pattern.size() - bigL[i + 1] - 1;
                        } else {
                            maxSuff = pattern.size() - littleL[i + 1];
                        }
                    }
                    // нахождение плохого символа
                    int maxSymb = 1;
                    bool badSymbFound = false;
                    if (text[h] == ' ') { // если несовпадение в символе ' '
                        for (int j = 0; j < r[r.size() - 1].size(); j++) {
                            //если найдётся такая позиция ' ' в паттерне меньшая i 
                            if (r[r.size() - 1][j] < i) {
                                maxSymb = std::max(1, i - r[r.size() - 1][j]);
                                badSymbFound = true;
                                break;
                            }
                        }
                    }
                    if (text[h] >= 97 && text[h] <= 122) { // если несовпадение в букве
                        for (int j = 0; j < r[text[h] - 97].size(); j++) {
                            // находим слово левее i  позиции, в котором встреается наша буква
                            if (r[text[h] - 97][j] < i) {
                                maxSymb = std::max(1, i - r[text[h] - 97][j]);
                                badSymbFound = true;
                                break;
                            }
                        }
                    }
                    if (!badSymbFound) { // если символа строки нет до позиции i, то сдвигаем за этот символ
                        maxSymb = i + 1;
                    }

                    k += std::max(maxSuff, maxSymb);
                    break; // конец фазы
                }
            // Если число сиволов при наложении конца паттерна на позицию h меньше,
            // чем число символов совпавшее с суфиксом c позиции i.
            } else if (m[h] < n[i]) {
                i -= m[h];
            /*
            Если число сиволов при наложении конца паттерна на позицию h больше или равно,
            чем число символов совпавшее с суфиксом c позиции i и i меньше,
            чем  число символов совпавшее с суфиксом c позиции i.
            */
            } else if (m[h] >= n[i] && n[i] >= i) {
                entry.push_back(k); // сообщить о вхождении
                m[k] = k - h; 
                // такой сдвиг, что префикс образца должен совпасть с суффиксом
                if (pattern.size() > 2) {
                    k += pattern.size() - littleL[1];
                } else {
                    k++;
                }
                break; // конец фазы
            } else if (m[h] > n[i] && n[i] < i) {
                m[k] = k - h;
                // несовпадение в i - n[i]
                // нахождение хорошего суффикса
                int maxSuff;
                if (i - n[i] == pattern.size() - 1) { // если не совпал первый символ
                    maxSuff = 1;
                } else {
                    if (bigL[i - n[i] + 1] > 0) {
                        maxSuff = pattern.size() - bigL[i - n[i] + 1] - 1;
                    } else {
                        maxSuff = pattern.size() - littleL[i - n[i] + 1];
                    }
                }
                // нахождение плохого символа
                int maxSymb = 1;
                bool badSymbFound = false;
                if (text[h - n[i]] == ' ') { // если несовпадение в символе ' '
                    for (int j = 0; j < r[r.size() - 1].size(); j++) {
                        if (r[r.size() - 1][j] < i - n[i]) {
                            maxSymb = std::max(1, i - n[i] - r[r.size() - 1][j]);
                            badSymbFound = true;
                            break;
                        }
                    }
                }
                if (text[h - n[i]] >= 97 && text[h - n[i]] <= 122) { // если несовпадение в букве
                    for (int j = 0; j < r[text[h - n[i]] - 97].size(); j++) {
                        if (r[text[h - n[i]] - 97][j] < i - n[i]) {
                            maxSymb = std::max(1, i - n[i] - r[text[h - n[i]] - 97][j]);
                            badSymbFound = true;
                            break;
                        }
                    }
                }
                if (!badSymbFound) { // если символа строки нет до позиции i, то сдвигаем за этот символ
                    maxSymb = i - n[i] + 1;
                }

                k += std::max(maxSuff, maxSymb);
                break; // конец фазы
            } else if (m[h] == n[i] && n[i] < i) {
                i -= m[h];
                h -= m[h];
            }
        }
    }

    for (int infCnt = 0, entryCnt = 0; entryCnt < entry.size(); infCnt++) {
        // Если образ лежит в промежутке от начала слова до конца слова
        if (info[infCnt][3] <= entry[entryCnt] && info[infCnt][2] >= entry[entryCnt]) {
            std::cout << info[infCnt - wordsInPattern + 1][0] << ", " << info[infCnt - wordsInPattern + 1][1] << "\n";
            entryCnt++;
            infCnt--;
        }
    }
}