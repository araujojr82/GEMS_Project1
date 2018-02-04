#include "cPerson.h"
#include <iostream>
#include "cSTD_List.h"

cSTD_List* theSTDList;

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

	theSTDList = new cSTD_List();

	theSTDList->LoadDataFilesIntoContainer( "../dist.female.first.txt",
											  "../dist.male.first.txt",
											  "../US_LastNames.txt" );
	theSTDList->GenerateRandomPeople( 100 );

	//printVector( theSTDList->theList );
	//std::cout << std::endl;

	std::vector<sPerson> resultVector;

	// -------------TESTING SORT BEGIN-------------
	sPerson personToFind;
	theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );

	std::cout << "DESC_BY_ID" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;
	
	std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "ASC_BY_HEALTH" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;

	std::cout << "DESC_BY_HEALTH" << std::endl;
	theSTDList->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	printVector( resultVector );
	std::cout << std::endl;
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	//std::vector<sPerson> vecPeople;
	//sPerson personToFind;
	//personToFind.first = "JOHN";
	//theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "JAMES";
	//theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();
	//
	//personToFind.first = "ROBERT";
	//theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "MICHAEL";
	//theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//personToFind.first = "WILLIAM";
	//theSTDList->FindPeopleByName( resultVector, personToFind, theSTDList->theList.size() );
	//std::cout << "Number of " << personToFind.first << ": " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//if( resultVector.size() > 0 ) printVector( resultVector );
	//resultVector.clear();

	//theSTDList->FindPeopleByName( resultVector, vecPeople, 3 );
	////theSTDList->FindPeopleByName( resultVector, vecPeople, theSTDList->theList.size() );
	//std::cout << "Number of People with one of those names: " << resultVector.size() << std::endl;
	//vecPeople.push_back( personToFind );
	//printVector( resultVector );
	// -------------TESTING FIND BY NAME END-------------

	// -------------TESTING FIND BY POSITION/HEALTH BEGIN-------------
	//theSTDList->FindPeople( resultVector, 40, 60, theSTDList->theList.size() );
	//std::cout << "Number of People in that heath: " << resultVector.size() << std::endl;
	////printVector( resultVector );
	//resultVector.clear();

	//sPoint center;
	//center.x = 50; center.y = 50; center.z = 50;

	//theSTDList->FindPeople( resultVector, center, 20, theSTDList->theList.size() );
	//std::cout << "Number of People in that range: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();

	//theSTDList->FindPeople( resultVector, center, 20, 40, 60, theSTDList->theList.size() );
	//std::cout << "Number of People in that range with that health: " << resultVector.size() << std::endl;
	//printVector( resultVector );
	//resultVector.clear();
	// -------------TESTING FIND BY POSITION/HEALTH END-------------

	// -------------TESTING FIND BY ID BEGIN-------------
	//sPerson p1;
	//theSTDList->FindPersonByID( p1, 1 );
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

	//theSTDList->FindPersonByID( p1, 100 );
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

	//theSTDList->FindPersonByID( p1, 1000 );
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