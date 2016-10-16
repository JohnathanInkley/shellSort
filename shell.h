// Filename: shell.h
// Author: Johnathan Inkley
// Date: 2016 10 15
// Description: Function declarations for the shell sort and insertion sort functions

#ifndef SHELL_H
#define SHELL_H

struct Node
{
  int num;
  Node *next;
};

typedef Node* NodePtr;

NodePtr addNewNode(NodePtr head, int numberToAdd);
// Precondition: head is either NULL or start of an existing linkedList.
// Postcondition: The list has the desired number added in a new node

  
class LinkedList
{
 public:
  LinkedList();
  // Creates a blank linkedList that the user must fill in with the populate function
  LinkedList(const LinkedList& aList);
  // Copy constructor 
  ~LinkedList();
  // Destructor 
  void populate(std::ifstream& inputFile);
  // Fills LinkedList with integers from an input file
  friend void insertionSort(LinkedList& list);
  // Performs an insertion sort on a given LinkedList
  void shell();
  // Peforms a shell sort on our LinkedList
  void output();
  // Outputs our LinkedList to the screen
 private:
  void kSort(int k);
  // Performs a k sort for the whole list
  void addToList(int numberToAdd);
  // Adds a single element to our list
  NodePtr advance(NodePtr current, int k);
  // This will advance current k places and return prevCurrentPtr so you can join lists
  void sortKSublist(NodePtr subStart, int k);
  // Sorts a given k sublist
  void extractSubList(LinkedList& subList, NodePtr subStart, int k);
  // Given a NodePtr, it populates subList (a blank list) with every kth elt after our NodePtr
  void insertSubList(const LinkedList& subList, NodePtr subStart, int k);
  // Given a list, it puts the list values into every kth position starting from subStart
  int length;
  // Length of our list
  NodePtr listStart;
  // Head of the list
};


#endif
