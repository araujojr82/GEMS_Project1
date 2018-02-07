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
	bool isValid;

	cList( )
	{
		this->pFirst = NULL;
		this->pLast  = NULL;
		this->pCurrent = NULL;
		this->isValid = false;
		this->mySize = 0;
		return;
	}

	~cList(){}

	// Clear the cList and start a new one with the same capacity
	void clear()
	{
		//this->myIndex = 0;		
		//delete[] this->myData;	// Delete the old vector data
		//this->myData = new Type[this->myCapacity];
		//return;
	};

	// Insert the 'value' at the end of the cList
	void push_back( Type value ) // same as push_back(value);
	{
		cNode* pNewNode = new cNode();

		pNewNode->value = value;
				
		if( this->mySize == 0 )			    // | First | Current | Last | 
		{ // The list is empty				// |  NULL |   NULL  | NULL |
			this->pFirst = pNewNode;		// |  New  |   NULL  | NULL |
			this->pCurrent = pNewNode;		// |  New  |   New   | NULL |
			this->pLast = pNewNode;			// |  New  |   New   | New  |
		}
		else
		{
			this->moveToLast();
			pNewNode->pPrev = this->pCurrent;
			this->pLast = pNewNode;
			this->pCurrent->pNext = this->pLast;
			this->pCurrent = this->pLast;
		}
		this->mySize++;

		return;
	}

	// Insert the 'value' at the current position
	void insert( Type value )
	{
		cNode* pNewNode = new cNode();

		pNewNode->value = value;
													
		if( this->mySize == 0 )			    // | First | Current | Last | 
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
		this->mySize++;
		 
		return;
	}

	// Delete the value at the 'index' position
	void erase( unsigned int index )
	{
		this->moveTo( index );
		this->erase();
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
			this->mySize--;

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

	// Set 'value' at the position 'index' of the cList
	void set( unsigned int index, Type value ) // same as vector[index] = value
	{
		this->moveTo( index );
		this->pCurrent->value = value;
		return;
	}

	// Returns the value at the position 'index' of the cList
	Type get( unsigned int index )	// same as return vector[index]
	{
		this->moveTo( index );
		return this->pCurrent->value;
	}

	void moveTo( unsigned int index )
	{
		this->moveToFirst();
		for( int i = 0; i <= index; i++ )
		{
			this->moveToNext();
		}
	}

	void moveToPrev( void )
	{
		if( this->pCurrent != this->pFirst )		// Don't move if it is the first 
		{	
			this->pCurrent = this->pCurrent->pPrev;
		}		
		return;
	}

	void moveToNext( void )
	{
		if( this->pCurrent != this->pLast )			// Don't move if it is the last 
		{
			this->pCurrent = this->pCurrent->pNext;
		}
		return;
	}

	void moveToFirst( void )
	{
		this->pCurrent = this->pFirst;
		return;
	}

	void moveToLast( void )
	{
		this->pCurrent = this->pLast;
		return;
	}

	// Returns the current size of the cList
	unsigned int size( void )		//same as size()
	{
		return this->mySize;
	}

private:

	unsigned int mySize;

};

#endif
