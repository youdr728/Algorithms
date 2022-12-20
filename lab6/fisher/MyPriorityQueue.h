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
    queue.push_back(t); // Adds on the end
    std::cout << "Adding: " << t << std::endl;
    printTree();
    std::cout << " -> ";

    unsigned currentIndex = queue.size() - 1;
    unsigned parentIndex = (currentIndex)/ 2;

    while (currentIndex != 0 and strictly_larger_operator(queue[parentIndex], t)) { // Parent > new
        queue[currentIndex] = queue[parentIndex]; // Move parent down
        queue[parentIndex] = t; // Move t up
        currentIndex = parentIndex; // Update to new pos

        parentIndex = (parentIndex - 1) / 2; // Update to new parent
    }
    printTree();
    std::cout << std::endl;

}

// Return the element with highest priority
template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return queue[0];
}

// Remove the element with highest priority
template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    unsigned index = 0; // Start at the top
    queue[0] = queue[queue.size()-1];
    queue.pop_back();

    unsigned left = 2 * index + 1;
    unsigned right = 2 * index + 2;

    if (strictly_larger_operator(queue[left], queue[0]) and strictly_larger_operator(queue[right], queue[0])) {
        return; // found the smallest (somehow at the back initially?)
    }

    while (right <= queue.size()-1) { // Loop as long as there are children

        unsigned replaceWith = left; // Assume left is smaller
//        std::cout << queue[left] << "   " << queue[right] << "   |   left > right: " << strictly_larger_operator(left, right) << std::endl;

        if (strictly_larger_operator(queue[left], queue[right])) { // (left > right) determine if right was smaller
            replaceWith = right; // right was smaller
//            std::cout << "   - Swapped with right" << std::endl;
        }/* else {
            std::cout << "   - Swapped with left" << std::endl;
        }*/

        queue[index] = queue[replaceWith];

        index = replaceWith; // Follow down the path which was replaced
        left = 2 * index + 1;
        right = 2 * index + 2;
    }

    std::cout << "New top: " << top() << std::endl;
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



#endif // MY_PRIORITY_QUEUE_H
