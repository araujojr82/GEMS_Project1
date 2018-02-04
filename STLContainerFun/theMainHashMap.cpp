
#include "cHashMap.h"
#include <iostream>

int main3()
{
	cHashMap myMapByFirstName;

	sWizard Voldemort;
	Voldemort.first = "Voldemort";	Voldemort.last = "Riddle";
	Voldemort.health = 100.0f;

	sWizard Hermione;
	Hermione.first = "Hermione";	Hermione.last = "Granger";
	Hermione.health = 100.0f;

	sWizard Harry;
	Harry.first = "Harry";	Harry.last = "Potter";
	Harry.health = 100.0f;

	sWizard Michael;
	Michael.first = "Michael";	Michael.last = "Feeney";
	Michael.health = 100.0f;

	myMapByFirstName.addWiz( Voldemort.first, Voldemort );
	myMapByFirstName.addWiz( Hermione.first, Hermione );
	myMapByFirstName.addWiz( Harry.first, Harry );
	myMapByFirstName.addWiz( Michael.first, Michael );

	sWizard foundWiz;
	if ( myMapByFirstName.findWiz( "Harry", Harry ) )
	{
		std::cout << "Found voldemort!" << std::endl;
		std::cout << foundWiz.first << " " 
			<< foundWiz.last << " " 
			<< foundWiz.health << std::endl;
	}
	else
	{	
		std::cout << "Didn't find it" << std::endl;
	}

	return 0;
}