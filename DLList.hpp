#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <iostream>

template <typename T>
class DLList{
private:
    struct Node{ //nested inside DLList class
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DLList();               //constructor
    ~DLList();              //destructor
    void insertFront(T value);
    void insertBack(T value);
    void removeFront();
    void removeBack();
    void insert(T value, int index);
    void remove(int index);
    T getFront() const;
    T getBack() const;
    void print() const;
    int getSize() const;
};

template <typename T>
DLList<T>::DLList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DLList<T>::~DLList(){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete(temp);
    }

    tail = nullptr;
}

template <typename T>
void DLList<T>::insertFront(T value) {
    Node* newNode = new Node(value);
    if(head == nullptr){ //list is empty
        tail = newNode;
    }
    else{
        head->prev = newNode;
    }
    
    newNode -> next = head;
    head = newNode;

    size++;
}

template <typename T>
void DLList<T>::insertBack(T value){
    Node* newNode = new Node(value);
    if(tail == nullptr){ //list is empty
        head = newNode;
    }
    else{
        tail->next = newNode;
    }

    newNode->prev = tail;
    tail = newNode;

    size++;
}

template<typename T>
void DLList<T>::removeFront(){
    if(head == nullptr){ //list is empty
        return;
    }

    Node* temp = head;
    head = head->next;
    delete(temp);

    if(head == nullptr){ //new list is empty
        tail = nullptr;
    }
    else{
        head->prev = nullptr;
    }
    
    size--;
}

template<typename T>
void DLList<T>::removeBack(){
    if(head == nullptr){ //list is empty
        return;
    }

    Node* temp = tail;
    tail = tail -> prev;
    delete(temp);

    if(tail == nullptr){
        head = nullptr;
    }
    else{
        tail -> next = nullptr;
    }

    size--;
}

template <typename T>
void DLList<T>::insert(T value, int index){

    if(index == 0){
        insertFront(value);
        return;
    }
    else if(index == size - 1){
        insertBack(value);
        return;
    }

    Node* tempPrev = head;
    for(int i = 0; i < index - 1; i++){
        tempPrev = tempPrev->next;
    }
    Node* tempNext = tempPrev -> next;

    Node* newNode = new Node(value);

    tempPrev -> next = newNode;
    tempNext -> prev = newNode;

    newNode -> prev = tempPrev;
    newNode -> next = tempNext;

    size--;
}

template <typename T>
void DLList<T>::remove(int index){

    if(index == 0){
        removeFront();
        return;
    }
    else if(index == size - 1){
        removeBack();
        return;
    }

    Node* tempPrev = head;
    for(int i = 0; i < index - 1; i++){
        tempPrev = tempPrev -> next;
    }

    Node* temp = tempPrev -> next;
    Node* tempNext = temp -> next;

    tempPrev -> next = tempNext;
    tempNext -> prev = tempPrev;
    
    delete(temp);
    temp = nullptr;
    
    size--;

}

template<typename T>
void DLList<T>::print() const{
    if(head == nullptr){
        std::cout << "Empty List." << std::endl;
        return;
    }
    
    Node* temp = head;
    while(temp->next != nullptr){
        std::cout<< temp->data <<" <-> ";
        temp = temp->next;
    }

    std::cout << temp->data;
    std::cout << " -> null" << std::endl;
}

template<typename T>
int DLList<T>::getSize() const{
    return size;
}

template<typename T>
T DLList<T>::getFront() const{
    return head->data;
}

template<typename T>
T DLList<T>::getBack() const{
    return tail->data;
}

#endif

