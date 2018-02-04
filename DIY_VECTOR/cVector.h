#ifndef _cVector_HG_
#define _cVector_HG_

#define INITIAL_SIZE 10;

// #include "cPerson.h"

//•	A "smart" or "dynamically grown" array.
//•	In general, behaves like a "regular" array
//•	Insert at end( equivalent to "push_back" )
//•	Insert and delete anywhere( slower than at end )
//•	Indexed on integer, starting at 0
//•	Access using index( STL uses operator[] for this )
//•	Find on index takes O( 1 ) time; finding data takes O( n ) time( linear search )

// This class "works" like a STD vector
// I had to use templates because I'm using this class for more than one type
template <class Type >
class cVector
{
public:
	cVector( )
	{
		this->myIndex = 0;
		
		this->myCapacity = INITIAL_SIZE;

		this->myData = new Type[this->myCapacity];
	};

	~cVector(){};

	// Clear the cVector and start a new one with the same capacity
	void clear()
	{
		this->myIndex = 0;		
		delete[] this->myData;	// Delete the old vector data
		this->myData = new Type[this->myCapacity];
		return;
	}

	// TODO
	//void insert_at();

	// Insert the 'value' at the end of the cVector
	void push_back( Type value ) // same as push_back(value);
	{
		if( this->myIndex >= this->myCapacity )
		{	// Vector is Full
			// Double its capacity 			
			this->resize( this->myCapacity * 2 );
			this->myCapacity *= 2;
		}

		this->myData[this->myIndex] = value;
		this->myIndex++;

		return;
	}

	// Returns the value at the position 'index' of the cVector
	Type get( unsigned int index )	// same as return vector[index]
	{
		return this->myData[index];
	}

	// Set 'value' at the position 'index' of the cVector
	void set( unsigned int index, Type value ) // same as vector[index] = value
	{
		if( index <= this->myCapacity )
		{
			this->myData[index] = value;
		}		
		return;
	}

	// Returns the current size of the cVector
	unsigned int size( void )		//same as size()
	{
		return this->myIndex;
		return 0;
	}
	
	// Returns the current capacity of the cVector
	unsigned int capacity( void )	// same as capacity()
	{
		return this->myCapacity;
		return 0;
	}

private:
	Type* myData;

	unsigned int myIndex;
	unsigned int myCapacity;

	void resize( unsigned int newCapacity )
	{
		Type* pTemVector = new Type[newCapacity];

		// Copy the current data to the larger temp Vector
		for( int index = 0; index != this->myCapacity; index++ )
		{
			pTemVector[index] = this->myData[index];
		}

		// Delete the old vector data
		delete[] this->myData;

		// The Vector Data will now be the tempVector
		this->myData = pTemVector;

		return;
	}

};

#endif
