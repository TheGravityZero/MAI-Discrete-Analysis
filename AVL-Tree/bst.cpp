/* ПРИМЕЧАНИЯ!
1) Когда мы сравниваем строку с ключём узла, мы делаем это следующим оброзом:
    if (*root == key) ...
Такая реалицая является следствием перегрузки операторов > < ==
2)
*/

#include <iostream>
#include "bst.hpp"

namespace bst {

bool TreeNode::operator==(const char* key) {
    int i = 0;
    while((key[i] == this->key[i]) && (key[i] != '\0') && (this->key[i] != '\0'))
        i++;
    if(key[i] == this->key[i])
        return true;
    return false;
}

bool TreeNode::operator>(const char* key) {
    int i = 0;
    while(key[i] != '\0'){
        if(this->key[i] == '\0'){
            return false;
        }
        if(key[i] < this->key[i]){
            return true;
        }
        if(key[i] > this->key[i]){
            return false;
        }
        i++;
    }
    if(this->key[i] == '\0'){
        return false;
    }
    return true;
}

bool TreeNode::operator<(const char* key) {
    int i = 0;
    while(key[i] != '\0'){
        if(this->key[i] == '\0'){
            return true;
        }
        if(key[i] < this->key[i]){
            return false;
        }
        if(key[i] > this->key[i]){
            return true;
        }
        i++;
    }
    if(this->key[i] == '\0'){
        return false;
    }
    return false;
}

bool Is_leaf(TreeNode* node){
    if((node->right == nullptr) && (node->left == nullptr))
        return true;
    return false;
}


void print_Tree(TreeNode* p,int level){
    if(p){
        print_Tree(p->right,level + 1);
        for(int i = 0;i < level;i++) 
            std::cout<<"   ";
        std::cout << p->key << p->height  << '\n';
        print_Tree(p->left,level + 1);
    }
}

void Tree::Rebalance(TreeNode* node){
if (node->height < 0){
    if (node->right->height > 0){
        RotateRight(node->right);
        RotateLeft(node);
    }
    else
        RotateLeft(node);
}
else if (node->height > 0){
    if (node->left->height < 0){
        RotateLeft(node->left);
        RotateRight(node);
    }
    else
        RotateRight(node);
}
}
void Tree::UpdateBalance(TreeNode* node){
    if (node->height > 1 || node->height < -1){
        Rebalance(node);
        if(node->parent->height != 0){
            UpdateBalanceDelete(node->parent);
        }
        return;
    }
    if (node->parent != nullptr){
        if (node->parent->left == node){
                node->parent->height += 1;
        }
        else if (node->parent->right == node){
                node->parent->height -= 1;
        }
        if (node->parent->height != 0)
            UpdateBalance(node->parent);
    }
}

void Tree::UpdateBalanceDelete(TreeNode* node){
    if (node->height > 1 || node->height < -1){
        Rebalance(node);
        if(node->parent->height == 0){
            UpdateBalanceDelete(node->parent);
        }
        return;
    }
    if (node->parent != nullptr){
        if (node->parent->left == node){
                node->parent->height -= 1;
        }
        else if (node->parent->right == node){
                node->parent->height += 1;
        }
        if ((node->parent->height == -1) || (node->parent->height == 1))
            return;
        else    
            UpdateBalanceDelete(node->parent);
    }
}

void Tree::Insert( char* key, uint64_t value ) {
    // Если дерево пустое, тогда создадим корень.
    if( root == nullptr ) {
        root = new TreeNode( key, value, 0);
        std::cout << "OK\n";
        return;
    }
    // Если у нас элемент с таким ключём в коне дерева.
    if(*root == key){
        std::cout << "Exist\n";
        return;
    }
    // Иначе - добавим в дерево.
    if(  *root > key && root->left == nullptr ) {
        root->left = new TreeNode( key, value, 0);
        root->left->parent = root;
        UpdateBalance(root->left);
        std::cout << "OK\n";
        return;
    }

    if( *root < key && root->right == nullptr ) {
        root->right = new TreeNode( key, value, 0);
        root->right->parent = root;
        UpdateBalance(root->right);
        std::cout << "OK\n";
        return;
    }
    Insert( key, value, *root > key ? root->left : root->right);
}

void Tree::Insert( char* key, uint64_t value, TreeNode *node) {
    
    if( *node == key ) {
        std::cout << "Exist\n";
        return;
    }

    if( *node > key && node->left == nullptr ) {
        node->left = new TreeNode( key, value, 0);
        node->left->parent = node;
        UpdateBalance(node->left);
        std::cout << "OK\n";
        return;
    }

    if( *node < key && node->right == nullptr ) {
        node->right = new TreeNode( key, value, 0 );
        node->right->parent = node;
        UpdateBalance(node->right);
        std::cout << "OK\n";
        return;
    }
    Insert( key, value,  *node > key ? node->left : node->right);
}

TreeNode* Tree::Search( char* key ) {
    TreeNode* res = Search( key, root );
    return res;
}

TreeNode* Tree::Search( char* key, TreeNode *node ) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord\n";
        return nullptr;
    }

    if( *node == key ) {
        std::cout << "OK: " << node->value << '\n';
        return node;
    }
    return Search( key,  *node > key ? node->left : node->right );
}

