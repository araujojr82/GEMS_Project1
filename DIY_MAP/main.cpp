#include "cPerson.h"
#include <iostream>
#include "cDIY_Map.h"

cDIY_Map* theDIYMap;

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
	unsigned int numberOfPeople = 1000;

	theDIYMap = new cDIY_Map();

	theDIYMap->LoadDataFilesIntoContainer( "../dist.female.first.txt",
											"../dist.male.first.txt",
											"../US_LastNames.txt" );
	theDIYMap->GenerateRandomPeople( numberOfPeople );

	//printVector( theDIYMap->theMap );
	//std::cout << std::endl;

	std::vector<sPerson> resultVector;

	// -------------TESTING SORT BEGIN-------------
	/*std::cout << "DESC_BY_ID" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;
	
	std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_BY_HEALTH" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_ID" << std::endl;
	theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;*/
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	std::vector<sPerson> vecPeople;

	sPerson personToFind;
	personToFind.first = "JOHN";
	theDIYMap->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();

	personToFind.first = "JAMES";
	theDIYMap->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();
	
	personToFind.first = "ROBERT";
	theDIYMap->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();

	personToFind.first = "MICHAEL";
	theDIYMap->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();

	personToFind.first = "WILLIAM";
	theDIYMap->FindPeopleByName( resultVector, personToFind, numberOfPeople );
	std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	if( resultVector.size() > 0 ) printVector( resultVector );
	resultVector.clear();

	theDIYMap->FindPeopleByName( resultVector, vecPeople, 3 );
	//theDIYMap->FindPeopleByName( resultVector, vecPeople, numberOfPeople );
	std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	vecPeople.push_back( personToFind );
	printVector( resultVector );
	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	//theDIYMap->FindPeople( resultVector, 40, 60, numberOfPeople );
	//std::cout << "Number of People in that heath: " << resultVector.size() << std::endl;
	////printVector( resultVector );
	//resultVector.clear();

	//sPoint center;
	//center.x = 50; center.y = 50; center.z = 50;

	//theDIYMap->FindPeople( resultVector, center, 20, numberOfPeople );
	//std::cout << "Number of People in that range: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();

	//theDIYMap->FindPeople( resultVector, center, 20, 40, 60, numberOfPeople );
	//std::cout << "Number of People in that range with that health: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();
	// -------------TESTING FIND BY POSITION/HEALTH END-------------
	return 0;
}