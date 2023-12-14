/*
Nadav Horowitz CS300 Data Structures
HW#4 - Big Integer Arithmetic and Doubly Linked List - BigInteger.cpp

This file contains the implementation details for the function prototypes specified in BigInteger.h. The file contains a default constructer and also a constructor which takes in a string. The file uses the default destructor. The file contains getter methods like getLength() and isNegative(). The file also implements operator overloading for addition, subtraction, equality, and boolean operators. The file also overloads the insertion and extraction operators.
*/
#include <iostream>
#include <string>
#include "BigInteger.h"
using namespace std;

     //default constructor (Not used)
     BigInteger::BigInteger() = default;

     //constructor with string parameter throws IllegalArgumentException for non-numeric input
     BigInteger::BigInteger(string s) {
          int k = 0;
          char letter = s.at(0);
          if(letter == '-' || letter == 45){
               negative = true;
               k = 1;
          } else {
               negative = false;
          }
          for(int i = k; i < s.length(); i++){
               char letter = s.at(i);
               if(letter >= 58 || letter < 48){
                    throw new IllegalArgumentException;
               }
               int digit = letter - '0';
               list.insertLast(digit);
          }
     }

     //getLength() getter method returns # of integers in BigInteger object
     int BigInteger::getLength(){
          return list.getLength();
     }

     //isNegative() getter method returns boolean value for field negative of BigInteger
     bool BigInteger::isNegative(){
          return negative;
     }

     //addition operator overloading allows functionality for addition of BigInteger objects
     BigInteger BigInteger::operator+(const BigInteger &other){
          DoublyLinkedList<int> sumList;
          DoublyLinkedList<int> otherList = other.list;
          list.setIteratorLast();
          otherList.setIteratorLast();
          int carryover = 0;
          while(!otherList.isIteratorNULL() && !list.isIteratorNULL()){
               int otherListElement = otherList.getData();
               int thisListElement = list.getData();
               int total = (carryover + thisListElement + otherListElement);
               sumList.insertFirst(total % 10);
               if(total >= 10)
                    carryover = 1;
               else
                    carryover = 0;
               list.prev();
               otherList.prev();
          }
          while(!list.isIteratorNULL()){
               sumList.insertFirst(carryover + list.getData());
               list.prev();
               carryover = 0;
          }
          while(!otherList.isIteratorNULL()){
               sumList.insertFirst(carryover + otherList.getData());
               otherList.prev();
               carryover = 0;
          }
          string s = sumList.display();
          BigInteger newBigInteger = BigInteger(s);
          return newBigInteger;
     }

    //subtraction operator overloading allows functionality for subtraction of BigInteger objects 
     BigInteger BigInteger::operator-(const BigInteger &other){
          DoublyLinkedList<int> otherList = other.list;
          DoublyLinkedList<int> thisList = this->list;
          if(*this == other){
               BigInteger diff = BigInteger("0");
               return diff;
          }
          bool negate = false;
          if(*this < other){
               DoublyLinkedList<int> tempList = thisList;
               thisList = otherList;
               otherList = tempList;
               negate = true;
          }
          while(thisList.getLength() > otherList.getLength()){
               otherList.insertFirst(0);
          }
          while(thisList.getLength() < otherList.getLength()){
               thisList.insertFirst(0);
          }
          DoublyLinkedList<int> sumList;
          thisList.setIteratorLast();
          otherList.setIteratorLast();
          int carryover = 0;
          int difference = 0;
          while(!thisList.isIteratorNULL()){
               int thisListElement = thisList.getData();
               int otherListElement = otherList.getData();
               thisList.prev();
               otherList.prev();
               difference = thisListElement - otherListElement + carryover;
               if(difference < 0){
                    carryover = -1;
                    difference = 10 + difference;
               }
               else {
                    carryover = 0;
               }
               sumList.insertFirst(difference);
          }
          sumList.trimZeros();
          if(negate == true){
               sumList.insertFirst('-');
          }
          string diffString = sumList.display();
          BigInteger diff = BigInteger(diffString);
          return diff;
     }

     //overloading assignment operator
     BigInteger BigInteger::operator=(const BigInteger &other){
          this->negative = other.negative;
          this->list = other.list;
          return *this;
     }

     //overloading boolean operator <=
     bool BigInteger::operator<=(const BigInteger &other){
          if(*this == other){
               return true;
          }
          if(*this < other)
               return true;
          return false;
     }

     //overloading boolean operator >=
     bool BigInteger::operator>=(const BigInteger &other){
          if(*this == other){
               return true;
          }
          if(*this > other)
               return true;
          return false;
     }

     //overloading boolean operator ==
     bool BigInteger::operator==(const BigInteger &other){
          DoublyLinkedList<int> otherList = other.list;
          if(this->negative != other.negative || this->getLength() != otherList.getLength())
               return false;
          
          otherList.setIteratorFirst();
          this->list.setIteratorFirst();
          while(otherList.hasNext()){
               int thisElement = list.getData();
               int otherElement = otherList.getData();
               if(thisElement != otherElement)
                    return false;
               list.next();
               otherList.next();
          }
          return true;
     }

     //overloading boolean operator >
     bool BigInteger::operator>(const BigInteger &other){
          if(!this->negative && other.negative)
               return true;
          if(this->negative && !other.negative)
               return false;
          DoublyLinkedList<int> otherList = other.list;
          if(this->negative && (this->getLength() > otherList.getLength()))
               return false;
          if(this->negative && (this->getLength() < otherList.getLength()))
               return true;
          if(!this->negative && (this->getLength() > otherList.getLength()))
               return true;
          if(!this->negative && (this->getLength() < otherList.getLength()))
               return false;
          otherList.setIteratorFirst();
          this->list.setIteratorFirst();
          while(!otherList.isIteratorNULL()){
               int thisElement = list.getData();
               int otherElement = otherList.getData();
               if(thisElement < otherElement)
                    return false;
               list.next();
               otherList.next();
          }
          return true;
     }

     //overloading boolean operator <
     bool BigInteger::operator<(const BigInteger &other){
          if (*this > other)
               return false; 
          return true;
     }
     
     //overloading extraction operator <<
     ostream& operator<<(ostream& out, const BigInteger &other){
          DoublyLinkedList<int> thisList = other.list;
          out << thisList.display();
          return out;
     }

     //overloading insertion operator >>
     istream& operator>>(istream& in, BigInteger &other){
          string s;
          std::getline(in,s);
          BigInteger big = BigInteger(s);
          other = big;
          return in;
     }