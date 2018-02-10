#ifndef _cDIY_List_HG_
#define _cDIY_List_HG_

#include <fstream>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <numeric>
#include <chrono>

#include "iPersonMotron.h"
#include "cSorter.h"		//	<-- Functor 
#include "cList.h"

class cDIY_List : iPersonMotron
{
public:
	
	cSorter mySorter;
	
	cList<sPerson*> theList;

	cList< std::string > listFemaleNames;
	cList< std::string > listMaleNames;
	cList< std::string > listLastNames;

	cDIY_List();
	~cDIY_List();

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

	void startPerformanceData( void );
	void stopPerformanceData( void );

	int getPersonID();
	bool sortList( eSortType sortType );

private:
	static int uniqueID;
	eContainerType type;

	sPerfData theCallStats;
	std::chrono::system_clock::time_point start;
	bool b_runPerformanceData = true;
};

#endif