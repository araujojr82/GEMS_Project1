#include "cSmartArray.h"
#include <iostream>

//const unsigned int INITIAL_ARRAY_SIZE = 10;

//static 
const unsigned int cSmartArray::INITIAL_ARRAY_SIZE = 4;

cSmartArray::cSmartArray()
{
	this->m_nextIndexToUse = 0;	// Start at 0
	

	//sPerson* m_pTheData;
	this->m_currentCapacity = INITIAL_ARRAY_SIZE;

	this->m_pTheData = new sPerson[this->m_currentCapacity];

	return;
}

void cSmartArray::insert_at_end(sPerson thePerson)
{
	// Can we insert? (i.e. is there room)
	if ( this->m_nextIndexToUse >= this->m_currentCapacity )
	{	
		// NO, it's too big!

		// Make capacity 2x the current capacity
		unsigned int newCapacity = this->m_currentCapacity * 2;

		this->m_resize(newCapacity);

		this->m_currentCapacity = newCapacity;

		std::cout << "Smart Array capacity now: " << this->m_currentCapacity << std::endl;
	}

	// Array will always be big enough at this point
	// (i.e. location of "end" is less than the capacity)

	// Insert at whereever the "next index" is
	this->m_pTheData[this->m_nextIndexToUse] = thePerson;

	// Increment to the "next" index
	this->m_nextIndexToUse++;

	return;
}


sPerson cSmartArray::lookUpAtIndex(unsigned int index)
{
	return this->m_pTheData[index];
}

// myVec[10] = x;
void cSmartArray::assignAtIndex(unsigned int index, sPerson thePerson)
{
	this->m_pTheData[index] = thePerson;
	return;
}


unsigned int cSmartArray::getSize(void)
{
	return this->m_nextIndexToUse;
}

unsigned int cSmartArray::getCapacity(void)
{
	return this->m_currentCapacity;
}

cSmartArray::~cSmartArray()
{
	// FINE! You win, linker!!
	return;
}

void cSmartArray::m_resize(unsigned int newSize)
{
	// make a new, larger array... 
	sPerson* pTempData =  new sPerson[newSize];

	// Copy the old data to the new location
	for ( int index = 0; index != this->m_currentCapacity; index++ )
	{
		pTempData[index] = this->m_pTheData[index];
	}

	// Delete the old data
	delete [] this->m_pTheData;			// GOTCHA! Watch the []

	// Point the original array pointer to the new data
	this->m_pTheData = pTempData;

	// DON'T DELETE THE NEW ARRAY
	return;
}
