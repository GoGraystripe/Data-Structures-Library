#ifndef HEAP
#define HEAP

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

enum HeapType {MIN, MAX};

template <typename T>
class Heap{
    private:
        void swap(int index1, int index2);
        void downHeapify(int position);
        void heapifyUp(int position);

public:
    std::vector<T> heap;
    int size;
    int maxSize;
    HeapType type;

    Heap(int maxSize, HeapType type);
    int findParentPosition(int position);
    T findParent(int position);
    int findLeftChildPosition(int position);
    T findLeftChild(int position);
    int findRightChildPosition(int position);
    T findRightChild(int position);
    void insert(T element);
    void print();
    T deleteRoot();
    void heapSort(std::vector<T>& data);
    std::vector<T> heapSort();
};

template <typename T>
Heap<T>::Heap(int maxSize, HeapType type){
    this -> maxSize = maxSize;
    this -> type = type;
    size = 0;
}

template <typename T>
int Heap<T>::findParentPosition(int position){
    return (position - 1)/2;
}

template <typename T>
T Heap<T>::findParent(int position){
    return heap[findParentPosition(position)];
}

template <typename T>
int Heap<T>::findLeftChildPosition(int position){
    return 2 * position + 1;
}

template <typename T>
T Heap<T>::findLeftChild(int position){
    return heap[findLeftChildPosition(position)];
}

template <typename T>
int Heap<T>::findRightChildPosition(int position){
    return 2 * position + 2;
}

template <typename T>
T Heap<T>::findRightChild(int position){
    return heap[findRightChildPosition(position)];
}

template <typename T>
void Heap<T>::swap(int index1, int index2){
    T temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

template <typename T>
void Heap<T>::downHeapify(int position){
    T node = heap[position];
    T leftChild = findLeftChild(position);
    T rightChild = findRightChild(position);
    T target = node;
    int targetPosition = position;
    
    while(true){
        node = heap[position];
        leftChild = findLeftChild(position);
        rightChild = findRightChild(position);
        target = node;
        targetPosition = position;

        if(type == MIN){
            if(findLeftChildPosition(position) < size && leftChild < target){
                targetPosition = findLeftChildPosition(position);
                target = leftChild;
            }
            if(findRightChildPosition(position) < size && rightChild < target){
                targetPosition = findRightChildPosition(position);
                target = rightChild;
            }
            
        }
        else if(type == MAX){
            if(findLeftChildPosition(position) < size && leftChild > target){
                targetPosition = findLeftChildPosition(position);
                target = leftChild;
            }
            if(findRightChildPosition(position) < size && rightChild > target){
                targetPosition = findRightChildPosition(position);
                target = rightChild;
            }
        }

        if(node == target){
            break;
        }
        else if(node != target){
            swap(position, targetPosition);
            position = targetPosition;
        }
    }
}

template <typename T>
void Heap<T>::heapifyUp(int position){
    if(type == MIN){
        T node = heap[position];
        T parent = findParent(position);
        while(position > 0 && parent > node){
            node = heap[position];
            parent = findParent(position);
            swap(position, findParentPosition(position));

            position = findParentPosition(position);
            node = heap[position];
            parent = findParent(position);

            if(position < 0){
                break;
            }
        }
        
    }
    else if(type == MAX){
        T node = heap[position];
        T parent = findParent(position);
        while(position > 0 && parent < node){
            node = heap[position];
            parent = findParent(position);
            swap(position, findParentPosition(position));

            position = findParentPosition(position);
            node = heap[position];
            parent = findParent(position);


            if(findParentPosition(position) < 0){
                break;
            }
        }
    }
}

template <typename T>
void Heap<T>::insert(T element){
    if(size <= maxSize){
        heap.push_back(element);
        
        heapifyUp(size);

        size++;
    }

    
}

template <typename T>
void Heap<T>::print(){
    
    std::cout<<"\n";

    int totalElementsLooped = 0;
    int elementsInRowLooped = 0;
    int row = 0;

    while(totalElementsLooped < size){
        while(elementsInRowLooped < pow(2, row) && totalElementsLooped < size){
            T node = heap[totalElementsLooped];
            std::cout << node << " ";
            
            totalElementsLooped++;
            elementsInRowLooped++;
        }
        
        std::cout<<"\n";

        row++;
        elementsInRowLooped = 0;
    }
}

template <typename T>
T Heap<T>::deleteRoot(){
    
    T result = heap[0];

    swap(0, size - 1);

    heap.pop_back();
    
    size--;

    downHeapify(0);

    return result;
}

template <typename T>
void Heap<T>::heapSort(std::vector<T>& data){
    Heap<T> heap(data.size(), MIN);

    for(int i = 0; i < data.size(); i++){
        heap.insert(data[i]);
    }

    data.clear();

    while(heap.size > 0){
        data.push_back(heap.deleteRoot());
    }
}

template <typename T>
std::vector<T> Heap<T>::heapSort(){
    int s = size;
    Heap tempHeap = *this;
    std::vector<T> data(s);

    if(type == MIN){

        for(int i = 0; i < s; i++){
            data[i] = tempHeap.deleteRoot();
        }

    }
    else if(type == MAX){

        for(int i = s - 1; i >= 0; i--){
            data[i] = tempHeap.deleteRoot();
        }
    }

    return data;

}


#endif