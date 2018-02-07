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
	
	//cMap<sPerson*> theMap;
	// Basically it will store multiple maps, one for each key type
	// First Name, Last Name, UniqueID and Health will have their own map
	// This way there's no need for sorting the map itself, just the elements
	// in the cList of each position
	cMap<sPerson*> theMapByFirst;	//ASC_FIRST_THEN_LAST
	cMap<sPerson*> theMapByLast;	//ASC_LAST_THEN_FIRST
	cMap<sPerson*> theMapByID;		//ASC_BY_ID
	cMap<sPerson*> theMapByHealth;	//ASC_BY_HEALTH


	cMap< std::string > mapFemaleNames;
	cMap< std::string > mapMaleNames;
	cMap< std::string > mapLastNames;

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