TreeNode* Tree::SearchForDelete( char* key ) {
    TreeNode* res = SearchForDelete( key, root );
    return res;
}

TreeNode* Tree::SearchForDelete( char* key, TreeNode *node ) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord\n";
        return nullptr;
    }

    if( *node == key ) {
        std::cout << "OK\n";
        return node;
    }
    return SearchForDelete( key,  *node > key ? node->left : node->right );
    //return node;
}


void Tree::Delete(char* key){
    TreeNode* foundNode = SearchForDelete(key);
    if(!foundNode){
        return;
    }
    Delete(foundNode);
}

//Копирует строки узов.
bool Copykey(TreeNode* fst, TreeNode* scd){
    int i = 0;
    while(scd->key[i] != '\0'){
        fst->key[i] = scd->key[i];
        i++;
    }
    fst->key[i] = scd->key[i];
    return true;
}

// Функция удаления узла в дереве.
void Tree::Delete(TreeNode* node){
    // Если у узла один ребёнок
    if((node->left != nullptr) && (node->right == nullptr)){
        // Если у нас один ребёнок и узел корень дерева
        if(node == this->root){
            node = node->left;
            Copykey(this->root, node);
            this->root->value = node->value;
            UpdateBalanceDelete(node);
            this->root->left = nullptr;
            delete node;
            return;   
        }
        if((node->parent != nullptr)&&(node->parent->left == node)){
            node->parent->left = node->left;
            node->left->parent = node->parent;
            UpdateBalanceDelete(node->left);
            delete node;
            return;
        } else if ((node->parent != nullptr)&&(node->parent->right == node)){
            node->parent->right = node->left;
            node->left->parent = node->parent;
            UpdateBalanceDelete(node->left);
            delete node;
            return;
        }
    }
    if((node->left == nullptr) && (node->right != nullptr)){
        // Если у нас один ребёнок и узел корень дерева
        if(node == this->root){
            node = node->right;
            Copykey(this->root, node);
            this->root->value = node->value;
            UpdateBalanceDelete(node);
            this->root->right = nullptr;
            delete node;
            return;   
        }
        if((node->parent != nullptr)&&(node->parent->left == node)){
            node->parent->left = node->right;
            node->right->parent = node->parent;
            UpdateBalanceDelete(node->right);
            delete node;
            return;

        } else if((node->parent != nullptr)&&(node->parent->right == node)){
            node->parent->right = node->right;
            node->right->parent = node->parent;
            UpdateBalanceDelete(node->right);
            delete node;
            return;
        }
    }
    // Если у узла два ребёнка
    if(node->right != nullptr && node->left != nullptr){
        // Двойной переход необходим, чтобы при нахождении минимального элемента
        // в поддереве мы не потеряли родителя и смогли занулить его ребёнка.
        if(node->right->left != nullptr){
            // Находим минимальный элемент в правом поддереве и заменяем на него удаляемый.
            TreeNode* res = Tree::remove_r(node->right);
            node->value = res->value;
            Copykey(node, res);
            Delete(res);
            return;
        // Иначе если правый ребёнок изначального узла является минимальным, то мы заменяем на него.  
        }else{
            node->value = node->right->value;
            Copykey(node, node->right);
            Delete(node->right);
            return;
        }
    }
    // Если у узла нет детей
    if(node->right == nullptr && node->left == nullptr){
        UpdateBalanceDelete(node);
        if((node->parent != nullptr)&&(node->parent->right == node))
            node->parent->right = nullptr;
        else if((node->parent != nullptr)&&(node->parent->left == node))
            node->parent->left = nullptr;
        if(node == this->root)
            this->root = nullptr;
        delete node;
    }
}


TreeNode* Tree::remove_r(TreeNode* node){
    if(node->left->left == nullptr){
        return  node->left;
    } else{
        return Tree::remove_r(node->left);
    }
}

int min(int& a, int b){
    return a < b ? a : b;
}
int max(int& a, int b){
    return a > b ? a : b;
}

void Tree::RotateRight(TreeNode* node){
    TreeNode* tmp = node->left;
    node->left = tmp->right;
    if (tmp->right != nullptr){
        tmp->right->parent = node;
    }
    tmp->parent = node->parent;
   if(node == this->root){
        this->root = tmp;
    } else{
        if(node->parent->right == node){
            node->parent->right = tmp;
        } else{
            node->parent->left = tmp;
        }
    }
    tmp->right = node;
    node->parent = tmp;
    node->height = node->height - 1 - max(tmp->height, 0);
    tmp->height = tmp->height - 1 + min(node->height, 0);
}

void Tree::RotateLeft(TreeNode* node){
    TreeNode* tmp = node->right;
    node->right = tmp->left;
    if (tmp->left != nullptr){
        tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if(node == this->root){
        this->root = tmp;
    } else{
        if(node->parent->left == node){
            node->parent->left = tmp;
        } else{
            node->parent->right = tmp;
        }
    }
    tmp->left = node;
    node->parent = tmp;
    node->height = node->height + 1 - min(tmp->height, 0);
    tmp->height = tmp->height + 1 + max(node->height, 0);
}

} // namespace bst