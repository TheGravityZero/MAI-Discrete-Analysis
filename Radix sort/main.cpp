#include<iostream>
#include "vector.hpp"
#include <string.h>

struct TPair{
    TPair(){}
    //Вызывается конструктор копирования.
    TPair(char n[], unsigned long long &v){
        // Заполним поле number символом '\0'
        for(int i = 0; i < 20; ++i){
            number[i] = '\0';
        }
        this->value = v;
        for(int i = 0; i < 20; ++i){
            if(n[i] != '\0'){
                this->number[i] = n[i];
            }
            else{
                break;                   
            }
            
        }
        size = strlen(n);
    }
    ~TPair(){}
    unsigned long long value;
    char number[20];
    short size;
};

void Counting_sort (NVector::TVector<TPair>& myData){
    int array[10];
    short k = 1;
    size_t maxLen = 0;
    NVector::TVector<TPair> result(myData.Size());
    //Обнуляем массив-счётчик.
    for(int i = 0; i < 10; ++i){
        array[i] = 0;
    }
    //Находим самый длинный номер
    for(int i = 0; i < myData.Size(); ++i){
        if(strlen(myData[i].number) > maxLen){
            maxLen = strlen(myData[i].number);
        }
    }
    //Выравниваем номера
    for(int i = 0; i < myData.Size(); ++i){
        short tmp = maxLen-strlen(myData[i].number);
            if(tmp > 0){
                for(int z = strlen(myData[i].number) - 1 ; z >= 1; --z){
                    myData[i].number[z+tmp] = myData[i].number[z];
                }
                for(int z = 1; z <= tmp; ++z){
                    myData[i].number[z] = '0';
                }
                
            }
    }
    //Начинаем сортировать по последним 7-ми цифрам номера.
    for(int j = 0; j < 7; ++j){
        //Проходим все номера вектора myData и заполняем массив счётчик.
        for(int l = 0; l < myData.Size(); ++l){
            //Увеличиваем массив-счётчик на единицу по индексу последних цифр номеров.
            array[myData[l].number[strlen(myData[l].number) - k] - 48] += 1;
        }     
        //К каждому элементу массива-счётчика прибавляем левый элемент
        for(int l = 1; l < 10; ++l){
            array[l] += array[l-1];
        }
        for(int l = myData.Size()-1; l >= 0; --l){

            result[array[myData[l].number[strlen(myData[l].number) - k] - '0']-1] = myData[l];
            array[myData[l].number[strlen(myData[l].number) - k] - '0'] -= 1;
        }
        myData = result;
        //Обниление массива счётсчика.
        for(int l = 0; l < 10; ++l){
            array[l] = 0;
        }
        // Переходим ко второй цифре с конца номера и т.д.
        ++k;
    }
    ++k;
    // Начинаем сортировать по коду города.
    for(int j = 0; j < 3; ++j){
        for(int l = 0; l < myData.Size(); ++l){
            //Увеличиваем массив-счётчик на единицу по индексу последних цифр номеров.
            array[myData[l].number[strlen(myData[l].number) - k] - 48] += 1;
        }
        //К каждому элементу массива-счётчика прибавляем левый элемент
        for(int l = 1; l < 10; ++l){
            array[l] += array[l-1];
        }
        for(int l = myData.Size() - 1; l >= 0; --l){
            result[array[myData[l].number[strlen(myData[l].number) - k]-'0']-1] = myData[l];
            array[myData[l].number[strlen(myData[l].number) - k] - '0'] -= 1;
        }
        myData = result; 
        //Обниление массива счётсчика.
        for(int i = 0; i < 10; ++i){
            array[i] = 0;
        }
        ++k;
    }

    //Продолжаем сортировку по коду строны...ФиналОчка
    for(int z = maxLen - 13; z >= 1; --z){
        //Заполняем массив-счётчик
        for(int i = 0; i < myData.Size(); ++i){
            array[myData[i].number[z] - 48] += 1;
        }
        //К каждому элементу массива-счётчика прибавляем левый элемент
        for(int l = 1; l < 10; ++l){
            array[l] += array[l-1];
        }

        for(int i = myData.Size()-1; i >= 0; --i){
                result[array[myData[i].number[z]- 48]-1] = myData[i];
                array[myData[i].number[z]- 48] -= 1;
        }
        myData = result;
        //Обнуление массива счётсчика.
        for(int i = 0; i < 10; ++i){
            array[i] = 0;
        }
    }
}
void DeleteZero(NVector::TVector<TPair>& myData){
    for(int i = 0; i < myData.Size(); ++i){
        short tmp = 1, count = 0;
        while(myData[i].number[tmp] == '0'){
            if(myData[i].size == (strlen(myData[i].number) - count)){
                break;
            }
            count++;
            tmp++;
        }
        if(count > 0){
            for(size_t j = 1; j < strlen(myData[i].number) - count; ++j){
                myData[i].number[j] =  myData[i].number[j+count];
            }
            for(size_t j =  strlen(myData[i].number)- count; j < strlen(myData[i].number); ++j){
                myData[i].number[j] = '\0';
            }
        }
    }
}
int main(){
    unsigned long long value;
    char key[20];
    NVector::TVector<TPair>myData;
    //Заполняем наш массив ключа символами конца строки.
    for(int i = 0; i < 20; ++i){
        key[i] = '\0';
    }
    //Считываем данные из стандартного потока и записываем в вектор.
    while (std::cin >> key >> value){
        myData.Push_back(TPair(key, value));
        
        //Заполняем наш массив символами конца строки, так как работаем с одной областью памяти.
        for(int i = 0; i < 20; ++i){
            key[i] = '\0';
        }
    }
    // Побитовая сорти.
    Counting_sort(myData);
    DeleteZero(myData);
    for (int i = 0; i < myData.Size(); ++i){
        std::cout << myData[i].number << '\t' << myData[i].value << '\n';
    }
    return 0;
}
