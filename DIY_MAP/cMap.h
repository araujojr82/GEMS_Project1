#ifndef _cMap_HG_
#define _cMap_HG_

#include <iostream>

#include "../DIY_LIST/cList.h"

#define INITIAL_SIZE 300;

//•	STL usually implements as a "red-black tree". Suggestion is to use a "hash map"
//•	Insert, delete, lookup: O( log n ) time
//•	Find takes O( log n ) time if searching by index, O( n ) time( linear search ) otherwise

// This class "works" like a STD List
// I had to use templates because I'm using this class for more than one type
template <class Type >
class cMap
{
public:

	//cMap( int capacity ) : 
	//	this->mySize( 0 ),
	//	this->myCapacity( capacity ),
	//	this->myData( new cList<Type>[this->myCapacity] ) {}

	cMap()
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
		
		if( theHash >= this->myCapacity )
		{
			this->resize( this->myCapacity * 2 );
			this->myCapacity *= 2;
		}

		this->myData[theHash].push_back( value );
		this->myData[theHash].isValid = true;
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

	// Returns the value at the position (hashed string) of the cMap
	cList<Type> get( std::string hashBy )	// same as return vector[index]
	{
		// Generate the hash for the given hash string 
		unsigned int theHash = this->getHash( hashBy );

		return this->myData[theHash];
	}

	// Set the value of a position to the new value
	void set( int index, cList<Type> value )	// same as return vector[index]
	{
		this->myData[index] = value;

		return;
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
		std::string theHashString;

		int char0Value = ( unsigned int )strToBeHashed[0];
		int char1Value;

		std::string char0String;
		std::string char1String;
		std::string char2String;

		// Check for the fisrt char of the string
		if( char0Value > 64 )						// It's a String
		{
			char0Value -= 64;
			char1Value = ( unsigned int )strToBeHashed[1] - 64;

			char0String = std::to_string( char0Value );
			char1String = std::to_string( char1Value );

			if( char1String.size() == 1 )		// if the second char value is less than 10
			{									// add a 0 in front of it
				char1String = "0" + char1String;
			}
			theHashString = char0String + char1String;

			theHash = stoi( theHashString ) / 10;
		}
		else										// It's a number
		{
			for( int index = 0; index != strToBeHashed.size(); index++ )
			{
				if( strToBeHashed[index] == '.' ) break; // Stop if it reaches '.'
				theHashString += strToBeHashed[index];
			}
			theHash = stoi( theHashString );
		}		

		return theHash;
	}
	
	void resize( unsigned int newCapacity )
	{
		// Make a new map with the new capacity
		cList<Type>* tempMap = new cList<Type>[newCapacity];

		// Copy the current data to the larger temp Map
		for( int index = 0; index != this->myCapacity; index++ )
		{
			tempMap[index] = this->myData[index];
		}
		
		// Delete the old vector data
		delete[] this->myData;

		// The Vector Data will now be the tempVector
		this->myData = tempMap;

		return;
	}	

};

#endif
