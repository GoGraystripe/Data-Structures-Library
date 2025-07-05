#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <iostream>
#include <algorithm>

enum Color {RED, BLACK};

template<typename T>
class RedBlackTree{

private:
    struct Node{
        T data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(T value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {};

    };

    Node* root;

    void rotateLeft(Node*& node); //done
    void rotateRight(Node*& node); //done
    void fixInsert(Node*& node); //done 
    void remove(Node*& node, T value); //done
    void inorder(Node* node) const;
    void clear(Node* node); //helper for destructor;
    void transplant(Node* u, Node* v); //done
    void fixRemove(Node* x); //done
    bool search(Node* node, T value);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(T value);
    bool search(T value);
    void remove(T value);
    void inorder() const;

};

template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr) {};

template <typename T>
RedBlackTree<T>::~RedBlackTree(){
    clear(root);
}

template <typename T>
void RedBlackTree<T>::clear(Node* node){
    if(node){
        clear(node -> left);
        clear(node -> right);
        delete(node);
    }
}

template <typename T>
void RedBlackTree<T>::insert(T value){
    Node* newNode = new Node(value);
    Node* y = nullptr;
    Node* x = root;

    /* iterate down with x | x is a dummy variable that is just used to loop down | once x becomes a nullptr, its relationship
    to the tree is lost. */

    while(x != nullptr){
        y = x;

        if(value < x -> data){
            x = x -> left;
        }
        else if(value > x -> data){
            x = x -> right;
        }
    }

    newNode -> parent = y;

    if(y == nullptr){
        root = newNode;
    }
    else if(value < y -> data){
        y -> left = newNode;
    }
    else if(value > y -> data){
        y -> right = newNode;
    }

    newNode -> left = nullptr;
    newNode -> right = nullptr;
    newNode -> color = RED;

    fixInsert(newNode);
}

template <typename T>
void RedBlackTree<T>::rotateLeft(Node*& node){
    Node* y = node;
    Node* x = y -> right;
    Node* T1 = x -> left;

    x -> left = y;
    y -> right = T1;

    //update parents:
    x -> parent = y -> parent;
    y -> parent = x;

    if(T1 != nullptr){
        T1 -> parent = y;
    }

    if(x -> parent != nullptr){
        if(y == x -> parent -> left){
            x -> parent -> left = x;
        }
        else if(y == x -> parent -> right){
            x -> parent -> right = x;
        }
    }

    if(root == y){
        root = x;
    }

    node = x;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node*& node){
    Node* y = node;
    Node* x = y -> left;
    Node* T2 = x -> right;

    x -> right = y;
    y -> left = T2;

    x -> parent = y -> parent;
    y -> parent = x;

    if(T2 != nullptr){
        T2 -> parent = y;
    }

    if(x -> parent != nullptr){
        if(y == x -> parent -> left){
            x -> parent -> left = x;
        }
        else if(y == x -> parent -> right){
            x -> parent -> right = x;
        }
    }
    
    if(root == y){
        root = x;
    }

    node = x;
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node*& node){
    while(node != root && node -> parent -> color == RED){
        Node* parent = node -> parent;
        Node* grandparent = parent -> parent;
    

        if(parent == grandparent -> left){ //Left
            Node* uncle = grandparent -> right;

            if(uncle && uncle -> color == RED){
                //case 1: uncle is red --> recolor
                parent -> color = BLACK;
                uncle -> color = BLACK;
                grandparent -> color = RED;
                node = grandparent;
            }
            else if(!uncle || uncle -> color == BLACK){
                
                if(node == parent -> right){ //LR
                    rotateLeft(parent);
                    node = parent;
                    parent = node -> parent;
                }

                //LL
                parent -> color = BLACK;
                grandparent -> color = RED;
                rotateRight(grandparent);
            }
        }
        else if(parent == grandparent -> right){ //R
            Node* uncle = grandparent -> left;

            if(uncle && uncle -> color == RED){
                parent -> color = BLACK;
                uncle -> color = BLACK;
                grandparent -> color = RED;
                node = grandparent;
            }
            else if(!uncle || uncle -> color == BLACK){
                if(node == parent -> left){ //RL
                    rotateRight(parent);
                    parent = node -> parent;
                }
                //RR
                parent -> color = BLACK;
                grandparent -> color = RED;
                rotateLeft(grandparent);
            }
        }
    }

    root -> color = BLACK;

}

template <typename T>
void RedBlackTree<T>::remove(T value){
    remove(root, value);
}

