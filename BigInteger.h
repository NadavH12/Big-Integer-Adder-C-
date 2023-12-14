/*
Nadav Horowitz CS300 Data Structures
HW#4 - Big Integer Arithmetic and Doubly Linked List - BigInteger.h

This file contains the fields and the function prototypes for the BigInteger class. The file also contains a user defined IllegalArgumentException class. The implementation details of the BigInteger class can be found in BigInteger.cpp
*/
#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H
#include "DoublyLinkedList.h"

//user defined IllegalArgumentException class, can be thrown in the BigInteger parameterized constructor
class IllegalArgumentException : public std::exception {
};


class BigInteger {
public:
     //underlying DoublyLinkedList object holds the integers for the BigInteger
     DoublyLinkedList<int> list;

     //boolean negative field for identifying if BigInteger is positive or negative
     bool negative;

     //constructors
     BigInteger();
     BigInteger(string s);

     //getters
     int getLength();
     bool isNegative();
     
     //arithmetic operator overloading
     BigInteger operator+(const BigInteger &other);
     BigInteger operator-(const BigInteger &other);

     //assignment operator overloading
     BigInteger operator=(const BigInteger &other);

     //boolean operator overloading
     bool operator<=(const BigInteger &other);
     bool operator>=(const BigInteger &other);
     bool operator==(const BigInteger &other);
     bool operator>(const BigInteger &other);
     bool operator<(const BigInteger &other);
     
     //extraction operator overloading
     friend ostream& operator<<(ostream& out, const BigInteger &list);

     //insertion operator overloading
     friend istream& operator>>(istream& in,  BigInteger &list);
};
#endif