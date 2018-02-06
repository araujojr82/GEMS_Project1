#include <string>

#include "../DIY_LIST/cList.h"
#include "cMap.h"
#include "cPerson.h"

std::string getRandomString( cMap< std::string > theMapOfStrings )
{

	int size = theMapOfStrings.size();
	std::string theRandomString;
	cList< std::string > tempList;

	bool found = false;

	while( !found )
	{
		int randomPosition = rand() % size;
		tempList = theMapOfStrings.get( std::to_string( randomPosition ) );
		if( tempList.size() != 0 )	// Check if there's data at the cList
		{
			randomPosition = rand() % tempList.size();
			theRandomString = tempList.get( randomPosition );
			found = true;
		}
	}
	return theRandomString;
}

std::string getRandomFirstName( cMap< std::string > maleNames, cMap< std::string > femaleNames )
{
	std::string firstName;

	int gender = rand() % 2; // 0 = female, 1 = male
	if( gender == 1 )
		firstName = getRandomString( maleNames );
	else
		firstName = getRandomString( femaleNames );

	return firstName;
}

std::string getRandomLastName( cMap< std::string > lastNames )
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