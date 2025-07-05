#ifndef DEQUE.HPP
#define DEQUE.HPP

#include "DLList.hpp"

template <typename T>
class Deque{

private:
    DLList<T> list;

public:
    void pushFront(T value){
        list.insertFront(value);
    }    

    void pushBack(T value){
        list.insertBack(value);
    }

    void popFront(){
        list.removeFront();
    }

    void popBack(){
        list.removeBack();
    }

    T front() const{
        return list.getFront();
    }

    T back() const{
        return list.getBack();
    }

    bool isEmpty(){
        return list.getSize() == 0;
    }

    int size() const{
        return list.getSize();
    }

};

#endif