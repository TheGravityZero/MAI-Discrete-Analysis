#include <iostream>
#include <fstream>
#include "bst.hpp"
#include <string.h>

// Константа, задающая максимальную длину ключа.
const uint64_t SIZE_KEY = 257;

// Вычисляет длину ключа в узле
int Sizekey(bst::TreeNode* node){
    size_t i = 0;
    while(node->key[i] != '\0')
        i++;
    return i;
}

// Сохранение в файл
bool Save(FILE* file, bst::TreeNode* node){
    if(node == nullptr){
        return true;    
    }
    int size = Sizekey(node);
    int balance = node->height;
    if(!fwrite(&size,sizeof(int),1,file))
        return false;
    if(!fwrite(node->key,sizeof(char),SIZE_KEY,file))
        return false;
    if(!fwrite(&node->value,sizeof(node->value),1,file))
        return false;
    if(!fwrite(&balance,sizeof(int),1,file))
        return false;
    bool hasleft = node->left != nullptr;
    bool hasright= node->right != nullptr;
    if(!fwrite(&hasleft, sizeof(bool),1,file))
        return false;
    if(!fwrite(&hasright, sizeof(bool),1,file))
        return false;

    if(hasleft)
        Save(file,node->left);
    if(hasright)
        Save(file,node->right);
    return true;
}

// Загрузка дерева из файла
bst::TreeNode* Load(FILE* file, bst::TreeNode* node){
    char* key = new char[SIZE_KEY];
    for(uint64_t i = 0; i < SIZE_KEY; ++i)
        key[i] = '\0';
    int size = 0; 
    uint64_t val = 0;
    int balance = 0;
    if (!fread(&size,sizeof(int),1,file))
        return nullptr;
    else if(!fread(key,sizeof(char),SIZE_KEY,file))
        return nullptr;
    else if(!fread(&val,sizeof(val),1,file))
        return nullptr;
    else if(!fread(&balance,sizeof(int),1,file))
        return nullptr;
//key[size] = '\0';
    node = new bst::TreeNode(key, val, balance);
    delete[] key;

    bool hasleft = false;
    bool hasright= false;
    fread(&hasleft, sizeof(bool),1,file);
    fread(&hasright, sizeof(bool),1,file);
    if(hasleft){
        node->left = Load(file, node->left);
        if(node->left != nullptr)
            node->left->parent = node;
    }
    if(hasright){
        node->right = Load(file, node->right);
        if(node->right != nullptr)
            node->right->parent = node;
    }
    return node;
}

// Удаление всего дерева
void DeleteTree(bst::TreeNode* node){
    if (node != nullptr){
        if(node->left != nullptr)
            DeleteTree(node->left);
        if(node->right != nullptr)
            DeleteTree(node->right);
        delete node;
    }
}


int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    // Корень дерева
    bst::Tree root;
    // Ключ
    char* key = new char[SIZE_KEY];
    // Значение
    uint64_t value;
    // Выбор действия.
    char* action = new char[SIZE_KEY];
    // Обнуляем ключ и действие.
    for(uint64_t i = 0; i < SIZE_KEY; ++i){
        action[i] = '\0';
        key[i] = '\0';
    }
    while( std::cin >> action ){
        // Операция добавления пары ключ-значение в AVL-дерево
        //print_Tree(root.root,0);
        if( action[0] == '+' ) {
            std::cin >> key;
            std::cin >> value;
            // Переводим ключ в нижний регистр.
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                if(key[i] == '\0')
                    break;
                key[i] = tolower(key[i]);
            }
            root.Insert( key, value );
            //print_Tree(root.root,0);
            // Обнуляем ключ и действие.
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                action[i] = '\0';
                key[i] = '\0';
            }
        } 
        // Операция удаление пары из дерева
        else if( action[0] == '-' ){
            std::cin >> key;
            // Переводим ключ в нижний регистр.
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                if(key[i] == '\0')
                    break;
                key[i] = tolower(key[i]);
            }
            root.Delete(key);
            //print_Tree(root.root,0);
            // Обнуляем ключ и действие.
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                action[i] = '\0';
                key[i] = '\0';
            }
        }
        else if(action[0] == '!'){
            std::cin >> action;
            //print_Tree(root.root,0);
            if(!strcmp(action, "Save")){
                //Запись в файл
                std::cin >> key;
                FILE* file = fopen(key, "wb");
                if (file == NULL){
                    std::cout << "ERROR: Couldn't create file\n";
                    continue;
                }
                if(root.root == nullptr){
                    std::cout << "OK\n";    
                    fclose(file);
                    continue; 
                }
                if(!Save(file, root.root)){
                    std::cout << "ERROR: Couldn't create file\n";    
                    fclose(file);
                    continue;                
                }
                std::cout << "OK\n";
                fclose(file);
                continue;
            }
            else if(!strcmp(action, "Load")){
                //Загрузка файла в программу
                std::cin >> key;
                FILE* file = fopen(key, "rb");
                if (file == NULL){
                    std::cout << "ERROR: Couldn't load file\n";
                    continue;
                }
                //print_Tree(root.root,0);
                fseek(file,0,SEEK_END);
                int pos = ftell(file);
                if(pos == 0){
                    DeleteTree(root.root);
                    root.root = nullptr;
                    std::cout << "OK\n";
                    fclose(file);
                    continue;      
                }
                fseek(file,0,SEEK_SET);
                bst::TreeNode* node = Load(file, nullptr);
                if(node == nullptr ){
                    std::cout << "ERROR: Couldn't load file\n";
                    fclose(file);
                    continue;
                }
                DeleteTree(root.root);
                root.root = node;
                std::cout << "OK\n";
                fclose(file);
                continue;
            }
            else{
                std::cout << "Incorrect enter!\n";                
                continue;
            }

        }
        // поиск.
        else{
            // В качестве ключа выступает тут action.
            // Переводим ключ в нижний регистр.      
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                if(action[i] == '\0')
                    break;
                action[i] = tolower(action[i]);
            }
            root.Search( action );
            // Обнуляем ключ и действие.
            for(uint64_t i = 0; i < SIZE_KEY; ++i){
                action[i] = '\0';
                key[i] = '\0';
            }
        }
    }
    delete[] key;
    delete[] action;
    //print_Tree(root.root,0);
    DeleteTree(root.root);
    return 0;
}
