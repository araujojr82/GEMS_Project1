#include <string>
//#include <vector>
#include <list>
#include "cPerson.h"

std::string getRandomString( std::list< std::string > stringList )
{
	int size = stringList.size();
	std::string theRandomString;

	int randomPosition = rand() % size;

	//theRandomString = theListOfStrings[randomPosition];

	
	// std::list<std::string>::iterator itString = std::next( stringList.begin(), randomPosition ); // <- C++ 11 way

	std::list<std::string>::iterator itString = stringList.begin();
	std::advance( itString, randomPosition );

	theRandomString = ( *itString );

	return theRandomString;
}

std::string getRandomFirstName( std::list< std::string > maleNames, std::list< std::string > femaleNames )
{
	std::string firstName;

	int gender = rand() % 2; // 0 = female, 1 = male
	if( gender == 1 )
		firstName = getRandomString( maleNames );
	else
		firstName = getRandomString( femaleNames );

	return firstName;
}

std::string getRandomLastName( std::list< std::string > lastNames )
{
	std::string lastName = getRandomString( lastNames );
	return lastName;
}

int getRandomAge()
{
	int age = rand() % 100 + 1;
	return age;
}

float getRandomHealth()
{
	float health = rand() % 1000 + 1;
	health = health / 10;
	return health;
}

sPoint getRandomLocation()
{
	sPoint location;
	location.x = rand() % 100;
	location.y = rand() % 100;
	location.z = rand() % 100;
	return location;
}