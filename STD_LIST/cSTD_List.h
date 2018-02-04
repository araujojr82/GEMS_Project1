#ifndef _cSTD_Vector_HG_
#define _cSTD_Vector_HG_

#include <fstream>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>

#include "iPersonMotron.h"
#include "cSorter.h"		//	<-- Functor 


class cSTD_List : iPersonMotron
{
public:
	
	std::list<sPerson*> theList;
	cSorter mySorter;

	std::list< std::string > listFemaleNames;
	std::list< std::string > listMaleNames;
	std::list< std::string > listLastNames;

	cSTD_List();
	~cSTD_List();

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