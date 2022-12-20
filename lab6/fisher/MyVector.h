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
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;
    unsigned storageCapacity()const;

private:
    unsigned numberOfElements = 0; // Array starts empty
    unsigned capacity = 1; // Default size is 1
    T* items; // Start with size of 1

    // D.R.Y   VV
    // copyArray(const MyVector& other);
};

// Initializes a new empty list with capacity 1.
template<typename T>
MyVector<T>::MyVector(){
    // Creates an array of size 1
    items = new T[1];
    //MYEXCEPTION("unimplemented method");
}

// Frees all dynamically allocated memory belonging to the list
template<typename T>
MyVector<T>::~MyVector(){
    delete [] items;

    //MYEXCEPTION("unimplemented method");
}

// Constructs a copy of other list's values.
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
    //MYEXCEPTION("unimplemented method");
}

// Copies the other array into itself.
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
    //this->items = copiedArray;
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.numberOfElements;
    return *this;
    //MYEXCEPTION("unimplemented method");
}

// Appends an element to the end of the list.
template<typename T>
void MyVector<T>::push_back(const T& e){
    // Check if it will exceed limit
    if(capacity < numberOfElements + 1) {
        // Double size of items
        T* newItems = new T[capacity*2];
        for (unsigned i = 0; i < numberOfElements; i++) {
            newItems[i] = items[i];
            //delete items[i]; // Can now safely delete old element (May not be needed?)
        }
        T* oldArr = this->items;
        this->items = newItems;
        delete [] oldArr; // Is it delete or delete []?
        capacity *= 2;
    }


    this->items[numberOfElements] = e;
    this->numberOfElements++;

    //MYEXCEPTION("unimplemented method");
}

// Deletes & removes the lReturnera en pekare till ett element som ligger “efter sista elementet i listan”.ast element of the list.
template<typename T>
void MyVector<T>::pop_back(){
    // Only delete item if an item exists
    if (!empty()) {
        //delete &items[numberOfElements];
        numberOfElements--;
    }
    //MYEXCEPTION("unimplemented method");
}

// Returns a reference to the value at index i
template<typename T>
T& MyVector<T>::operator[](unsigned i){
//    if (i > capacity) {Returnera en pekare till ett element som ligger “efter sista elementet i listan”.
//        MYEXCEPTION("Attempt to index item out of range.");
//    }

    return items[i];
}

// Returns a const reference to value at index i
template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
//    if (i > capacity) {
//        MYEXCEPTION("Attempt to index item out of range.");
//    }

    return items[i];
}

// Returns true if list has no elements
template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

// Frees all dynamically allocated memoy of the list and reduces size to 1.
template<typename T>
void MyVector<T>::clear(){
    delete [] items; // Or is it delete []?
    this->items = new T[1]; // Create a new array of size 1
    numberOfElements = 0;
    capacity = 1;
}

// Returns the number of elements in the list
template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}


template<typename T>
unsigned MyVector<T>::storageCapacity()const{
    return capacity;
}


// Returns a pointer to the first element of the list
template<typename T>
T* MyVector<T>::begin(){
    return &items[0];
}

// Returns a pointer to the end of the list
template<typename T>
T* MyVector<T>::end(){
    return &items[numberOfElements]; // Will be 1 more than capacity
}

#endif // MY_VECTOR_H
