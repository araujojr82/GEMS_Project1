#include "cPerson.h"
#include <iostream>
#include "cSTD_Vector.h"

cSTD_Vector* theSTDVector;

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
	int numberOfPeople = 10000;
	sPerfData lastCallData;

	theSTDVector = new cSTD_Vector();

	theSTDVector->LoadDataFilesIntoContainer( "../dist.female.first.txt",
											  "../dist.male.first.txt",
											  "../US_LastNames.txt" );

	std::cout << "Generating " << numberOfPeople << " people..." << std::endl;
	theSTDVector->GenerateRandomPeople( numberOfPeople );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::vector<sPerson> resultVector;
	
	// -------------TESTING SORT BEGIN-------------
	sPerson personToFind;
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	std::cout << "Loading Everyone " << std::endl;
	printPerfData( lastCallData );
	std::cout << std::endl;

	theSTDVector->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theSTDVector->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;
	
	theSTDVector->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theSTDVector->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	theSTDVector->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theSTDVector->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theSTDVector->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	std::cout << "DESC_BY_ID" << std::endl;
	theSTDVector->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	//printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	std::vector<sPerson> vecPeople;

	resultVector.clear();

	//sPerson personToFind;
	personToFind.first = "JOHN";
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "JAMES";
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;
	
	personToFind.first = "ROBERT";
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "MICHAEL";
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	personToFind.first = "WILLIAM";
	theSTDVector->FindPeopleByName( resultVector, personToFind, theSTDVector->theVector.size() );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	//theSTDVector->FindPeopleByName( resultVector, vecPeople, 3 );
	theSTDVector->FindPeopleByName( resultVector, vecPeople, theSTDVector->theVector.size() );
	std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	printVector( resultVector );
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	theSTDVector->FindPeople( resultVector, 40, 60, theSTDVector->theVector.size() );
	std::cout << "Number of People in that heath: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	sPoint center;
	center.x = 50; center.y = 50; center.z = 50;

	theSTDVector->FindPeople( resultVector, center, 20, theSTDVector->theVector.size() );
	std::cout << "Number of People in that range: " << resultVector.size() << std::endl;
	printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );
	std::cout << std::endl;

	theSTDVector->FindPeople( resultVector, center, 20, 40, 60, theSTDVector->theVector.size() );
	std::cout << "Number of People in that range with that health: " << resultVector.size() << std::endl;
	printVector( resultVector );
	resultVector.clear();
	theSTDVector->GetPerformanceFromLastCall( lastCallData );
	printPerfData( lastCallData );

	// -------------TESTING FIND BY POSITION/HEALTH END-------------
	return 0;
}