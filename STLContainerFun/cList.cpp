#include "cList.h"

cList::cNode::cNode()
{
	this->pNextNode = NULL;
	this->pPrevNode = NULL;
	return;
}		

cList::cList()
{
	this->pFirstNode = NULL;	// 0 or nullptr
	this->pCurrentNode = NULL;	// just in case...

	this->m_numNodes = 0;
	return;
}

void cList::AddDataAtCurrentNode(std::string theData)
{
	// Add a node (with this data)
	cNode* pNEWNode = new cNode();
	pNEWNode->name = theData;
	this->m_numNodes++;

	// Special case: 1st node
	if ( this->pFirstNode == NULL )
	{	
		// No, this is the very first node
		this->pFirstNode = pNEWNode;
		// Also the current node
		this->pCurrentNode = this->pFirstNode;
		// We're done
		return;
	}//if ( this->pFirstNode == NULL )

	// We have nodes AND the pCurrentNode is VALID
	// Insert it at "current" location

	// Hernione:  pNext --> Michael 
	//            pPrev --> NULL
	pNEWNode->pNextNode = this->pCurrentNode;	// H --> M

	// Michael:   pNext --> NULL
	//            pPrev --> Hermione (NEW node)
	this->pCurrentNode->pPrevNode = pNEWNode;   // M --> H

	// FIRST node:	is the current note ALSO the first node?
	if ( this->pCurrentNode == this->pFirstNode )
	{
		//YES, so update the first node to be the new one
		this->pFirstNode = pNEWNode;
	}

	// Update the "current" node
	this->pCurrentNode = pNEWNode;

	return;
}

bool cList::GetDataAtCurrentNode(std::string &theData)
{
	// Are there any nodes? 
	if ( this->pFirstNode == NULL )
	{	// Nope. 
		return false;
	}

	// Yes, there is
	theData = this->pCurrentNode->name;
	return true;
}

void cList::MoveToNextNode(void)	// iterator++
{
	// is there anything in the list?
	if ( this->pCurrentNode == NULL ) {	return; }
	
	// At this point, there ARE nodes 
	cNode* pNEXTnode = this->pCurrentNode->pNextNode;
	
	// Hold on... IS there another node??? 
	if ( pNEXTnode == NULL )
	{	// NO, so DON'T move to the next node as this is the LAST one
		return;
	}

	this->pCurrentNode = pNEXTnode;
}

void cList::MoveToPrevNode(void)	// iterator--
{
	// is there anything in the list?
	if (this->pCurrentNode == NULL) { return; }

	// At this point, there ARE nodes 
	cNode* pPREVnode = this->pCurrentNode->pPrevNode;

	// Hold on... IS there another node??? 
	if (pPREVnode == NULL)
	{	// NO, so DON'T move to the next node as this is the LAST one
		return;
	}

	this->pCurrentNode = pPREVnode;
}

void cList::DeleteCurrentNode(void)	// delete(...)
{
	// is there anything in the list?
	if (this->pCurrentNode == NULL) { return; }

	// Find the next and prev pointers for the current node

	// Voldemort		--> Next: Hermione
	//
	// Hermione			--> Prev: Voldemort
	//					--> Next: Hermione
	//
	// Michael			--> Prev: Hermione

	cNode* pPREVnode = this->pCurrentNode->pPrevNode;  //V  null
	cNode* pNEXTnode = this->pCurrentNode->pNextNode;  //H

	if ( pPREVnode != NULL )
	{	// There IS a node there
		pPREVnode->pNextNode = pNEXTnode;  // V --> H
	}
	else
	{	// The current node IS the FIRST node
		pNEXTnode->pPrevNode = NULL;	// pPREVnode
	}

	if (pNEXTnode != NULL )
	{
		pNEXTnode->pPrevNode = pPREVnode;  // H --> V
	}
	else
	{	// The current node IS the LAST node
		pPREVnode->pNextNode = NULL;	// pNEXTnode;
	}

	// Get rid of current 
	delete this->pCurrentNode;
	this->m_numNodes--;

	// Make sure there is a "next" node
	// (i.e. we are deleting the last node)
	if ( pNEXTnode != NULL )
	{
		this->pCurrentNode = pNEXTnode;
	}
	else
	{	// point the previous node
		this->pCurrentNode = pPREVnode;
	}

	return;
}

void cList::MoveToStart(void)					// begin()
{
	this->pCurrentNode = this->pFirstNode;
	return;
}

void cList::MoveToEnd()						// end()
{
	this->pCurrentNode = this->pLastNode;
	return;
}
unsigned int cList::GetSize(void)
{
	return this->m_numNodes;
}
