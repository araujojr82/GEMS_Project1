#ifndef _cList_HG_
#define _cList_HG_

#include <string>

// This is the DIY List...
class cList
{
public:
	// "nested class"
	// This is the thing that actually holds the data
	class cNode
	{
	public:
		cNode();
		std::string name;	// Data we want
		cNode* pNextNode;
		cNode* pPrevNode;
	};
	// "nested class"


	cList();	
//	~cList();
	// The list holds "nodes", which hold data
	// (and they also hold the 'linking stuff')
	cNode* pFirstNode;		// Start of the entire list
	cNode* pLastNode;		// Start of the entire list

	cNode* pCurrentNode;	// Current node

	void AddDataAtCurrentNode( std::string theData );	// insert(...)
	void DeleteCurrentNode(void);	// delete(...)
	bool GetDataAtCurrentNode( std::string &theData );
	//std::string	GetDataAtCurrentNode(void);		Why not this way?

	// STL iterator, but inside the list itself
	void MoveToNextNode(void);				// iterator++
	void MoveToPrevNode(void);				// iterator--
	void MoveToStart(void);					// begin()
	void MoveToEnd();						// end()

	unsigned int GetSize(void);
	void ClearAll(void);

private:
	unsigned int m_numNodes;

};


#endif
