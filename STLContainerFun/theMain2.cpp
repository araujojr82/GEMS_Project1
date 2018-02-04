#include <string>
#include <vector>
#include <iostream>
#include "cPerson.h"
#include <algorithm>			// STL algo lib

#include <list>			// Double-linked list

#include <map>			// In STL it's usually (always?) a 'red-black' tree


bool loadDataIntoVector(std::string femaleNamesFileName, std::vector<std::string> &vecFirstFemale,
						std::string maleNamesFileName, std::vector<std::string> &vecFirstMale,
						std::string lastNamesFileName, std::vector<std::string> &vecLast,
						std::string &error); 

// Uses c interface, rather than C++ one (so WAY faster)
bool loadDataIntoVector2(std::string femaleNamesFileName, std::vector<std::string> &vecFirstFemale,
						 std::string maleNamesFileName, std::vector<std::string> &vecFirstMale,
						 std::string lastNamesFileName, std::vector<std::string> &vecLast,
						 std::string &error);


// Compare two people for which is "greater than"
// Predicate "function"
bool IsPersonABigger( sPerson& A, sPerson &B )
{

	if ( A.first < B.first )
	{
		return true;
	}
	return false;
}


class cIsPersonABigger
{
public:
	bool operator() ( const sPerson& A, const sPerson &B )
	{
		count++;
		if ( A.first < B.first )
		{
			return true;
		}
		return false;
	}
private:
	int count;
};

