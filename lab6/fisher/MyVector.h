// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

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
    // TODO: replace the code below with your code for this member

    //T copy[round(log2(other.numberOfElements))]; // Crete minimum size
    T copiedArray[other.capacity];
    for (unsigned i = 0; i < other.capacity - 1; i++) {
        T copy = items[i]; // Copy-constructor creating a new one
        copiedArray[i] = &copy;
    }

    for (unsigned i = 0; i < this->capacity - 1; i++) {
        delete items[i]; // not needed, items is empty
    }
    T* oldArr = this->items;
    this->items = copiedArray;
    delete oldArr; // Or is it delete []?
    this->numberOfElements = other.numberOfElements;
    this->capacity = other.numberOfElements;
    //MYEXCEPTION("unimplemented method");
}

// Copies the other array into itself.
template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if (this->items == other.items) {
        return this;
    }

    T copiedArray[other.capacity];
    for (unsigned i = 0; i < other.capacity - 1; i++) {
        T copy = items[i]; // Copy-constructor creating a new one
        copiedArray[i] = &copy;
    }

    for (unsigned i = 0; i < this->capacity - 1; i++) {
        delete items[i];
    }
    T* oldArr = this->items;
    this->items = copiedArray;
    delete oldArr; // Or is it delete []?

    this->numberOfElements = other.numberOfElements;
    this->capacity = other.numberOfElements;
    return this;
    //MYEXCEPTION("unimplemented method");
}

// Appends an element to the end of the list.
template<typename T>
void MyVector<T>::push_back(const T& e){
    // Check if it will exceed limit
    if(capacity < numberOfElements) {
        // Double size of items
        T* newItems = new T[capacity*2];
        for (unsigned i = 0; i < numberOfElements; i++) {
//            T copy = items[i]; // Copy-constructor creating a new one
//            newItems[i] = copy;
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
        numberOfElements--;
        delete &items[numberOfElements];
    }
    //MYEXCEPTION("unimplemented method");
}

// Returns a reference to the value at index i
template<typename T>
T& MyVector<T>::operator[](unsigned i){
    // TODO: replace the code below with your code for this member
//    if (i > capacity) {Returnera en pekare till ett element som ligger “efter sista elementet i listan”.
//        MYEXCEPTION("Attempt to index item out of range.");
//    }

    return items[i];
    //return items[numberOfElements - 1];
    //MYEXCEPTION("unimplemented method");
}

// Returns a const reference to value at index i
template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    // TODO: replace the code below with your code for this member
//    if (i > capacity) {
//        MYEXCEPTION("Attempt to index item out of range.");
//    }

    return items[i];
    //MYEXCEPTION("unimplemented method");
}

// Returns true if list has no elements
template<typename T>
bool MyVector<T>::empty()const{
    // TODO: replace the code below with your code for this member
    return numberOfElements == 0;
    //MYEXCEPTION("unimplemented method");
}

// Frees all dynamically allocated memoy of the list and reduces size to 1.
template<typename T>
void MyVector<T>::clear(){
    // TODO: replace the code below with your code for this member
//    for (unsigned i = 0; i < numberOfElements-1; i++) {
//        delete &items[i];
//    }
    delete [] items; // Or is it delete []?
    this->items = new T[1]; // Create a new array of size 1
    numberOfElements = 0;
    capacity = 1;
    //MYEXCEPTION("unimplemented method");
}

// Returns the number of elements in the list
template<typename T>
unsigned MyVector<T>::size()const{
    // TODO: replace the code below with your code for this member
    return numberOfElements;
    //MYEXCEPTION("unimplemented method");
}

// Returns a pointer to the first element of the list
template<typename T>
T* MyVector<T>::begin(){
    // TODO: replace the code below with your code for this member
    return &items[0];
    //MYEXCEPTION("unimplemented method");
}

// Returns a pointer to the end of the list
template<typename T>
T* MyVector<T>::end(){
    // TODO: replace the code below with your code for this member
    return &items[numberOfElements]; // Will be 1 more than capacity
    //MYEXCEPTION("unimplemented method");
}

#endif // MY_VECTOR_H
