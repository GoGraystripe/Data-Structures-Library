#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DLList.hpp"

template <typename T>
class Queue {

private:
    DLList<T> list;

public:
    void enqueue(T value){
        list.insertBack(value);
    }

    void dequeue(){
        list.removeFront();
    }

    T front() const{
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