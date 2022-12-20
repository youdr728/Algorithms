// LiuID:
// - filru737
// - youdr728
//
// Contains implementation of custom PriorityQueue class, using min-heap BST implementation

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <math.h>
#include <iostream>

template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

    unsigned size() const;

private:
    MyVector<T> queue = MyVector<T>();

    void printTree();
    void swap(unsigned i, unsigned j);
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    // Standard constructor
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    // Standard deconstructor
}

// Add the given element to the queue
template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
//    std::cout << "Adding: " << t << std::endl;
//    std::cout << "-> ";

    unsigned currentIndex = queue.size(); // Is one larger than should be
    queue.push_back(t); // Adds on the end, will increase size + 1, so has to be done after queue.size() is saved
    unsigned parentIndex = (currentIndex - 1)/ 2;

    while (currentIndex != 0 and strictly_larger_operator(queue[parentIndex], t)) { // Parent > new
        swap(currentIndex, parentIndex);

        currentIndex = parentIndex; // Update to new pos
        parentIndex = (parentIndex - 1) / 2; // Update to new parent
    }
//    printTree();
//    std::cout << std::endl;

}

// Return the element with highest priority
template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return queue[0];
}

// Remove the element with highest priority
template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
//    std::cout << "-------------------------------------\n";
//    printTree();

    unsigned index = 0; // Start at the top
    queue[0] = queue[queue.size()-1];
    queue.pop_back();

    unsigned left = 2 * index + 1;
    unsigned right = 2 * index + 2;

//    std::cout << "\n New top: " << queue[0] << std::endl;
    while (right <= queue.size()-1 and (strictly_larger_operator(queue[index], queue[right]) or strictly_larger_operator(queue[index], queue[left]))) { // Loop as long as there are children, and the children are smaller



        unsigned replaceWith = left; // Assume left is smaller
        //std::cout << queue[left] << "   " << queue[right] << "   |   left > right: " << strictly_larger_operator(left, right) << std::endl;

        if (strictly_larger_operator(queue[left], queue[right])) { // (left > right) determine if right was smaller
            replaceWith = right; // right was smaller
            //std::cout << "   - Swapped with right" << std::endl;
        } /*else {
            std::cout << "   - Swapped with left" << std::endl;
        }*/

        swap(index, replaceWith);

        index = replaceWith; // Follow down the path which was replaced
        left = 2 * index + 1;
        right = 2 * index + 2;
    }
//    std::cout << "\n\n-> ";
//    printTree();
//    std::cout << std::endl;
}

// Returns whether the queue is empty or not
template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    // TODO: replace the code below with your code for this member
    return queue.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    // TODO: replace the code below with your code for this member
    return  queue.size();
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::printTree() {
    std::cout << "[ ";
    for (unsigned i=0; i < queue.size(); i++) {
        std::cout << queue[i] << ", ";
    }
    std::cout << "]";
}


template <typename T, typename C>
void MyPriorityQueue<T, C>::swap(unsigned i, unsigned j) {
    T tmpHolder = queue[i];
    queue[i] = queue[j];
    queue[j] = tmpHolder;
}


#endif // MY_PRIORITY_QUEUE_H