template <typename T>
void RedBlackTree<T>::remove(Node*& node, T value){
    //BST removal + casework:
    if(value < node -> data){
        remove(node -> left, value);
    }
    else if(value > node -> data){
        remove(node -> right, value);
    }
    else if(value == node -> data){
        Node* z = node;
        Node* y = z;
        Color originalColorOfy = y -> color;
        Node* x = nullptr;


        if(node -> left == nullptr){ //node to be deleted has a right child or no children
            x = z -> right;
            transplant(z, z -> right); //replace z with its right child, which may or may not be a nullptr
        }
        else if(z -> right == nullptr){ //node to be deleted has a left child
            x = z -> left;
            transplant(z, z -> left);
        }
        else{ //case 2: z has 2 children
            //find successor node
            Node* successor = z -> right;
            while(successor -> left != nullptr){
                successor = successor -> left;
            }
            y = successor;
            x = y -> right;

            if(y -> parent == z){ //special case: y's parent is z
                if (x) x -> parent = y;
            }
            else{ //general case
                transplant(y, y -> right);
                y -> right = z -> right;
                if (y -> right) y -> right -> parent = y;

            }
            
            transplant(z, y);
            y -> left = z -> left;
            if(y -> left) y -> left -> parent = y;
        }

        y -> color = z -> color;

        if(originalColorOfy == BLACK){
            if(x) fixRemove(x);
        }

    }

    
}

template <typename T>
void RedBlackTree<T>::transplant(Node* u, Node* v){ //transplant helper
    if(u -> parent == nullptr){
        root = v;
    }
    else if(u == u -> parent -> left){
        u -> parent -> left = v;
    }
    else if(u == u -> parent -> right){
        u -> parent -> right = v;
    }

    if(v != nullptr){
        v -> parent = u -> parent;
    }
}

template <typename T>
void RedBlackTree<T>::fixRemove(Node* x){
    while(x != root && (!x || x -> color == BLACK)){ //while (x is not the root) and (x doesn't exist or x's color is black)

        Node* parent = x ? x -> parent : nullptr;

        if(parent == nullptr){
            break;
        }

        if(x == x -> parent -> left){ //x is the left child
            //cases
            Node* w = x -> parent -> right; //w is the right child

            if(w && w -> color == RED){ //if the sibling is red
                w -> color = BLACK; //make the sibling black
                x -> parent -> color = RED; //make the parent red
               rotateLeft(x -> parent); //rotate away from the sibling at the parent
                w = x -> parent -> right; //reassign the parent
            }
            else if(((!w -> left) || w -> left -> color == BLACK) && 
                    ((!w -> right) || (w -> right -> color == BLACK))){ //if the sibling has black children
                w -> color = RED; //make the sibling red
                x = x -> parent; //try again at the parent node
            }
            else if(w -> left && w -> left -> color == RED &&
            ((!w -> right) || w -> right -> color == BLACK)){ //if the sibling's inner child is red
                w -> left -> color = BLACK; //make that child black
                w -> color = RED; //make the sibling red
                rotateRight(w); //rotate away from the sibling's inner child at the sibling
                w = x -> parent -> right; //reassign the parent
            }
            else if(w -> color == BLACK && (!(w -> right) || w -> right -> color == RED)){ //if the sibling's outer child doesn't exist or is red
                w -> color = x -> parent -> color; //make the sibling's color the parent's *current* color
                x -> parent -> color = BLACK; //make the parent's color black
                if(w -> right) w -> right -> color = BLACK; //make the sibling's outer child black if it exists
                rotateLeft(x -> parent); //rotate away from the sibling's outer child
                x  = root; //break the loop
            }
            
        }

        //mirror logic 
        else if(x == x -> parent -> right){ //x is the right child
            Node* w = x -> parent -> left; //w is the left child
            if(w && w -> color == RED){
                w -> color = BLACK;
                x -> parent -> color = RED;
                rotateRight(x -> parent);
                w = x -> parent -> left;
            }
            else if(((!w -> left) || w -> left -> color == BLACK)
            && ((!w -> right ) || w -> right -> color == BLACK)){
                w -> color = RED;
                x = x -> parent;
            }
            else if(w -> left && w -> left -> color == RED &&
            ((!w -> right) || w -> right -> color == BLACK )){
                w -> left -> color = BLACK;
                w -> color = RED;
                rotateLeft(w);
                w = x -> parent -> left;
            }
            else if(w -> color == BLACK && (!(w -> right) || (w -> right -> color == RED))){
                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                if(w -> left) w -> left -> color = BLACK;
                rotateRight(x -> parent);
                x = root; //break the loop
            }
        }
    }

    if(x) x -> color = BLACK;
    root -> color = BLACK;
}

template <typename T>
void RedBlackTree<T>::inorder() const{
    inorder(root);
}

template <typename T>
void RedBlackTree<T>::inorder(Node* node) const{
        if(node){
            inorder(node -> left);
            std::string colorString = (node -> color == RED) ? "RED" : "BLACK";
            std::cout << node -> data << " (" << colorString << ") " << " -> ";
            inorder(node -> right);
        }
    }

template <typename T>
bool RedBlackTree<T>::search(T value){
    return search(root, value);
}

template <typename T>
bool RedBlackTree<T>::search(Node* node, T value){
    if(node == nullptr){
        return false;
    }
    else if(value == node -> data){
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




#endif