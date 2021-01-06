#pragma once

namespace bst {
    
// Константа, задающая максимальную длину ключа.       
const uint64_t SIZE_KEY = 257;

struct TreeNode {
    char* key = new char[SIZE_KEY];
    int  height = 0;
    uint64_t value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode* parent = nullptr;
    //Конструктор копирования.
    TreeNode( char* key, uint64_t value, int height){
      //  this->key = new char[SIZE_KEY];
        for(uint64_t i = 0; i < SIZE_KEY; ++i){
            this->key[i] = '\0';
        }
        // Копируем строку в key.
        for(uint64_t i = 0; i < SIZE_KEY; ++i){
            this->key[i] = key[i];
            if(key[i] == '\0')
                break;
            
        }
       // this->key[0] = *key;
        //this->key[1] = '\0';
        this->value = value;
        this->height = height;
    }
    //Деструктор
    ~TreeNode(){
        delete[] key;
    }
    bool operator==(const char* key);
    bool operator<(const char* key);
    bool operator>(const char* key);
};

class Tree {
public:
    Tree() {}
    ~Tree() {}
    void Insert( char* key, uint64_t value );
    void Delete( char* key);
    TreeNode* Search( char* key );
    TreeNode* root = nullptr;
private:
    void Insert( char* key, uint64_t value, TreeNode* node);
    TreeNode* Search( char* key, TreeNode* node );
    TreeNode* SearchForDelete( char* key, TreeNode *node );
    TreeNode* SearchForDelete( char* key );
    void Delete(TreeNode* node);
    TreeNode* Balance(TreeNode* node);
    TreeNode* remove_l(TreeNode* node);
    TreeNode* remove_r(TreeNode* node);
    void RotateRight(TreeNode* node);
    void RotateLeft(TreeNode* node);
    void Rebalance(TreeNode* node);
    void UpdateBalance(TreeNode* node);
    void UpdateBalanceDelete(TreeNode* node);
    void fixheight(TreeNode* p);
};
void print_Tree(TreeNode* p,int level);
bool Copykey(TreeNode* fst, TreeNode* scd);
int min(int& a, int b);
int max(int& a, int b);
bool Is_leaf(TreeNode* node);

} // namespace bst