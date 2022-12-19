// LiuID:
// - filru737
// - youdr728
//
// Contains implementation of custom PriorityQueue class, using max-heap BST implementation

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <math.h>


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

    unsigned currentIndex = queue.size() - 1;
    unsigned parentIndex = (currentIndex)/ 2;
    ////////////////////////////////////////////////// Something is wrong here
    while (currentIndex != 0 and strictly_larger_operator(t, queue[parentIndex])) { // While t > queue[parentIndex]
        queue[currentIndex] = queue[parentIndex]; // Move parent down
        queue[parentIndex] = t; // Move t up
        currentIndex = parentIndex; // Update to new pos

        parentIndex = (parentIndex - 1) / 2; // Update to new parent
    }

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
    while (2 * index + 1 <= queue.size()) { // Loop until it is out of range
        unsigned left = 2 * index + 1;
        unsigned right = 2 * index + 2;

        unsigned replaceWith = right; // Assume right is bigger
        if (strictly_larger_operator(left, right)) {
            replaceWith = left; // Left was bigger
        }

        queue[index] = queue[replaceWith];

        index = replaceWith; // Follow down the path which was replaced
    }

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




#endif // MY_PRIORITY_QUEUE_H
