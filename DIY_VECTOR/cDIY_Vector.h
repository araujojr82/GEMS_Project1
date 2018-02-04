#ifndef _cSTD_Vector_HG_
#define _cSTD_Vector_HG_

#include <fstream>
#include <vector>
#include <time.h>
//#include <algorithm>

#include "iPersonMotron.h"
#include "cSorter.h"		//	<-- Functor 
#include "cVector.h"

class cDIY_Vector : iPersonMotron
{
public:
	
	cSorter mySorter;
	
	//std::vector<sPerson*> theVector;

	//std::vector< std::string > vecFemaleNames;
	//std::vector< std::string > vecMaleNames;
	//std::vector< std::string > vecLastNames;

	cVector<sPerson*> theVector;

	cVector< std::string > vecFemaleNames;
	cVector< std::string > vecMaleNames;
	cVector< std::string > vecLastNames;

	cDIY_Vector();
	~cDIY_Vector();

	bool LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
		std::string firstNameMaleFileName,
		std::string lastNameFileName );
						 
	bool GenerateRandomPeople( int numberOfPeople );

	bool FindPeopleByName( std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople = INT_MAX );


	bool FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople = INT_MAX );

	bool FindPersonByID( sPerson &person, unsigned long long uniqueID );

	bool FindPeople( std::vector<sPerson> &vecPeople, sPoint location, float radius,
		int maxPeopleToReturn = INT_MAX );

	bool FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX );

	bool FindPeople( std::vector<sPerson> &vecPeople,
		sPoint location, float radius, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX );

	bool SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType );

	bool GetPerformanceFromLastCall( sPerfData &callStats );

	// Returns the enum from the cPerson.h file
	eContainerType getContainerType( void );

	int getPersonID();

private:
	static int uniqueID;
	eContainerType type;
};

#endif