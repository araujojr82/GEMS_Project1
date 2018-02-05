#ifndef _cList_HG_
#define _cList_HG_

#define INITIAL_SIZE 10;

//•	Singly or doubly linked list
//•	Insert and delete anywhere "O(1)"
//•	Find takes O( n ) time
//•	"MoveNext", "MovePrevious", "MoveToStart", "MoveToEnd" functionality( implemented in iterators in STL library )
//•	Find takes O( n ) time( linear search )

// This class "works" like a STD List
// I had to use templates because I'm using this class for more than one type
template <class Type >
class cList
{
public:

	class cNode
	{
	public:
		cNode()
		{
			this->pNext = NULL;
			this->pPrev = NULL;
			return;
		}
		Type value;		// Stores data of any Type
		cNode* pNext;
		cNode* pPrev;
	};

	cNode* pFirst;		// First Node of the List
	cNode* pLast;		// The Last Node of the List
	cNode* pCurrent;	// Current node

	cList( )
	{
		this->pFirst = NULL;	// 0 or nullptr
		this->pCurrent = NULL;	// just in case...

		this->size = 0;
		return;
	};

	~cList(){};

	// Clear the cList and start a new one with the same capacity
	void clear()
	{
		//this->myIndex = 0;		
		//delete[] this->myData;	// Delete the old vector data
		//this->myData = new Type[this->myCapacity];
		//return;
	}

	// Insert the 'value' at the end of the cList
	void push_back( Type value ) // same as push_back(value);
	{
		//if( this->myIndex >= this->myCapacity )
		//{	// Vector is Full
		//	// Double its capacity 			
		//	this->resize( this->myCapacity * 2 );
		//	this->myCapacity *= 2;
		//}

		//this->myData[this->myIndex] = value;
		//this->myIndex++;

		return;
	}

	// Insert the 'value' at the current position
	void insert( Type value )
	{
		cNode* pNewNode = new cNode();

		pNewNode->value = value;
		
		this->size++;
											
		if( this->pFirst == NULL )			// | First | Current | Last | 
		{ // The list is empty				// |  NULL |   NULL  | NULL |
			this->pFirst   = pNewNode;		// |  New  |   NULL  | NULL |
			this->pCurrent = pNewNode;		// |  New  |   New   | NULL |
			this->pLast   = pNewNode;		// |  New  |   New   | New  |
		}
		else
		{ // The list has value
			pNewNode->pNextNode = this->pCurrent;	// Set the current node as the Next of this one

			this->pCurrent->pPrevNode = pNewNode;	// Set the previous node of the current to this

			if( this->pCurrent == this->pFirst )	// If the current is the also the first... 
			{
				this->pFirst = pNewNode;			// The new node is the first now
			}
			this->pCurrent = pNewNode;				// Finally, update the current node to be the new
		}
		 
		return;
	}

	// Delete the value at the CURRENT position
	void erase()
	{
		if( this->pCurrent == NULL )
		{ // The list is empty
			return; 
		}
		else
		{
			// Find the next and prev pointers for the current node
			cNode* pThePrev = this->pCurrent->pPrev;
			cNode* pTheNext = this->pCurrent->pNext;

			if( pThePrev == NULL )				// The Current node is the First
				pTheNext->pPrev = NULL;
			else	
				pThePrev->pNext = pTheNext;

			if( pTheNext == NULL )				// The Current node is the Last
				pThePrev->pNext = NULL;
			else
				pTheNext->pPrev = pThePrev;

			delete this->pCurrent;				// Delete Current node
			this->m_numNodes--;					// Decrease size by one

			if( pTheNext != NULL )				// If current node is the last
				this->pCurrent = pTheNext;
			else								// point the previous node			
				this->pCurrent = pThePrev;

			return;
		}
	}

	// Delete the value at the 'index' position
	void erase( unsigned int index )
	{

	}

	// Set 'value' at the position 'index' of the cList
	void set( unsigned int index, Type value ) // same as vector[index] = value
	{
		//if( index <= this->myCapacity )
		//{
		//	this->myData[index] = value;
		//}
		return;
	}

	// Returns the value at the position 'index' of the cList
	Type get( unsigned int index )	// same as return vector[index]
	{
		//return this->myData[index];
		return NULL;
	}

	void moveToPrev( void )
	{
		return;
	}

	void moveToNext( void )
	{
		return;
	}

	void moveToFirst( void )
	{
		return;
	}

	void moveToLast( void )
	{

		return;
	}


	// Returns the current size of the cList
	unsigned int size( void )		//same as size()
	{
		return this->mySize;
	}
	
	// Returns the current capacity of the cList
	unsigned int capacity( void )	// same as capacity()
	{
		//return this->myCapacity;
		return 0;
	}

private:

	unsigned int mySize;

	//Type* myData;

	//unsigned int myIndex;
	//unsigned int myCapacity;

	//void resize( unsigned int newCapacity )
	//{
	//	Type* pTemVector = new Type[newCapacity];

	//	// Copy the current data to the larger temp Vector
	//	for( int index = 0; index != this->myCapacity; index++ )
	//	{
	//		pTemVector[index] = this->myData[index];
	//	}

	//	// Delete the old vector data
	//	delete[] this->myData;

	//	// The Vector Data will now be the tempVector
	//	this->myData = pTemVector;

	//	return;
	//}

};

#endif
