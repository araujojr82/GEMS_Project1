#ifndef _cSmartArray_HG_
#define _cSmartArray_HG_

#include "cPerson.h"

// This is the DIY Vector...
class cSmartArray
{
public:
	cSmartArray();
	~cSmartArray();

	void insert_at_end( sPerson theThing);	// Push_Back()  "insert_at_end"
	sPerson lookUpAtIndex( unsigned int index );	// int x = myVec[10];
	void assignAtIndex( unsigned int index, sPerson theThing);		// myVec[10] = x;
	
	unsigned int getSize(void);
	unsigned int getCapacity(void);

private:
	// c style array
	sPerson* m_pTheData;	


	unsigned int m_nextIndexToUse;		// Start at 0
	unsigned int m_currentCapacity;		// Max size of array

	// You can do this in C++98 if this is an integer... (not anything else, though)
	static const unsigned int INITIAL_ARRAY_SIZE;// = 10;


	void m_resize(unsigned int newSize);
	
};
// The "sPerson* m_pTheData" is a c-style array that will be this:
//sPerson* m_pTheData = new sPerson[100];

#endif



// You could also make this a template if you'd like
//
//cSmartArray<sPerson> sexyVector;
//
//template <class T>
//class cSmartArray
//{
//public:
//	cSmartArray();
//	~cSmartArray();
//	void insert_at_end(T theThing);	// Push_Back()  "insert_at_end"
//	T lookUpAtIndex(unsigned int index);
//	void assignAtIndex(unsigned int index, T theThing);
//	unsigned int getSize(void);
//	unsigned int getCapacity(void);
//};
//
//#include "evilActualTemplateCode.inc"

