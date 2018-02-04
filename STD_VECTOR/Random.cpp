#include <string>
#include <vector>
#include "cPerson.h"

std::string getRandomString( std::vector< std::string > theVectorOfStrings )
{

	int size = theVectorOfStrings.size();
	std::string theRandomString;

	int randomPosition = rand() % size;

	theRandomString = theVectorOfStrings[randomPosition];

	return theRandomString;
}

std::string getRandomFirstName( std::vector< std::string > maleNames, std::vector< std::string > femaleNames )
{
	std::string firstName;

	int gender = rand() % 2; // 0 = female, 1 = male
	if( gender == 1 )
		firstName = getRandomString( maleNames );
	else
		firstName = getRandomString( femaleNames );

	return firstName;
}

std::string getRandomLastName( std::vector< std::string > lastNames )
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