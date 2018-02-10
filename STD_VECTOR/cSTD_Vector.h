#ifndef _cSTD_Vector_HG_
#define _cSTD_Vector_HG_

#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "windows.h"
#include "psapi.h"
#include <iostream>

#include "iPersonMotron.h"
#include "cSorter.h"		//	<-- Functor 

#include <numeric>
#include <chrono>

class cSTD_Vector : iPersonMotron
{
public:
	
	std::vector<sPerson*> theVector;
	cSorter mySorter;

	std::vector< std::string > vecFemaleNames;
	std::vector< std::string > vecMaleNames;
	std::vector< std::string > vecLastNames;

	cSTD_Vector();
	~cSTD_Vector();

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

private:
	static int uniqueID;
	eContainerType type;

	sPerfData theCallStats;
	std::chrono::system_clock::time_point start;
	bool b_runPerformanceData = true;
};

#endif