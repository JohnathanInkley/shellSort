// Filename: main.cpp
// Author: Johnathan Inkley
// Date: 2016 10 15
// Description: a simple implementation of the shell sort on a linked list

#include <iostream>
#include <fstream>
#include <ctime>
#include "shell.h"

int main()
{
  std::ifstream inputFile;
  inputFile.open("listOfNum.dat");
  LinkedList myList;
  myList.populate(inputFile);
  inputFile.close();

  //Measure time for shell sort
  std::clock_t begin = clock();
  myList.shell();
  std::clock_t end = clock();
  std::cout << "\nShell sort took " << (double) (end - begin) << std::endl;

  inputFile.open("listOfNum.dat");
  LinkedList myList2;
  myList2.populate(inputFile);
  inputFile.close();

  //Measure time for insertion sort
  std::clock_t begin1 = clock();
  insertionSort(myList2);
  std::clock_t end1 = clock();
  std::cout << "\nInsertion sort took " << (double) (end1 - begin1) << std::endl << std::endl;

  // Display sorted list to screen
  myList.output();

  // Test destructors
  myList.~LinkedList();
  myList2.~LinkedList();
  
  
  return 0;
}
