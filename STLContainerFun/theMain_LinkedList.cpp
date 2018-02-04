
#include "cList.h"
#include <iostream>

int main_LINKEDLIST()
{

	cList myList;

	myList.AddDataAtCurrentNode( "Michael" );
	myList.AddDataAtCurrentNode( "Hermione" );
	myList.AddDataAtCurrentNode( "Voldemort" );
	myList.AddDataAtCurrentNode( "Ron" );
	myList.AddDataAtCurrentNode( "Hagrid" );

	// Hagrid		
	// Ron
	// Voldemort	<-- Current
	// Hermione		
	// Michael

	myList.MoveToNextNode();		// to Ron
	myList.MoveToNextNode();		// to Voldemort
	myList.MoveToNextNode();		// to Hermione
	myList.MoveToNextNode();		// to Michael

	myList.DeleteCurrentNode();		// Current is now Hermionoe

	std::string curName;
	myList.GetDataAtCurrentNode( curName );

	std::cout << curName << std::endl;


	return 0;
}
