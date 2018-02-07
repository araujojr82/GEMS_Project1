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
	std::cout << "    Number of Elements: " << theVector.size() << std::endl;
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
	std::cout << "    Number of Elements: " << theVector.size() << std::endl;
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

	//cMap<std::string> tempMap = theDIYMap->mapLastNames;
	//cList<std::string> tempList;

	////std::cout << "ID\tage\thealth\tlocation\tfirst and last name" << std::endl;

	//int total = 0;

	//for( int i = 0; i != tempMap.size(); i++ )
	//{
	//	tempList = tempMap.get( i );					// In each step get the cList for this posiiton

	//	tempList.moveToFirst();						// Move to first element
	//	
	//	if( tempList.size() != 0 )		
	//	std::cout << "Map Position: " << i << " contains " 
	//		<< tempList.size() << " elements." << std::endl;		

	//	total += tempList.size();

	//	//for( int i = 0; i != tempList.size(); i++ )	// Loops through the list
	//	//{
	//	//	sPerson* tempPerson = tempList.pCurrent->value;

	//	//	std::cout
	//	//		<< tempPerson->uniqueID << "\t"
	//	//		<< tempPerson->age << "\t"
	//	//		<< tempPerson->health << "\t"
	//	//		<< tempPerson->location.x << ", "
	//	//		<< tempPerson->location.y << ", "
	//	//		<< tempPerson->location.z << "\t"
	//	//		<< tempPerson->first << " "
	//	//		<< tempPerson->last
	//	//		<< std::endl;

	//	//	tempList.moveToNext();
	//	//}
	//}
	//std::cout << "Total: " << total << std::endl;


	////cMap<sPerson*> tempMap = theDIYMap->theMapByID;
	////cList<sPerson*> tempList;

	//////std::cout << "ID\tage\thealth\tlocation\tfirst and last name" << std::endl;

	////int total = 0;

	////for( int i = 0; i != tempMap.size(); i++ )
	////{
	////	tempList = tempMap.get( i );					// In each step get the cList for this posiiton

	////	tempList.moveToFirst();						// Move to first element

	////	if( tempList.size() != 0 )
	////		std::cout << "Map Position: " << i << " contains "
	////		<< tempList.size() << " elements." << std::endl;

	////	total += tempList.size();
	////}
	////std::cout << "Total: " << total << std::endl;


	//cMap<sPerson*> tempMap = theDIYMap->theMapByFirst;
	//cList<sPerson*> tempList;

	//std::cout << "ID\tage\thealth\tlocation\tfirst and last name" << std::endl;

	//int total = 0;

	//for( int i = 0; i != tempMap.size(); i++ )
	//{
	//	tempList = tempMap.get( i );					// In each step get the cList for this posiiton

	//	tempList.moveToFirst();						// Move to first element

	//	//if( tempList.size() != 0 )
	//	//	std::cout << "Map Position: " << i << " contains "
	//	//	<< tempList.size() << " elements." << std::endl;

	//	total += tempList.size();

	//	for( int i = 0; i != tempList.size(); i++ )	// Loops through the list
	//	{
	//		sPerson* tempPerson = tempList.pCurrent->value;

	//		std::cout
	//			<< tempPerson->uniqueID << "\t"
	//			<< tempPerson->age << "\t"
	//			<< tempPerson->health << "\t"
	//			<< tempPerson->location.x << ", "
	//			<< tempPerson->location.y << ", "
	//			<< tempPerson->location.z << "\t"
	//			<< tempPerson->first << " "
	//			<< tempPerson->last
	//			<< std::endl;

	//		tempList.moveToNext();
	//	}
	//}
	//std::cout << "Total: " << total << std::endl;


	// -------------TESTING SORT BEGIN-------------
	///*std::cout << "DESC_BY_ID" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_BY_ID );
	//printVector( resultVector );
	//std::cout << "DESC_BY_ID" << std::endl;
	//std::cout << std::endl;

	//std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_FIRST_THEN_LAST );
	//printVector( resultVector );
	//std::cout << "ASC_FIRST_THEN_LAST" << std::endl;
	//std::cout << std::endl;
	//
	//std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_FIRST_THEN_LAST );
	//printVector( resultVector );
	//std::cout << "DESC_FIRST_THEN_LAST" << std::endl;
	//std::cout << std::endl;

	//std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_LAST_THEN_FIRST );
	//printVector( resultVector );
	//std::cout << "ASC_LAST_THEN_FIRST" << std::endl;
	//std::cout << std::endl;

	//std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_LAST_THEN_FIRST );
	//printVector( resultVector );
	//std::cout << "DESC_LAST_THEN_FIRST" << std::endl;
	//std::cout << std::endl;

	//std::cout << "ASC_BY_HEALTH" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_BY_HEALTH );
	//printVector( resultVector );
	//std::cout << "ASC_BY_HEALTH" << std::endl;
	//std::cout << std::endl;

	//std::cout << "DESC_BY_HEALTH" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::DESC_BY_HEALTH );
	//printVector( resultVector );
	//std::cout << "DESC_BY_HEALTH" << std::endl;
	//std::cout << std::endl;

	//std::cout << "ASC_BY_ID" << std::endl;
	//theDIYMap->SortPeople( resultVector, iPersonMotron::ASC_BY_ID );
	//printVector( resultVector );
	//std::cout << "ASC_BY_ID" << std::endl;
	//std::cout << std::endl;*/
	// -------------TESTING SORT END-------------

	// -------------TESTING FIND BY NAME BEGIN-------------
	std::vector<sPerson> vecPeople;

	resultVector.clear();

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
	theDIYMap->FindPeopleByName( resultVector, vecPeople, numberOfPeople );
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