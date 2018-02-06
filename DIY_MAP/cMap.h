#ifndef _cMap_HG_
#define _cMap_HG_

#include "../DIY_LIST/cList.h"

#define INITIAL_SIZE 200;

//•	STL usually implements as a "red-black tree". Suggestion is to use a "hash map"
//•	Insert, delete, lookup: O( log n ) time
//•	Find takes O( log n ) time if searching by index, O( n ) time( linear search ) otherwise

// This class "works" like a STD List
// I had to use templates because I'm using this class for more than one type
template <class Type >
class cMap
{
public:

	cMap( )
	{
		this->mySize = 0;
		this->myCapacity = INITIAL_SIZE;
		this->myData = new cList<Type>[this->myCapacity];

		return;
	}

	void clear()
	{
		this->mySize = 0;
		delete[] this->myData;
		this->myData = new cList<Type>[this->myCapacity];

		return;
	}

	// Insert the 'value' at the current position
	void insert( Type value, std::string hashBy )
	{
		// Generate the hash for the given hash string 
		unsigned int theHash = this->getHash( hashBy );

		//// Check if the cList at this hash position exists		
		//if( this->myData[theHash].size() == 0)
		//{	// Nothing stored in this position yet			
		//	cList< Type > newList;
		//	newList.push_back( value );
		//	this->myData[theHash] = newList;			
		//}
		//else
		//{	// There's already a cList at this position
		//	this->myData[theHash].push_back( value );
		//}
		// Actually dont check anything
		this->myData[theHash].push_back( value );
		this->mySize++;
		 
		return;
	}

	// Delete the value at the 'index' position
	void erase( unsigned int index )
	{
		this->moveTo( index );
		this->erase();
		this->mySize--;
	}

	// Returns the value at the position 'index' of the cMap
	cList<Type> get( int index )	// same as return vector[index]
	{
		return this->myData[index];
	}

	cList<Type> get( std::string hashBy )	// same as return vector[index]
	{
		// Generate the hash for the given hash string 
		unsigned int theHash = this->getHash( hashBy );

		return this->myData[theHash];
	}

	// Returns the current size of the cMap
	unsigned int size( void )		//same as size()
	{
		//return this->mySize;
		return this->myCapacity;
	}

private:

	unsigned int mySize;	
	unsigned int myCapacity;

	cList<Type>* myData;	// The map is an Array of cLists

	unsigned int getHash( std::string strToBeHashed )
	{
		// Take ASCII value for each letter and add them up!
		unsigned int theHash = 0;

		for( int index = 0; index != strToBeHashed.size(); index++ )
		{
			char curChar = strToBeHashed[index];

			theHash += ( unsigned int )curChar;
		}

		// 2. divide hash by size of the array
		theHash = theHash % INITIAL_SIZE;

		return theHash;
	}

	//bool m_getWizAt( unsigned int index );

	
	

};

#endif
