// Filename: shell.cpp
// Author: Johnathan Inkley
// Date: 2016 10 15
// Description: Function definitions for the shell sort and insertion sort

#include <iostream>
#include <fstream>
#include <assert.h>
#include "shell.h"

NodePtr addNewNode(NodePtr head, int numberToAdd)
{
  NodePtr tempPtr;
  tempPtr = new Node;
  assert(tempPtr);
  tempPtr->next = head;
  tempPtr->num = numberToAdd;
  return tempPtr;
}

LinkedList::LinkedList() : listStart(NULL), length(0)
{
  // Intentionally empty
}

LinkedList::LinkedList(const LinkedList& aList)
{
  NodePtr tempPtr = aList.listStart;
  while (tempPtr != NULL)
    {
      listStart = addNewNode(listStart, tempPtr->num);
      tempPtr = tempPtr->next;
    }
  return;
}

LinkedList::~LinkedList()
{
  NodePtr tempPtr = listStart, prevPtr;
  while (tempPtr != NULL)
    {
      prevPtr = tempPtr;
      tempPtr = tempPtr->next;
      delete prevPtr;
    }
  return;
}

void LinkedList::populate(std::ifstream& inputFile)
{
  int currentNum;
  inputFile >> currentNum;
  while (!inputFile.eof())
    {
      length++;
      listStart =  addNewNode(listStart, currentNum);
      inputFile >> currentNum;
    }
  return;
}

void LinkedList::addToList(int numberToAdd)
{
  listStart = addNewNode(listStart, numberToAdd);
  length++;
  return;
}

// This badboy saves us manually incremementing our pointer k times for our sublist
NodePtr LinkedList::advance(NodePtr current, int k)
{
  for (int j = 1; j <= k; j++)
    {
      current = current->next;
      if (current == NULL)
	break;
    }
  return current;
}

void LinkedList::output()
{
  NodePtr currentStart = listStart;
  while (currentStart)
    {
      std::cout << currentStart->num << " ";
      currentStart = currentStart->next;
    }
  std::cout << std::endl;
  return;
}

void LinkedList::shell()
{
  int k = length;
  while (k > 1)
    {
      k = k/2; // Note we want floor of k/2 so just do int division
      kSort(k);
    }

  return;
}

void LinkedList::kSort(int k)
{
  /* Wwhat this function needs to do is sort every k sublist. Therefore given a starting point
      we have sortKSublist below that sorts a k sublist for us. So this function just contains 
     a loop over 1 to k and calls sortKSublist
   */
  NodePtr subStart = listStart;
  for (int i = 1; i <= k; i++)
    {
      sortKSublist(subStart, k);
      subStart = subStart->next;
    }
  return;
}

void LinkedList::sortKSublist(NodePtr subStart, int k)
{
  /* This function needs to sort a given k sublist. However, this problem is non trivial for linked
     lists. The reason is when sorting a regular linked list, you can use the insertion sort to 
     move the element in to the correct place by simple deleting and adding of new links. However,
     as our sublist is part of a bigger list, we need to change the links in the big linked list,
     not in the sublist. This requires permutation of the elements!

     i.e if our simple list was 2 3 1, the insertion sort would simply pick 1 our and put it before
     the 2. but in our case we have x x 2 x x 3 x x 1 x x say. So we effectively, would have a temp
     number and say temp = 1, then put 3 into position of 1, 2 into position of 3, and then temp
     into position of 2. Very bad!

     So a better idea: For each k sublist. Make a copy of it as a real linked list. Use a standard
     insertion sort on this, which is trivial. And then have a function that reinserts this into
     our big linked list. This is what this function will do!
   */

  // 1) Make a copy of the sublist as a linked list
  LinkedList subList;
  extractSubList(subList, subStart, k);
  // 2) Run an insertion sort
  insertionSort(subList);
  // 3) Reinsert the sublist
  insertSubList(subList, subStart, k);
}


void LinkedList::extractSubList(LinkedList& subList, NodePtr subStart, int k)
{
  
  while (subStart != NULL)
    {
      subList.addToList(subStart->num);
      subStart = advance(subStart, k);
    }
  
  return;
}

void LinkedList::insertSubList(const LinkedList& subList, NodePtr subStart, int k)
{
  /* Move subStart through our original k subList and replace it with the corrensponding elt
     of our sorted subList */

  // Get the start to the sublist
  NodePtr subListPtr = subList.listStart;

  while (subStart != NULL)
    {
      subStart->num = subListPtr->num;
      subListPtr = subListPtr->next;
      subStart = advance(subStart,k);
    }
}

void insertionSort(LinkedList& list)
{
  /* Steps for an insertion sort are, for each position 1,2,...,end, we take the number in position
     i and place it in the sub array 1 to i
   */

  NodePtr currentStart, prevCurrentStart, tempStart,  loopPtr, prevLoopPtr, tempPtr;
  int currentNum;
  // 1) Loop over positions in list
  currentStart = list.listStart->next;// Initialise the loop over list positions variable. Don't need to do it for first case as nothing so sort
  while (currentStart != NULL) // While our current starting point is not the NULL pointer
    {
      // First take the current number we wish to repostition
      currentNum =  currentStart->num;
      // Then start at beginning of list, and find the position it should go in
      loopPtr = list.listStart;
      prevLoopPtr = NULL;

      // Keep incrementing a ptr til we have ptr->next = currentStart
      for (prevCurrentStart = list.listStart; (prevCurrentStart->next) != currentStart; prevCurrentStart = prevCurrentStart->next){};

      
      // If number goes at start of list, update the start of the list
      if (currentNum < list.listStart->num)
	{
	  tempStart = currentStart->next;
	  prevCurrentStart->next = tempStart;
	  currentStart->next = list.listStart;
	  list.listStart = currentStart;
	}
      else
	{ 

	  while ( (currentNum > loopPtr->num) && (loopPtr != currentStart) ) // This terminates when we have found our position
	    {
	      prevLoopPtr = loopPtr;
	      loopPtr = loopPtr->next;
	    } // At this point we want to point currentStart to loopPtr and point prevLoopPtr to currentStart

	 
	  // We now swap the links to get it in the right position
	  tempStart = currentStart->next; // keep track of where currentStart should be set for next loop
	  if (loopPtr != currentStart)
	    {
	      prevCurrentStart->next = tempStart; // We have taken current start completely out of the list
	      prevLoopPtr->next = currentStart;
	      currentStart->next = loopPtr;
	    }
	}   
      // Finally we increment the currentStarting point
      currentStart = tempStart;
    }

  /*  currentStart = list.listStart;
  while (currentStart)
    {
      std::cout << currentStart->num << " ";
      currentStart = currentStart->next;
    }
    std::cout << std::endl; */
  return; 
}

