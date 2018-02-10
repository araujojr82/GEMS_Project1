#include "cPerson.h"
#include <iostream>
#include "cSTD_Map.h"

cSTD_Map* theConteiner = new cSTD_Map();
int numberOfPeople = 1000;

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

void printPerfData( sPerfData &theData )
{
	std::cout << "Time Spent: " << theData.elapsedCallTime_ms << " ms " << std::endl;
	std::cout << "Minimum RAM: " << ( int )theData.memoryUsageBytes_min << std::endl;
	std::cout << "Average RAM: " << ( int )theData.memoryUsageBytes_max << std::endl;
	std::cout << "Maximum RAM: " << ( int )theData.memoryUsageBytes_avg << std::endl;
	return;
}

int main( int argc, char* argv[] )
{
	sPerfData lastCallData;

	theConteiner->LoadDataFilesIntoContainer( "../dist.female.first.txt",
		"../dist.male.first.txt",
		"../US_LastNames.txt" );

	std::cout << "Generating " << numberOfPeople << " people..." << std::endl;
	theConteiner->GenerateRandomPeople( numberOfPeople );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::vector<sPerson> resultVector;

	// -------------TESTING SORT BEGIN-------------
	sPerson personToFind;
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	std::cout << "Loading Everyone " << std::endl;
	printPerfData( lastCallData );
	std::cout << std::endl;

	theConteiner->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	theConteiner->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "DESC_BY_HEALTH" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_BY_ID" << std::endl;
	theConteiner->SortPeople( resultVector, iPersonMotron::ASC_BY_ID );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	std::vector<sPerson> vecPeople;

	resultVector.clear();

	//sPerson personToFind;
	personToFind.first = "JOHN";
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "JAMES";
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "ROBERT";
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "MICHAEL";
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "WILLIAM";
	theConteiner->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	//theConteiner->FindPeopleByName( resultVector, vecPeople, 3 );
	theConteiner->FindPeopleByName( resultVector, vecPeople, numberOfPeople );
	std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	printVector( resultVector );
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	theConteiner->FindPeople( resultVector, 40, 60, numberOfPeople );
	std::cout << "Number of People with health between 40 and 60: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	sPoint center;
	center.x = 50; center.y = 50; center.z = 50;

	theConteiner->FindPeople( resultVector, center, 20, numberOfPeople );
	std::cout << "Number of People within 20 units range of the center: " << resultVector.size() << std::endl;
	printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	theConteiner->FindPeople( resultVector, center, 20, 40, 60, numberOfPeople );
	std::cout << "Number of People in that range with that health range: " << resultVector.size() << std::endl;
	printVector( resultVector );
	resultVector.clear();
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	// -------------TESTING FIND BY POSITION/HEALTH END-------------

	// -------------TESTING FIND BY ID BEGIN-------------
	sPerson aPerson;
	int ID = 1;					// First person
	if( theConteiner->FindPersonByID( aPerson, ID ) )
		std::cout << "Person with ID: " << ID << " found!" << std::endl;
	else
		std::cout << "Person with ID: " << ID << " not found!" << std::endl;
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	ID = numberOfPeople;	// Last person
	if( theConteiner->FindPersonByID( aPerson, ID ) )
		std::cout << "Person with ID: " << ID << " found!" << std::endl;
	else
		std::cout << "Person with ID: " << ID << " not found!" << std::endl;
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	ID = numberOfPeople / 3;	// a "random" person
	if( theConteiner->FindPersonByID( aPerson, ID ) )
		std::cout << "Person with ID: " << ID << " found!" << std::endl;
	else
		std::cout << "Person with ID: " << ID << " not found!" << std::endl;
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	ID = numberOfPeople + 10;	// OFF RANGE
	if( theConteiner->FindPersonByID( aPerson, ID ) )
		std::cout << "Person with ID: " << ID << " found!" << std::endl;
	else
		std::cout << "Person with ID: " << ID << " not found!" << std::endl;
	theConteiner->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	// -------------TESTING FIND BY ID END-------------
	return 0;
}