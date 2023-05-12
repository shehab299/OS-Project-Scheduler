#pragma once

#include "Node.h"
#include <string>
#include <stdexcept>

template <typename T>
class List
{
protected:
    Node<T>* headPtr;
	int size;
public:
    List();
    List(const List<T>& toCopy);
	bool insert(int newPosition, const T& newElement);
	bool remove(int position);
	T getElement(int position);
    int getSize();
    bool isEmpty();
	void clear();
    std::string toString();
    ~List();
};


template<typename T>
List<T>::List() : headPtr(nullptr) , size(0)
{
}

template<typename T>
List<T>::List(const List<T>& toCopy)
{
    headPtr = nullptr;
    size = 0;
    Node<T>* srcPtr = toCopy.headPtr;
    Node<T>* destPtr = nullptr;

    while (srcPtr != nullptr) 
    {
        Node* newNode = new Node(srcPtr->getItem());
        
        if (destPtr == nullptr) {
            headPtr = newNode;
        }
        else {
            destPtr->setNext(newNode);
        }

        destPtr = newNode;
        srcPtr = srcPtr->getNext();
        size++;
    }
}

template <typename T>
bool List<T>::insert(int newPosition, const T& newElement) {

    if (newPosition < 0 || newPosition > size) {
        return false;
    }

    Node<T>* newNode = new Node<T>(newElement);

    if (newPosition == 0) {
        newNode->setNext(headPtr);
        headPtr = newNode;
    }
    else {
        Node<T>* prevPtr = headPtr;
        for (int i = 0; i < newPosition - 1; i++) {
            prevPtr = prevPtr;
        }
        newNode->setNext(prevPtr->getNext());
        prevPtr->setNext(newNode);
    }
    size++;
    return true;
}



template <typename T>
bool List<T>::remove(int position) {
    if (position < 0 || position >= size) {
        return false;
    }
    Node<T>* deletePtr = nullptr;
    if (position == 0) {
        deletePtr = headPtr;
        headPtr = headPtr->getNext();
    }
    else {
        Node<T>* prevPtr = headPtr;
        for (int i = 0; i < position - 1; i++) {
            prevPtr = prevPtr->getNext();
        }
        deletePtr = prevPtr->getNext();
        prevPtr->setNext(deletePtr->getNext());
    }
    delete deletePtr;
    size--;
    return true;
}



template <typename T>
T  List<T>::getElement(int position) {
    if (position < 0 || position >= size) {
        throw std::out_of_range("Index out of range.");
    }

    Node<T>* currPtr = headPtr;
    for (int i = 0; i < position; i++) {
        currPtr = currPtr->getNext();
    }
    return currPtr->getItem();
}


template <typename T>
void  List<T>::clear()
{
    while (headPtr) 
    {
        Node<T>* deletePtr = headPtr;
        headPtr = headPtr->getNext();
        delete deletePtr;
    }
    size = 0;
}



template<typename T>
std::string List<T>::toString()
{
    std::string text = "";
    Node<T>* temp = headPtr;

    while (temp)
    {
        text += to_string(temp->getItem());

        if (temp->getNext())
            text += ", ";

        temp = temp->getNext();
    }
    return text;
}


template <typename T>
int List<T>::getSize()
{
    return size;
}

template<typename T>
bool List<T>::isEmpty()
{
    return (size == 0);
}


template<typename T>
List<T>:: ~List()
{
    clear();
}
