// Sorted Doubly Linked List
// The list is sorted based on priority, with the item that has the lowest priority at the front of the list.

#ifndef DLLIST_H
#define DLLIST_H

//Core Libraries
#include <iostream>
#include <string>

//Standard namespace
using namespace std;

/*
	Node Struct
	- Small structure that contains a minimal amount of data
	- Has the following data members:
		> A priority level indicating this node's position within the list
		> A pointer to the actual data this node contains
		> A pointer to the next node in the list
		> A pointer to the previous node in the list
*/
struct node 
{
	int priority;
	string data;
	node *next;
	node *prev;
};

/*
	DLList Class
	- Stands for Doubly Linked List
	- A list that is made up of a bunch of nodes, each of which is linked to the previous and next node in the list
	- Contains the following data members:
		* Pointer to the first node in the list
		* Pointer to the last node in the list
		* A count of how many nodes are currently in the list
	- Contains the following methods:
		* AddNode (Overload 1)
			> Takes a string for the node's data as well as the priority level for the node
			> Links the new node correctly at the right location in the list
		* AddNode (Overload 2)
			> Only takes the string for the data
			> The priority level for the node is simply defaulted to 5
			> Performs all of the other tasks as the first overload
		* RemoveMaxNode
			> Takes no parameters
			> Destroys the node that has the highest priority (ie: start of the list)
		* RemoveMinNode
			> Takes no parameters
			> Destroys the node that has the lowest priority (ie: end of the list)
		* PrintList
			> Iterates through the list and outputs the data in order of priority
*/
class DLList 
{
public:
	//--- Constructors and Destructor ---//
	DLList();
	~DLList();

	//--- Methods ---//
	void addNode(string data, int priority); //Add a node to the list and put it in the correct place
	void addNode(string data); //Add a note to the list with a priority of 5
	void removeMaxNode(); //Remove the node with the maximum priority
	void removeMinNode(); //Remove the node with the lowest priority
	void printList(); // Print the content of the whole list
	void clearList(); //Delete all of the nodes in the list
	int getCount() const; //Return how many nodes are currently in the list

private:
	//--- Data Members ---//
	node *first; // pointer to the first node in the list
	node *last; // pointer to the last node in the list
	int count; //How many nodes are in the list
};
#endif
