#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <algorithm>

template<typename T>
class AVLTree{

private:
    struct Node{
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    void insert(Node*& node, T value); //done
    Node* rotateLeft(Node* node); //done
    Node* rotateRight(Node* node); //done
    int getHeight(Node* node); //done
    int getBalance(Node* node); //done
    void updateHeight(Node* node); //done
    bool search(Node* node, T value) const; //done
    void remove(Node*& node, T value);
    void inorder(Node* node) const;
    void clear(Node* node); //helper for destructor

public:
    AVLTree();
    ~AVLTree();

    void insert(T value); //done
    bool search(T value) const; //done
    void remove(T value);
    void inorder() const;

};

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {};

template <typename T>
AVLTree<T>::~AVLTree(){
    clear(root);
}

template <typename T>
void AVLTree<T>::clear(Node* node){
    if(node){
        clear(node -> left);
        clear(node -> right);
        delete(node);
    }
}

template <typename T>
void AVLTree<T>::insert(T value){
    insert(root, value);
}

template <typename T>
void AVLTree<T>::insert(Node*& node, T value){
    if(node){
        if(value < node -> data){
            insert(node -> left, value);
    }
        else if(value > node -> data){
            insert(node -> right, value);
        }

        updateHeight(node);

        int balance = getBalance(node);

        if(balance > 1 && value < node -> left -> data){ //LL
            node = rotateRight(node);
        }
        else if(balance > 1 && value > node -> left -> data){ //LR
            node -> left = rotateLeft(node -> left);
            node = rotateRight(node);
        }
        else if(balance < -1 && value > node -> right -> data){ //RR
            node = rotateLeft(node);
        }
        else if(balance < -1 && value < node -> right -> data){ //RL
            node -> right = rotateRight(node -> right);
            node = rotateLeft(node);
        }

    }
    else{
        node = new Node(value);
    }
}

template <typename T>
int AVLTree<T>::getHeight(Node* node){
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::getBalance(Node* node){
    return node ? getHeight(node -> left) - getHeight(node -> right ) : 0;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* node){
    Node* y = node;

    Node* x = y -> right;
    Node* T2 = x -> left;

    x -> left = y;
    y -> right = T2;

    //update heights:
    updateHeight(y);
    updateHeight(x);

    return(x);
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* node){
    Node* y = node;

    Node* x = y -> left;
    Node* T1 = x -> right;

    x -> right = y;
    y -> left = T1;

    //update heights:
    updateHeight(y);
    updateHeight(x);

    return x;
}

template <typename T>
void AVLTree<T>::updateHeight(Node* node){ //helper for rotation methods
    node -> height = 1 + std::max(getHeight(node -> left), getHeight(node -> right));
}

template <typename T>
bool AVLTree<T>::search(T value) const{
    return search(root, value);
}

template <typename T>
bool AVLTree<T>::search(Node* node, T value) const{

    if(node == nullptr){
        return false;
    }

    if(value == node -> data){
        return true;
    }
    else if(value < node -> data){
        return search(node -> left, value);
    }
    else if(value > node -> data){
        return search(node -> right, value);
    }
    
    return false;
}

template <typename T>
void AVLTree<T>::remove(T value){
    remove(root, value);
}

template <typename T>
void AVLTree<T>::remove(Node*& node, T value){
    if(!node){
            return;
        }

    if(value < node -> data){
        remove(node -> left, value);
    }
    else if(value > node -> data){
        remove(node -> right, value);
    }
    else if(value == node -> data){

        if(node -> left == nullptr && node -> right == nullptr){ //case 1: no children
            Node* temp = node;
            node = nullptr;
            delete(temp);

        }
        else if(node -> left != nullptr && node -> right == nullptr){ //case 2.1: 1 child, left
            Node* temp = node;
            node = node -> left;
            delete(temp);

        }
        else if(node -> right != nullptr && node -> left == nullptr){ //case 2.2: 1 child, right
            Node* temp = node;
            node = node -> right;
            delete(temp);

        }
        else if(node -> right != nullptr && node -> left != nullptr){ //case 3: 2 children
            Node* temp = node -> right;
            while(temp -> left != nullptr){
                temp = temp -> left;
            }

            Node* successor = temp;
            node -> data = successor -> data;
            remove(node -> right, successor -> data);

        }
    }

    if(!node){
        return;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if(balance > 1){ //Left-heavy
        if(getBalance(node -> left) < 0){ //LR
            node -> left = rotateLeft(node -> left);
            node = rotateRight(node);
        }
        else{ //LL
            node = rotateRight(node);
        }
    }
    else if(balance < -1){
        if(getBalance(node -> right) > 0){ //RL
            node -> right = rotateRight(node -> right);
            node = rotateLeft(node);
        } 
        else{ //RR
            node = rotateLeft(node);
        }
    }
}

template <typename T>
void AVLTree<T>::inorder() const{
    inorder(root);
}

template <typename T>
void AVLTree<T>::inorder(Node* node) const{
    if(node){
        inorder(node -> left);
        std::cout << node -> data << " -> ";
        inorder(node -> right);
    }
}

#endif