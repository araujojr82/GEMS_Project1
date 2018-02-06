#include "cHashMap.h"

cHashMap::cHashMap()
{
	this->m_ArraySize = cHashMap::INITALARRAYSIZE;

	//sWizard* pWizards;
	this->pWizards = new sWizard[this->m_ArraySize];

	return;
}

// Note: this one WON'T handle clashes
// To do that, either:
// 1. come up with a better hash function (no conflicts)
// 2. increase the size of the array once there is a conflict
//	  (note: when you copy the data into the new array, 
//     you can STILL get conflicts, but eventually you won't)
// 3. Add a linked list (or a simple array) at each 
//    location. When there is a conflict, store another 
//    one at that location. 
//    During lookup: 
//    - if there is ONE item, return it
//    - if there are GT one item, scan through list-array
//      until you find it (remember, it's indexed by name
//      or whatever)

void cHashMap::addWiz(std::string name, sWizard theWizard)
{
	// 1. calculate the hash for that name
	unsigned int theHash = this->m_genIndexHash(name);

	//// 2. divide hash by size of the array
	//theHash = theHash % cHashMap::INITALARRAYSIZE;

	// 3. Place wizard in that index location
	this->pWizards[theHash] = theWizard;
	this->pWizards[theHash].bIsValid = true;

	return;
}

bool cHashMap::findWiz(std::string name, sWizard &theWizard)
{
	// 1. calculate the hash for that name
	unsigned int theHash = this->m_genIndexHash(name);

	// Is there a wizard ther? 
	if ( this->pWizards[theHash].bIsValid )
	{
		theWizard = this->pWizards[theHash];
		return true;
	}

	return false;
}


unsigned int cHashMap::m_genIndexHash(std::string name)
{
	// Take ASCII value for each letter and add them up!
	unsigned int theHashValue = 0;

	for ( int index = 0; index != name.size(); index++ )
	{
		char curChar = name[index];

		theHashValue += (unsigned int)curChar;
	}

	// 2. divide hash by size of the array
	theHashValue = theHashValue % cHashMap::INITALARRAYSIZE;

	return theHashValue;
}



//bool findWiz(std::string name,
//			 sWizard &theWizard);
