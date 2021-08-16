//Core Libraries
#include <chrono>
#include <stdlib.h>

//1st Party Headers
#include "DLList.h"

//Chrono namespace
using namespace std::chrono;

//A bunch of random 10 letter words to be used as the node data
//Found on http://www.yougowords.com/10-letters
string randomStrings[] = { "everything", "silhouette", "restaurant", "adaptation", "basketball",
						 "helicopter", "loneliness", "understand", "watermelon", "confidence" };

void main()
{
	//Instantiate the list
	DLList linkedList;

	//Seed the random number generator
	srand(time(0));

	//Loop until the user exits to allow for multiple operations
	while (true)
	{
		//Get the number of entries in the list from the user
		int numEntries;
		cout << "Please enter the number of entries you want in the list. Entering a negative number will terminate the program\n>>>";
		cin >> numEntries;

		//Exit if the user enters a negative number
		if (numEntries < 0)
			exit(0);

		//Add the random entries
		for (int i = 0; i < numEntries; i++)
		{
			//Randomize the priority between 1 and 99
			int priorityNumber = rand() % 99 + 1;

			//Randomize the index for the random strings to be used as the data
			int stringNumber = rand() % 10;

			//Add the node with the random values
			linkedList.addNode(randomStrings[stringNumber], priorityNumber);
		}

		//Get the current system time
		auto startTime = std::chrono::high_resolution_clock::now();

		//Call the function that we're timing
		//linkedList.addNode("-NEW NODE-");
		//linkedList.removeMaxNode();
		//linkedList.removeMinNode();
		linkedList.printList();

		//Get the new system time after performing the function
		auto endTime = std::chrono::high_resolution_clock::now();

		//Calculate the time difference
		std::chrono::duration<double> executionTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

		//Output the time difference
		std::cout << "Program Time = " << executionTime.count() << "s" << std::endl;
		
		//Clear the list for the next set of instructions
		linkedList.clearList();
	}
}