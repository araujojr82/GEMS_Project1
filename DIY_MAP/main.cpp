#include "cPerson.h"
#include <iostream>
#include "cDIY_Map.h"

cDIY_Map* theDIYList;

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

	theDIYList = new cDIY_Map();

	theDIYList->LoadDataFilesIntoContainer( "../dist.female.first.txt",
											"../dist.male.first.txt",
											"../US_LastNames.txt" );
	theDIYList->GenerateRandomPeople( 1000 );

	//printVector( theDIYList->theList );
	//std::cout << std::endl;

	std::vector<sPerson> resultVector;

	// -------------TESTING SORT BEGIN-------------
	/*std::cout << "DESC_BY_ID" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;
	
	std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_BY_HEALTH" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_ID" << std::endl;
	theDIYList->SortPeople( resultVector, iPersonMotron::ASC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;*/
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	//std::vector<sPerson> vecPeople;

	//sPerson personToFind;
	//personToFind.first = "JOHN";
	//theDIYList->FindPeopleByName( resultVector, personToFind, theDIYList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "JAMES";
	//theDIYList->FindPeopleByName( resultVector, personToFind, theDIYList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();
	//
	//personToFind.first = "ROBERT";
	//theDIYList->FindPeopleByName( resultVector, personToFind, theDIYList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "MICHAEL";
	//theDIYList->FindPeopleByName( resultVector, personToFind, theDIYList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "WILLIAM";
	//theDIYList->FindPeopleByName( resultVector, personToFind, theDIYList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//theDIYList->FindPeopleByName( resultVector, vecPeople, 3 );
	////theDIYList->FindPeopleByName( resultVector, vecPeople, theDIYList->theList.size() );
	//std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//printVector( resultVector );
	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	//theDIYList->FindPeople( resultVector, 40, 60, theDIYList->theList.size() );
	//std::cout << "Number of People in that heath: " << resultVector.size() << std::endl;
	////printVector( resultVector );
	//resultVector.clear();

	//sPoint center;
	//center.x = 50; center.y = 50; center.z = 50;

	//theDIYList->FindPeople( resultVector, center, 20, theDIYList->theList.size() );
	//std::cout << "Number of People in that range: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();

	//theDIYList->FindPeople( resultVector, center, 20, 40, 60, theDIYList->theList.size() );
	//std::cout << "Number of People in that range with that health: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();
	// -------------TESTING FIND BY POSITION/HEALTH END-------------
	return 0;
}