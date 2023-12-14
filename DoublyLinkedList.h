/*
Nadav Horowitz CS300 Data Structures
HW#4 - Big Integer Arithmetic and Doubly Linked List - DoublyLinkedList.h

This file contains the impelementation of a DoublyLinkedList. The DoublyLinkedList has fields for pointers of the first Node, the last Node, and for a Node iterator. The class also contains a field for the list length.
This file also contains a user defined NoSuchElementException class, which is thrown when a call to move the iterator to the next or previous Node is made and the Node doesn't exist.
The file contains various getter and setter methods, operator overloading, and constructors and destructors, including a deep copy constructor.
*/
#ifndef DOUBLY_LINKED_LIST_
#define DOUBLY_LINKED_LIST_

#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//user defined NoSuchElementException class, can be thrown in the next() and prev() methods
class NoSuchElementException : public std::exception {
};

template <class T>
class DoublyLinkedList {
    
protected:
    Node<T> *first;      //a pointer to the first of the linked list
    Node<T> *last;       //a pointer to the last node of the linked list
    Node<T> *iterator;   //an internal iterator for the linked list object
    int length;          //number of items in the linked list
                                                                    
public:
    //default no-argument constructor
    DoublyLinkedList(){
        first = nullptr;
        last = nullptr;
        iterator = nullptr;
        length = 0;
    }  

    //destructor  
    ~DoublyLinkedList() = default;  
    
    //display() method extracts and returns a string which contains the integers that are in the list
    string display(){
        string s = "";
        setIteratorFirst();
        if(getData() == '-' || getData() == 45){
            s = s + "-";
            next();
        }
        while(hasNext()){
            s = s + to_string(getData());
            next();
        }
        s = s + to_string(getData());
        iterator = nullptr;
        return s;
    }

    //initializes an empty list
    void init(){
        first = nullptr;
        last = nullptr;
        iterator = nullptr;
        length = 0;
    }

    //deep copy constructor
    DoublyLinkedList(const DoublyLinkedList<T> &oldList){
        DoublyLinkedList<T> newList;
        Node<T>* current = oldList.first;
        while(current != nullptr){
            T& data = current->data;
            newList.insertLast(data);
            current = current->next;
        }
        *this = newList;
    } 

    //assignment operator overloading
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T> &other){
        this->first = other.first;
        this->last = other.last;
        this->iterator = other.iterator;
        this->length = other.length;
        return *this;
    }

    //trimZeros() method removes leading zeros of a DoublyLinkedList
    DoublyLinkedList<T>& trimZeros(){
        this->setIteratorFirst();
        while(this->getData() == 0){
            this->deleteFirst();
            this->setIteratorFirst();
        }
        return *this;
    }

    //returns true if the list is empty, false otherwise
    bool isEmpty(){
        return length == 0;
    }                

    //returns the number of items in the list
    int getLength(){
        return length;
    }              

    //inserts a new item to the beginning of the list
    void insertFirst(const T &newData){
        //Creation of new 1st Node
        Node<T>* newNode = new Node<T>();
        newNode->data = newData;
        //Non empty list insertion
        if(length > 0){
            iterator = first;
            first->prev = newNode;
            first = newNode;
            newNode->next = iterator;
        } 
        //Empty list insertion
        else{
            first = newNode;
            last = newNode;
        }
        length++;
        iterator = nullptr;
    }   

    //inserts a new item at the end of the list
    void insertLast(const T &newData){
        Node<T>* newNode = new Node<T>();
        newNode->data = newData;
        //Empty list insertion
        if(length == 0){
            insertFirst(newData);
        } 
        //Non empty list insertion
        else{
            setIteratorLast();
            iterator->next = newNode;
            newNode->prev = last;
            last = newNode;
            length++;
        }
        iterator = nullptr;
    }   

    //deletes the first item from the list
    void deleteFirst(){
        if(!isEmpty()){
            iterator = first->next;
            first = first->next;
            iterator->prev = nullptr;
            length--;
            iterator = nullptr;
        }
    }             

    //deletes the last item in the list
    void deleteLast(){
        if(!isEmpty()){
            setIteratorLast();
            last = iterator->prev;
            last->next = nullptr;
            iterator->prev = nullptr;
            length--;
            iterator = nullptr;
        }
    }              

    //destroys the list and makes it empty
    void clear(){
        init();
    }

    //iterator functions
    //sets the iterator to the beginning of the linked list
    void setIteratorFirst(){
        iterator = first;
    }      

    //sets the iterator to the end of the linked list
    void setIteratorLast(){
        iterator = last;
    }        

    //checks if the iterator has next
    bool hasNext(){
        return iterator->next != nullptr;
    } 

    //checks if the iterator has prev
    bool hasPrev(){
        return iterator->prev != nullptr;
    }          

    //If next node exists, sets the iterator to the next node. Otherwise throws NoSuchElementException
    void next(){
        if(this->isIteratorNULL())
            throw new NoSuchElementException; 
        else
            iterator = iterator->next;
    }

    //If prev node exists, sets the iterator to the prev node. Otherwise throws NoSuchElementException
    void prev(){
        if(this->isIteratorNULL())
            throw new NoSuchElementException;
        else
            iterator = iterator->prev;
    }

    //returns true if the iterator is null
    bool isIteratorNULL(){
        return iterator == nullptr;
    }

    //gets the data the iterator pointing at 
    T getData(){
        return iterator->data;
    }

    //friend functions
    //overloading operator<<
    friend ostream& operator<<(ostream& out, const DoublyLinkedList<T> &list){
        out << list.display();
        return out;
    }

    //overloading operator>>
    friend istream& operator>>(istream& in, DoublyLinkedList<T> &list){
        in >> list.display();
        return in;
    }
};
#endif 