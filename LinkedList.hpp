#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

template <typename T>
class LinkedList{
private:
    struct Node{ //nested inside LinkedList class
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    LinkedList();               //constructor
    ~LinkedList();              //destructor
    void insertFront(T value);
    void insertBack(T value);
    void removeFront();
    void removeBack();
    void print() const;
    int getSize() const;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList(){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete(temp);
    }
}

template <typename T>
void LinkedList<T>::insertFront(T value) {
    Node* newNode = new Node(value);
    newNode -> next = head;
    head = newNode;

    size++;
}

template <typename T>
void LinkedList<T>::insertBack(T value){
    Node* newNode = new Node(value);
    if(!head){
        head = newNode;
    }
    else{
        Node* temp = head;
        while(temp -> next != nullptr){
            temp = temp -> next;
        }
        
        temp -> next = newNode;
    }

    size++;
}

template<typename T>
void LinkedList<T>::removeFront(){
    if(head == nullptr){
        return;
    }

    Node* temp = head;
    head = head->next;
    delete(temp);
    
    size--;
}   

template<typename T>
void LinkedList<T>::removeBack(){
    if(head == nullptr){
        return;
    }

    if(head->next == nullptr){
        delete(head);
        head = nullptr;
        size--;
        return;
    }

    Node* temp = head;
    while(temp->next->next != nullptr){
        temp = temp->next;
    }
    delete(temp->next);
    temp->next = nullptr;

    size--;
}

template<typename T>
void LinkedList<T>::print() const{
    if(head == nullptr){
        std::cout << "Empty List." << std::endl;
        return;
    }
    
    Node* temp = head;
    while(temp != nullptr){
        std::cout<< temp->data <<" -> ";
        temp = temp->next;
    }
    std::cout << "null" << std::endl;
}

template<typename T>
int LinkedList<T>::getSize() const{
    return size;
}

#endif

