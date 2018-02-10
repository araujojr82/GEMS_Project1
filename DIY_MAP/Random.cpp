#include <string>
#include <chrono>
#include <random>
#include "../DIY_LIST/cList.h"
#include "cMap.h"
#include "cPerson.h"

int getRandomNumber( int min, int max )
{
	int output;

	unsigned seed = ( unsigned int )std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator( seed );
	std::uniform_real_distribution<float> distribution( ( float )min, ( float )max );

	output = 0;

	output = ( int )distribution( generator );
	return output;
}

std::string getRandomString( cMap< std::string > theMapOfStrings )
{
	int size = theMapOfStrings.size();	
	std::string theRandomString;
	cList< std::string >* tempList;

	bool found = false;

	while( !found )
	{
		int randomPosition = getRandomNumber( 0, size -1 );
		tempList = &theMapOfStrings.get( std::to_string( randomPosition ) );
		if( tempList->size() != 0 )	// Check if there's data at the cList
		{
			randomPosition = getRandomNumber( 0, tempList->size() -1 );
			theRandomString = tempList->get( randomPosition );
			found = true;
		}
	}
	return theRandomString;
}

std::string getRandomFirstName( cMap< std::string > maleNames, cMap< std::string > femaleNames )
{
	std::string firstName;

	int gender = getRandomNumber( 0, 1 );		// 0 = female, 1 = male
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
	int age = getRandomNumber( 1, 100 );
	return age;
}

float getRandomHealth()
{
	float health = ( float )getRandomNumber( 1, 1000 );
	health = health / 10;
	return health;
}

sPoint getRandomLocation()
{
	sPoint location;
	location.x = ( float )getRandomNumber( 1, 100 );
	location.y = ( float )getRandomNumber( 1, 100 );
	location.z = ( float )getRandomNumber( 1, 100 );
	return location;
}