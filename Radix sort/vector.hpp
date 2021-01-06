#pragma once
#include <iostream>

namespace NVector{
    template <class T>
    class  TVector{
    public:
        TVector();
        TVector(unsigned int size);
        TVector(unsigned int size, const T & initial);
        int Capacity() const;
        int Size() const;
        bool Empty() const;  
        T* Begin();
        T* End();
        T& Front() const;
        T& Back() const;
        void Reserve(unsigned int size);
        void  Push_back(T const &value);
        void Pop_back();
        void Resize(unsigned int size);
        T& operator[](unsigned int index);
        TVector<T>& operator=(const TVector<T>& v);   
        ~TVector();
        void clear();
    private:
        unsigned int my_size;
        unsigned int my_capacity;
        T* buffer;
    };
    template<class T>    
    TVector<T>::TVector(){
        my_size  = 0;
        my_capacity = 10;
        buffer = new T[10];
    }
    template<class T>   
    TVector<T>::TVector(unsigned int size){
        my_size = size;
        my_capacity = size*2;
        buffer = new T[my_capacity];
    }
    template<class T>   
    TVector<T>::TVector(unsigned int size, const T & initial){
        my_size = size;
        my_capacity = size*2;
        buffer = new T[my_capacity];
        for (unsigned int i = 0; i < size; i++)
            buffer[i] = initial;    
    }
    template<class T>   
    int TVector<T>::Capacity() const{return my_capacity;}
    template<class T>   
    int TVector<T>::Size() const{return my_size;}
    template<class T>   
    bool TVector<T>::Empty() const {return !my_size;}
    template<class T>   
    T* TVector<T>::Begin(){
        if(my_size > 0)
            return buffer;
        std::cout << "У вас 0 элементов в векторе\n";
        exit(1);
    }
    template<class T>   
    T* TVector<T>::End(){
        if(my_size > 0)
            return &buffer[my_size];
        std::cout << "У вас 0 элементов в векторе\n";
        exit(1);
    }
    template<class T>   
    T& TVector<T>::Front() const{
        if(my_size > 0)
            return buffer[0];
        std::cout << "У вас 0 элементов в векторе\n";
        exit(1);
    }
    template<class T>   
    T& TVector<T>::Back() const{
        if(my_size > 0)
            return buffer[my_size-1];
        std::cout << "У вас 0 элементов в векторе\n";
        exit(1);
    }
    template<class T>       
    void TVector<T>::Reserve(unsigned int size){
        if(my_size > 0){
            T* newBuffer = new T[size*2];
            for(unsigned int i = 0; i < my_capacity; ++i){
                newBuffer[i] = buffer[i];
            }
            delete[] buffer;
            buffer = newBuffer;
            my_capacity = 2 * size;
            my_size = size;
        }
        else{
            std::cout << "У вас 0 элементов в векторе\n";
            exit(1);
        }
    }
    template<class T>
    void  TVector<T>::Push_back(T const &value){
            if((my_size < my_capacity) && (my_capacity > 0)){
            // Сначала присваивает присваивает значение value buffer[my_size], потом инкрементирует mysize.
            buffer[my_size++] = value;  
        }
        else{
            TVector<T>::Reserve(my_size);
            buffer[my_size++] = value;
        }
    }
    template<class T>  
    void TVector<T>::Pop_back(){my_size--;}
    template<class T>
    void TVector<T>::Resize(unsigned int size){
        TVector<T>::Reserve(size);
    }

    template<class T>   
    T& TVector<T>::operator[](unsigned int index){
            return buffer[index];
    }

    template<class T>   
    TVector<T>& TVector<T>::operator=(const TVector<T>& v){
        delete[] buffer;
        my_size = v.my_size;
        my_capacity = v.my_capacity;
        buffer = new T[my_capacity];
        for (unsigned int i = 0; i < my_capacity; i++)
            buffer[i] = v.buffer[i];
        return *this;
    }       
    template<class T>   
    TVector<T>::~TVector(){
            delete[] buffer;
    }
    template<class T>   
    void TVector<T>::clear(){
        my_capacity = 0;
        my_size = 0;
        delete[] buffer;
    }
} // namespace vector