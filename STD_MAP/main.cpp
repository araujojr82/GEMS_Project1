#include "cPerson.h"
#include <iostream>
#include "cSTD_Map.h"

cSTD_Map* theSTDMap;

//std::string error;

void printVector( std::vector<sPerson*> &theVector )
{
	std::cout << "ID\tage\thealth\tlocation\tfirst and last name" << std::endl;

	for( int i = 0; i != theVector.size(); i++ )
	{
		std::cout
			<< theVector[i]->uniqueID << "\t"
			<< theVector[i]->age << "\t"
			<< theVector[i]->health << "\t"
			<< theVector[i]->location.x << ", "
			<< theVector[i]->location.y << ", "
			<< theVector[i]->location.z << "\t"
			<< theVector[i]->first << " "
			<< theVector[i]->last
			<< std::endl;
	}
}

void printVector( std::vector<sPerson> &theVector )
{
	std::cout << "ID\tage\thealth\tlocation\tfirst and last name" << std::endl;

	for( int i = 0; i != theVector.size(); i++ )
	{
		std::cout
			<< theVector[i].uniqueID << "\t"
			<< theVector[i].age << "\t"
			<< theVector[i].health << "\t"
			<< theVector[i].location.x << ", "
			<< theVector[i].location.y << ", "
			<< theVector[i].location.z << "\t"
			<< theVector[i].first << " "
			<< theVector[i].last
			<< std::endl;
	}
}


int main( int argc, char* argv[] )
{

	theSTDMap = new cSTD_Map();

	theSTDMap->LoadDataFilesIntoContainer( "../dist.female.first.txt",
											  "../dist.male.first.txt",
											  "../US_LastNames.txt" );
	theSTDMap->GenerateRandomPeople( 1000 );

	//printVector( theSTDMap->theMap );
	//std::cout << std::endl;

	std::vector<sPerson> resultVector;

	// -------------TESTING SORT BEGIN-------------
	sPerson personToFind;
	theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );

	std::cout << "DESC_BY_ID" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;
	
	std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_BY_HEALTH" << std::endl;
	theSTDMap->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	//std::vector<sPerson> vecPeople;
	//sPerson personToFind;
	//personToFind.first = "JOHN";
	//theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "JAMES";
	//theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();
	//
	//personToFind.first = "ROBERT";
	//theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "MICHAEL";
	//theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "WILLIAM";
	//theSTDMap->FindPeopleByName( resultVector, personToFind, theSTDMap->theMap.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//theSTDMap->FindPeopleByName( resultVector, vecPeople, 3 );
	////theSTDMap->FindPeopleByName( resultVector, vecPeople, theSTDMap->theMap.size() );
	//std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//printVector( resultVector );
	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	//theSTDMap->FindPeople( resultVector, 40, 60, theSTDMap->theMap.size() );
	//std::cout << "Number of People in that heath: " << resultVector.size() << std::endl;
	////printVector( resultVector );
	//resultVector.clear();

	//sPoint center;
	//center.x = 50; center.y = 50; center.z = 50;

	//theSTDMap->FindPeople( resultVector, center, 20, theSTDMap->theMap.size() );
	//std::cout << "Number of People in that range: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();

	//theSTDMap->FindPeople( resultVector, center, 20, 40, 60, theSTDMap->theMap.size() );
	//std::cout << "Number of People in that range with that health: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();
	// -------------TESTING FIND BY POSITION/HEALTH END-------------

	// -------------TESTING FIND BY ID BEGIN-------------
	//sPerson p1;
	//theSTDMap->FindPersonByID( p1, 1 );
	//std::cout
	//	<< p1.uniqueID << "\t"
	//	<< p1.age << "\t"
	//	<< p1.health << "\t"
	//	<< p1.location.x << ", "
	//	<< p1.location.y << ", "
	//	<< p1.location.z << "\t"
	//	<< p1.first << " "
	//	<< p1.last
	//	<< std::endl;

	//theSTDMap->FindPersonByID( p1, 100 );
	//std::cout
	//	<< p1.uniqueID << "\t"
	//	<< p1.age << "\t"
	//	<< p1.health << "\t"
	//	<< p1.location.x << ", "
	//	<< p1.location.y << ", "
	//	<< p1.location.z << "\t"
	//	<< p1.first << " "
	//	<< p1.last
	//	<< std::endl;

	//theSTDMap->FindPersonByID( p1, 1000 );
	//std::cout
	//	<< p1.uniqueID << "\t"
	//	<< p1.age << "\t"
	//	<< p1.health << "\t"
	//	<< p1.location.x << ", "
	//	<< p1.location.y << ", "
	//	<< p1.location.z << "\t"
	//	<< p1.first << " "
	//	<< p1.last
	//	<< std::endl;
	// -------------TESTING FIND BY ID END-------------

	return 0;
}