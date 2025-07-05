#ifndef STACK_HPP
#define STACK_HPP

#include "DLList.hpp"

template <typename T>
class Stack {
private:
    DLList<T> list;

public:
    void push(T value){
        list.insertFront(value);
    }

    void pop(){
        list.removeFront();
    }

    T top() const{
        return list.getFront();
    }

    bool isEmpty(){
        return list.getSize() == 0;
    }

    int size() const{
        return list.getSize();
    }

};

#endif