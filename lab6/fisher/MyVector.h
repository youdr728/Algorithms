// LiuID:
// - filru737
// - youdr728
//
// Contains implementation of custom Vector class

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
//#include <math.h>

template <typename T>
class MyVector
{

public:
    // Initializes a new empty list with capacity 1.
    MyVector();

    // Frees all dynamically allocated memory belonging to the list
    ~MyVector();

    // Constructs a copy of other list's values.
    MyVector(const MyVector& other);

    // Copies the other array into itself.
    MyVector& operator =(const MyVector& other);

    // Appends an element to the end of the list.
    void push_back(const T&);

    // Deletes & removes the last element of the list.
    void pop_back();

    // Returns a reference to the value at index i
    T& operator[](unsigned i);

    // Returns a const reference to value at index i
    const T& operator[](unsigned i)const;

    // Returns true if list has no elements
    bool empty()const;

    // Returns a pointer to the first element of the list
    T* begin();

    // Returns a pointer to the end of the list
    T* end();

    // Frees all dynamically allocated memoy of the list and reduces size to 1.
    void clear();

    // Returns the number of elements in the list
    unsigned size()const;

    // Returns size of array
    unsigned storageCapacity()const;

private:
    unsigned numberOfElements = 0; // Array starts empty
    unsigned capacity = 1; // Default size is 1
    T* items; // Start with size of 1

};


template<typename T>
MyVector<T>::MyVector(){
    // Creates an array of size 1
    items = new T[1];
}


template<typename T>
MyVector<T>::~MyVector(){
    delete [] items;
}


template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    if (this == &other) {
        return;
    }

    items = new T[other.capacity];
    for (unsigned i = 0; i < other.numberOfElements; i++) {
        items[i] = other.items[i];
    }

    this->numberOfElements = other.numberOfElements;
    this->capacity = other.numberOfElements;
}


template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this == &other) {
        return *this;
    }

    delete [] items;
    items = new T[other.capacity];
    for (unsigned i = 0; i < other.numberOfElements; i++) {
        items[i] = other.items[i];
    }
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.numberOfElements;
    return *this;
}


template<typename T>
void MyVector<T>::push_back(const T& e){
    if(capacity < numberOfElements + 1) {
        // Double size of items
        T* newItems = new T[capacity*2];
        for (unsigned i = 0; i < numberOfElements; i++) {
            newItems[i] = items[i];
        }
        T* oldArr = this->items;
        this->items = newItems;
        delete [] oldArr; // Is it delete or delete []?
        capacity *= 2;
    }


    this->items[numberOfElements] = e;
    this->numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    // Only delete item if an item exists
    if (!empty()) {
        numberOfElements--;
    }
}


template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return items[i];
}


template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return items[i];
}


template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}


template<typename T>
void MyVector<T>::clear(){
    delete [] items; // Or is it delete []?
    this->items = new T[1]; // Create a new array of size 1
    numberOfElements = 0;
    capacity = 1;
}


template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}


template<typename T>
unsigned MyVector<T>::storageCapacity()const{
    return capacity;
}


template<typename T>
T* MyVector<T>::begin(){
    return &items[0];
}


template<typename T>
T* MyVector<T>::end(){
    return &items[numberOfElements]; // Will be 1 more than capacity
}

#endif // MY_VECTOR_H
