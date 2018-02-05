#include <string>

#include "cList.h"
#include "cPerson.h"

std::string getRandomString( cList< std::string > theListOfStrings )
{

	int size = theListOfStrings.size();
	std::string theRandomString;

	int randomPosition = rand() % size;

	theRandomString = theListOfStrings.get( randomPosition );

	return theRandomString;
}

std::string getRandomFirstName( cList< std::string > maleNames, cList< std::string > femaleNames )
{
	std::string firstName;

	int gender = rand() % 2; // 0 = female, 1 = male
	if( gender == 1 )
		firstName = getRandomString( maleNames );
	else
		firstName = getRandomString( femaleNames );

	return firstName;
}

std::string getRandomLastName( cList< std::string > lastNames )
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