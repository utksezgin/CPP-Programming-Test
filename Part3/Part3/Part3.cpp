/*
Program to clone a linked list with a random reference to a node in the list without any dependencies. Time complexity is O(n) and n is the number of nodes in the list.
The program is optimized by using unordered_map instead of other containers like vector which decreased the time complexity from O(n^2) to O(n)
*/

#include "pch.h"
#include <iostream>
#include <unordered_map>

struct node
{
	struct node *next;
	struct node *reference;
	int value;
};

//Gives a copy of given list without any dependency.
node* cloneList(node *list);
//Helper function to print the list.
void printList(node* startNode);
//Helper function for cleaning up allocated memories on cloned list.
void freeList(node* startNode);

int main()
{
	//Simple driver for personal testing.
	node startNode;
	startNode.value = 1;
	node n2;
	n2.value = 2;
	node n3;
	n3.value = 3;
	node n4;
	n4.value = 4;

	startNode.next = &n2;
	startNode.reference = &n4;
	n2.next = &n3;
	n2.reference = &n3;
	n3.next = &n4;
	n3.reference = &startNode;
	n4.next = nullptr;
	n4.reference = &n2;


	try {
		//Cloning the list.
		node* clonedList = cloneList(&startNode);
		std::cout << "Cloned list:" << std::endl;
		printList(clonedList);

		//Dependency Check
		int i = 0;
		node* iterator = clonedList;
		while (iterator) {
			iterator->value = i * i;
			iterator = iterator->next;
			++i;
		}
		std::cout << "--------Dependency Check after changes on clone list--------" << std::endl;
		std::cout << "Updated cloned List:" << std::endl;
		printList(clonedList);
		std::cout << "Original List:" << std::endl;
		printList(&startNode);

		//Clean-up.
		freeList(clonedList);
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}

}

node* cloneList(node *list) {
	//Empty list
	if (list == nullptr) {
		throw std::runtime_error("List empty exception"); //TODO: Check this.
	}

	//unordered_map was used to benefit from it's access time of [] operator being constant time. There are quite a lot of accesses so unordered_map is the optimal ADT to use here.
	std::unordered_map<node*, node*> cloneOriginalMap;

	//Initializing starting node.

	//Iterators for both clone list and input list to go through the lists.
	node* currentClone = nullptr;
	node* listIterator = list;

	//Storing original list's nodes matched as clone's nodes without setting up next and references.
	//The idea is to create a new node for each node in original list to match them so that,
	//If we give a reference node to [] operator, we can get the cloned version of the node so we can bind it to the cloned node's reference node.
	while (listIterator) {
		node* nextNode = new node();
		nextNode->value = listIterator->value;
		currentClone = nextNode;
		cloneOriginalMap[listIterator] = currentClone;

		listIterator = listIterator->next;
	}

	//Assigning start node to iterator to iterate through again.
	listIterator = list;

	//Setting up next and reference nodes of clone nodes. Giving a node to [] operator of unordered_map will return the cloned version of the node and the access time takes O(1) time.
	while (listIterator) {
		currentClone = cloneOriginalMap[listIterator];
		currentClone->next = cloneOriginalMap[listIterator->next];
		currentClone->reference = cloneOriginalMap[listIterator->reference];
		listIterator = listIterator->next;
	}

	node* newList = cloneOriginalMap[list];
	return newList;
}


void printList(node* startNode) {
	if (startNode == nullptr) {
		throw std::runtime_error("List empty exception"); //TODO: Check this.
	}
	node *iterator = startNode;

	while (iterator) {
		std::cout << "Value: " << iterator->value << " " << "Reference Value: " << iterator->reference->value << std::endl;
		iterator = iterator->next;
	}
}

//Deallocates allocated memories on cloned list.
void freeList(node* startNode) {
	node* tempNode = startNode;
	while (startNode->next) {
		tempNode = startNode->next;
		delete startNode;
		startNode = tempNode;
	}
	delete tempNode;
}