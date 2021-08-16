//Core Libraries
#include <iostream>
#include <string>

//Our Headers
#include "DLList.h"

//--- Constructors and Destructor ---//
DLList::DLList() 
{
	first = NULL;
	last = NULL;
	count = 0;
}

DLList::~DLList() {
	clearList(); //Delete all of the nodes in the list
}



//--- Methods ---//
void DLList::addNode(string data)  {
	addNode(data, 5); //Adds a node with the data specified and a default priority of 5
}

void DLList::addNode(string data, int priority)
{
	//Create the new node with the requested data
	node* newNode = new node();
	newNode->data = data;
	newNode->priority = priority;

	//Increment the counter for how many nodes are in the list
	count++;

	//Check if the list is currently empty. If so, add this one then return immediately
	if (first == NULL && last == NULL)
	{
		//Sets the first and last pointers to the new node as it is now the only node in the list
		first = newNode;
		last = newNode;

		//Set the links to NULL since there are no other nodes in the list
		newNode->prev = NULL;
		newNode->next = NULL;

		//Return so we don't go through the loop below
		return;
	}

	//Check if there is only one node in the list. If there is, add this one then return immediately.
	if (first == last)
	{
		//Add the node in front or behind the only existing node depending on the priority
		if (newNode->priority <= first->priority) //If the new node has a higher priority, place the new node in front (1 is highest so check is inverted)
		{
			newNode->next = first; //Placing the new node at the front so it's next node is the now old first node
			first->prev = newNode; //The now old first node's previous node is the new node we just added
			first->next = NULL; //Since there are only 2 elements now, the old first node doesn't have a node after it
			last = first; //Set the last pointer to be the old first node
			first = newNode; //Set the first pointer to be the new node
		}
		else //If the new node has a lower priority, place the new node behind (1 is highest so check is inverted)
		{
			first->next = newNode; //Placing the new node after the first node so the first node's next pointer points to the new node
			newNode->prev = first; //The new node's previous pointer points to the first node
			newNode->next = NULL; //There are only 2 elements so the new node's next pointer is set to NULL (no node after it)
			last = newNode; //Set the last pointer to be the new node
		}

		//Return so we don't go through the loop below
		return;
	}

	//If there are at least two nodes already in the list, cycle through the nodes to find where to add the new node
	//The new node gets added before the 1st element with its same priority
	//Ex: if the priority list was currently 1, 2, 3, 3, 3, 3 and we had the new node with priority 3 (denoted as *3* for clarity),
	//	  the new node would be added in front of the existing priority 3 nodes, so the new list would be 1, 2, *3*, 3, 3, 3, 3	
	for (auto itr = first; itr != last; itr = itr->next )
	{
		//If currently on the first node, have to compare priorities a differently since there is no node BEFORE the first node
		if (itr == first)
		{
			//If the first is lower priority than the new node, place the new node in front of the first node
			if (first->priority >= newNode->priority)
			{
				//Link the new node
				newNode->prev = NULL;
				newNode->next = itr;

				//Update the previous link in the current first node
				first->prev = newNode;

				//Switch the first node to be the new node
				first = newNode;

				//Return since we have placed the node
				return;
			}
		}

		//If not checking against the first node, check against the next in the list since we want to position the new node BEFORE equal priority nodes
		if (itr->next->priority >= newNode->priority)
		{
			//Link the new node
			newNode->next = itr->next;
			newNode->prev = itr;

			//Update the stored links within the adjacent nodes
			itr->next = newNode;
			newNode->next->prev = newNode;

			//Return since we have placed the node
			return;
		}
	}

	//If it couldn't be added into the list before the last element, add it at the end
	last->next = newNode;
	newNode->prev = last;
	newNode->next = NULL;
	last = newNode;
}

void DLList::removeMaxNode()
{
	//Decrement the counter for how many nodes are currently in the list
	count--;

	//Delete the first node
	if (first == NULL && last == NULL) //If the list is empty
	{
		//Output an error message and return if the user is trying to delete from an empty list
		std::cout << "WARNING: You are trying to delete a node from an empty list!" << std::endl;
		return;
	}
	else if (first == last) //If there is only one node in the list
	{
		//Delete the only element in the list
		delete first;

		//Clean up the first element pointer
		first = NULL;

		//Clean up the last element pointer
		last = NULL;
	}
	else //The list is longer than one element
	{
		//Move the first pointer one down the chain
		first = first->next;

		//Delete the old first element
		delete first->prev;

		//Clean up the pointer
		first->prev = NULL;
	}
}

void DLList::removeMinNode() 
{
	//Decrement the counter for how many nodes are currently in the list
	count--;

	//Delete the last node
	if (first == NULL && last == NULL) //If the list is empty
	{
		//Output an error message and return if the user is trying to delete from an empty list
		std::cout << "WARNING: You are trying to delete a node from an empty list!" << std::endl;
		return;
	}
	else if (first == last) //If there is only one node in the list
	{
		//Delete the only element in the list
		delete first;
		
		//Clean up the first element pointer
		first = NULL;

		//Clean up the last element pointer
		last = NULL;
	}
	else //The list exists and is longer than one element
	{
		//Move the last pointer one up the chain
		last = last->prev;

		//Delete the old last element
		delete last->next;

		//Clean up the pointer
		last->next = NULL;
	}
}

void DLList::printList() 
{
	//Output the header above the information to explain the format
	cout << "[<Node ID>] = [<priority> | <data>]" << endl;
	cout << "-----------------------------------" << endl;

	//Holds the node ID so when the data gets output, we know which node it is
	int nodeID = 0;

	//Loop through all of the nodes and output the data listed at the node
	for (auto itr = first; itr != NULL; itr = itr->next, nodeID++)
		cout << "[" << nodeID << "] = [" << itr->priority << " | " << itr->data << "]" << endl;
}

void DLList::clearList()
{
	//Clear the node count
	count = 0;

	//Delete all of the nodes in the list except the last node (including the last node would create an infinite loop)
	for (auto itr = first; itr != last; )
	{
		itr = itr->next;
		delete itr->prev;
		itr->prev = NULL;
	}

	//Delete the last node
	last->prev = NULL;
	last->next = NULL;
	delete last;

	//Clean up the pointers
	last = NULL;
	first = NULL;
}

int DLList::getCount() const {
	return count;
}