//int main_STL_EXAMPLE(int argc, char* argv[])
int main( int argc, char* argv[] )
{
	std::vector< std::string > vecFemaleNames;
	std::vector< std::string > vecMaleNames;
	std::vector< std::string > vecLastNames;
	std::string error;

	if ( ! loadDataIntoVector( "dist.female.first.txt", vecFemaleNames, 
	                           "dist.male.first.txt", vecMaleNames, 
	                           "US_LastNames.txt", vecLastNames, error ) )
	{
		std::cout << "Error: " << error << std::endl;
		return -1;
	}

//	std::cout << vecFemaleNames[4];


	// fun with vectors and the stl
	sPerson p1;		p1.first = vecFemaleNames[4];
					p1.last = vecLastNames[543];
					p1.uniqueID = rand();

	sPerson p2;		p2.first = vecFemaleNames[85];
					p2.last = vecLastNames[12];
					p2.uniqueID = rand();

	sPerson p3;		p3.first = vecFemaleNames[758];
					p3.last = vecLastNames[123];
					p3.uniqueID = rand();

	sPerson p4;		p4.first = vecFemaleNames[1457];
					p4.last = vecLastNames[321];
					p4.uniqueID = rand();


	std::vector<sPerson> vecPeople;
	vecPeople.push_back(p4);
	vecPeople.push_back(p2);
	vecPeople.push_back(p3);
	vecPeople.push_back(p1);
//	vecPeople.insert( vecPeople.end(), p2 );

	//for ( int index = 0;  index != vecPeople.size(); index++ )
	//for ( int index = vecPeople.size() - 1;  
	//	  index >= 0; 
	//	  index-- )
	//{
	//	std::cout << vecPeople[index].first << std::endl;
	//}

	//std::cout << std::endl;

	//for ( std::vector<sPerson>::reverse_iterator itPerson = vecPeople.rbegin();
	//	  itPerson != vecPeople.rend();
	//	  itPerson++ )
	//for ( std::vector<sPerson>::iterator itPerson = vecPeople.begin();
	//	  itPerson != vecPeople.end();
	//	  itPerson++ )
	//{
	//	std::cout << itPerson->first << std::endl;
	//}
	//std::cout << std::endl;

	std::sort( vecPeople.begin(), vecPeople.end(), IsPersonABigger );

//	cIsPersonABigger mySorter();
//	std::sort( vecPeople.begin(), vecPeople.end(), mySorter );


	//
	std::list<sPerson> listPeople;

	listPeople.insert( listPeople.begin(), p1 );
	listPeople.insert( listPeople.begin(), p2 );
	listPeople.insert( listPeople.begin(), p3 );
	listPeople.insert( listPeople.begin(), p4 );

	sPerson Voldemort;
	Voldemort.first = "Voldemort";

	std::list<sPerson>::iterator itVol = listPeople.begin();

	for ( int count = 0; count < 3; count ++ )
	{
		itVol++;
	}

	listPeople.insert( itVol, Voldemort );

	for ( std::list<sPerson>::iterator itPerson = listPeople.begin();
		  itPerson != listPeople.end();
		  itPerson++ )
	{
		std::cout << itPerson->first << std::endl;
	}
	std::cout << std::endl;

	//std::sort( listPeople.begin(), listPeople.end(), 
	//		   IsPersonABigger );
	listPeople.sort( IsPersonABigger );

	for ( std::list<sPerson>::iterator itPerson = listPeople.begin();
		  itPerson != listPeople.end();
		  itPerson++ )
	{
		std::cout << itPerson->first << std::endl;
	}

//	sPerson Bob;

//	std::vector<sPerson>	myVector;
//	sPerson myArray[10];

//	myVector[3] = Bob;		// 0, 1, 2
//	myArray[3] = Bob;		// fine

//	std::map<int, sPerson> myMapThatsLikeAVector; 
//	myMapThatsLikeAVector[3] = Michael;		// fine
//	myMapThatsLikeAVector[1] = Bob;		// fine

	std::map<unsigned long long, sPerson> mapPeopleMASTER;
	std::map<unsigned long long, sPerson> mapPeopleANOTHER_MAP;
	mapPeopleMASTER[p1.uniqueID] = p1;
	mapPeopleMASTER[p2.uniqueID] = p2;
	mapPeopleMASTER[p3.uniqueID] = p3;
	mapPeopleMASTER[p4.uniqueID] = p4;

	std::map<std::string /*lastname*/, unsigned long long> lookUpByLastName;

//	for ( auto itPerson = mapPeopleMASTER.begin();
	for ( std::map<unsigned long long, sPerson>::iterator itPerson = mapPeopleMASTER.begin();
		  itPerson != mapPeopleANOTHER_MAP.end();
		  itPerson++ )
	{

		lookUpByLastName[ itPerson->second.last ] = itPerson->second.uniqueID;
	}

	// 2 lookups in one line
	sPerson &x = mapPeopleMASTER[ lookUpByLastName["KRAMER"] ];


	std::map<std::string /*lastname*/, unsigned long long>::iterator itA 
		= lookUpByLastName.find( "KRAMER" );
	// Did it find it? 
	if (itA == lookUpByLastName.end() )
	{	
		// Violent exit in the middle of nowhere...!!
		exit(-1);
	}
	//unsigned long long TheID = lookUpByLastName["KRAMER"];

	std::map<unsigned long long, sPerson>::iterator itB 
		= mapPeopleMASTER.find( itA->second );

	if ( itB == mapPeopleMASTER.end() )
	{	
		// Violent exit in the middle of nowhere...!!
		exit(-1);
	}
	sPerson &ThePerson = itB->second;

	//for ( std::map<unsigned long long, sPerson>::iterator itPerson = mapPeopleMASTER.begin();
	//	  itPerson != mapPeopleMASTER.end();
	//	  itPerson++ )
	//{
	//	lookUpByLastName[ itPerson->second.last ] = itPerson->second;
	//}



	return 0;
}




/*
std::vector<int> vecNewbie;
vecNewbie.push_back(3);
vecNewbie.push_back(17);
vecNewbie.push_back(1);
vecNewbie.push_back(98);

for (std::vector<int>::iterator it = vecNewbie.begin();
it != vecNewbie.end();
it++)
{
std::cout << *it << std::endl;
}
std::cout << std::endl;

std::vector<int>::iterator itA = vecNewbie.begin();
std::vector<int>::iterator itB = vecNewbie.end();

std::sort(itA, itB);

for (std::vector<int>::iterator it = vecNewbie.begin();
it != vecNewbie.end();
it++)
{
std::cout << *it << std::endl;
}

*/