#ifndef _cDIY_Map_HG_
#define _cDIY_Map_HG_

#include <fstream>
#include <vector>
#include <time.h>

#include "iPersonMotron.h"
#include "cSorter.h"		//	<-- Functor 
#include "cMap.h"

class cDIY_Map : iPersonMotron
{
public:
	
	cSorter mySorter;
	
	cMap<sPerson*> theList;

	cMap< std::string > listFemaleNames;
	cMap< std::string > listMaleNames;
	cMap< std::string > listLastNames;

	cDIY_Map();
	~cDIY_Map();

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