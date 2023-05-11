#include "processList.h"

Process* ProcessList::searchById(int id, int& pos)
{
	Node<Process*>* temp = headPtr;
	for (int i = 0; i < size; i++)
	{
		if (temp->getItem()->getId() == id) {
			pos = i;
			return temp->getItem();
		}

		temp = temp->getNext();
	}

	pos = -1;
	return nullptr;
}