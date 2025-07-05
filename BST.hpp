#ifndef BST_HPP
#define BST_HPP

#include <iostream>

template<typename T>
class BST{

private:
    struct Node{
        T data;
        Node* left;
        Node* right;
        Node(T val): data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& current, T value);
    bool search(Node* current, T value) const;
    void inorder(Node* current) const;
    void remove(Node*& current, T value);
    void clear(Node* current); //helper for the destructor

public:
    BST();
    ~BST();

    void insert(T value);
    bool search(T value) const;
    void remove(T value);
    void inorder() const;
};

template <typename T>
BST<T>::BST() : root(nullptr) {} //constructor--> initializes root to nullptr

template <typename T>
BST<T>::~BST() {
    clear(root);
}

template <typename T>
void BST<T>::clear(Node* current){
    if(current){
        clear(current -> left);
        clear(current -> right);
        delete(current);
    }
}

template <typename T>
void BST<T>::insert(T value) {
    insert(root, value);
}

template <typename T>
void BST<T>::insert(Node*& current, T value){
    if(current == nullptr){
        current = new Node(value);
    }
    else if(value < current->data){
        insert(current->left, value);
    }
    else if(value > current->data){
        insert(current->right, value);
    }
}

template <typename T>
bool BST<T>::search(T value) const{
    return BST<T>::search(root, value);
}

template <typename T>
bool BST<T>::search(Node* current, T value) const{
    if(current == nullptr){
        return false;
    }
    else if(value == current->data){
        return true;
    }
    else if(value < current->data){
        return search(current->left, value);
    }
    else if(value > current->data){
        return search(current->right, value);
    }

    return false;
}

template <typename T>
void BST<T>::remove(T value){
    BST<T>::remove(root, value);
}

template <typename T>
void BST<T>::remove(Node*& current, T value){
    if(current == nullptr) return;

    if(value < current->data){
        remove(current->left, value);
    }
    else if(value > current->data){
        remove(current->right, value);
    }
    else if(value == current->data ){
        //casework: 3 cases

        if(current->left == nullptr && current->right == nullptr){ //case 1: no children
            Node* temp = current;
            current = nullptr;
            delete(temp);
        }
        else if(current->right == nullptr){ //case 2.1: 1 child, left
            Node* temp = current;
            current = current->left;
            delete(temp);
        }
        else if(current->left == nullptr){ //case 2.2: 1 child, right
            Node* temp = current;
            current = current->right;
            delete(temp);
        }
        else{ //case 3: 2 children

            Node* successor = current->right;
            while(successor->left != nullptr){
                successor = successor->left;
            }

            current->data = successor->data;
            remove(current->right, successor->data);
            
        }
    }
}

template <typename T>
void BST<T>::inorder() const{
    inorder(root);
    std::cout << "null" << std::endl;
}

template <typename T>
void BST<T>::inorder(Node* current) const{ //for testing
    if(current){
        inorder(current->left);
        std::cout << current->data << " -> ";
        inorder(current->right);
    }
}


#endif