#include "cSTD_Map.h"

extern std::string getRandomString( std::map< int, std::string > theVectorOfStrings );
extern std::string getRandomFirstName( std::map< int, std::string > maleNames, std::map< int, std::string > femaleNames );
extern std::string getRandomLastName( std::map< int, std::string > lastNames );
extern int getRandomAge();
extern float getRandomHealth();
extern sPoint getRandomLocation();

int cSTD_Map::uniqueID = 0;

cSTD_Map::cSTD_Map()
{
	this->type = STD_MAP;
	//this->uniqueID = 0;

	// Initialize the rand() with a time seed
	time_t curTime;
	time( &curTime );

	// Using time as seed for random generation
	srand( (int)curTime );
}

cSTD_Map::~cSTD_Map()
{

}

bool cSTD_Map::LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
											std::string firstNameMaleFileName,
											std::string lastNameFileName )
{
	mapFemaleNames.clear();
	mapMaleNames.clear();
	mapLastNames.clear();

	// Load Female names files if filename is given
	if( firstNameFemaleFileName != "" )
	{
		std::fstream femaleFile( firstNameFemaleFileName.c_str() );
		if( !femaleFile.is_open() )
		{
			//error = "Can't open female name file called " + femaleNamesFileName;
			return false;
		}

		std::string tempName;	float garbage;
		int id;
		while( femaleFile >> tempName )
		{
			//mapFemaleNames.push_back( tempName );
			mapFemaleNames[id] = tempName;
			femaleFile >> garbage >> garbage >> garbage;
			id++;
		}
	}

	// Load Male names files if filename is given
	if( firstNameMaleFileName != "" )
	{
		std::fstream maleFile( firstNameMaleFileName.c_str() );
		if( !maleFile.is_open() )
		{
			//error = "Can't open male name file called " + maleNamesFileName;
			return false;
		}

		std::string tempName;	float garbage;
		int id;
		while( maleFile >> tempName )
		{
			//mapMaleNames.push_back( tempName );
			mapMaleNames[id] = tempName;
			maleFile >> garbage >> garbage >> garbage;
			id++;
		}
	}

	// Load Last names files if filename is given
	if( lastNameFileName != "" )
	{
		std::fstream lastNameFile( lastNameFileName.c_str() );
		if( !lastNameFile.is_open() )
		{
			//error = "Can't open last names file called " + lastNamesFileName;
			return false;
		}

		std::string tempName;	float garbage;
		int id;
		while( lastNameFile >> tempName )
		{
			//mapLastNames.push_back( tempName );
			mapLastNames[id] = tempName;
			lastNameFile >> garbage >> garbage >> garbage;
			id++;
		}
	}
	return true;
}

int cSTD_Map::getPersonID()
{
	this->uniqueID++;

	return this->uniqueID;
}


// Based on the files that have been loaded, generate people.
// Should be a mix of male and female names.
// Unique IDs must be unique								 
bool cSTD_Map::GenerateRandomPeople( int numberOfPeople )
{

	for( int i = 0; i != numberOfPeople; i++ )
	{
		sPerson* newPerson = new sPerson();
		newPerson->uniqueID = this->getPersonID();
		newPerson->first = getRandomFirstName( mapFemaleNames, mapMaleNames );
		newPerson->last = getRandomLastName( mapLastNames );
		newPerson->age = getRandomAge();
		newPerson->health = getRandomHealth();
		newPerson->location = getRandomLocation();

		//this->theMap.push_back( newPerson );
		this->theMap[newPerson->uniqueID] =  newPerson;
	}

	return true;
}

// Returns only people with this name 
// If the name (first or last) is blank (""), then ignore this parameter.
// For example: 
// - if last name is "", search only by first name
// - if first name is "", search only by last name
// - if both names are blank, return everyone
bool cSTD_Map::FindPeopleByName( std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople )
{

	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		itPerson != this->theMap.end();
		itPerson++ )
	{	
		if( personToMatch.first == "" )									// First Name is blank
		{
			if( personToMatch.last == "" )								// Last Name is blank
			{	
				vecPeople.push_back( *( *itPerson ).second );			// --> Return all persons
			}
			else														// Last Name is NOT blank
			{	
				if( ( *itPerson ).second->last == personToMatch.last )	// Look for people with this last name
				{
					vecPeople.push_back( *( *itPerson ).second );
				}
			}
		}
		else															// First Name is NOT blank
		{
			if( personToMatch.last == "" )								// Last Name is blank
			{	
				if( ( *itPerson ).second->first == personToMatch.first )
				{
					vecPeople.push_back( *( *itPerson ).second );		// Return all persons with the first name
				}
			}
			else														// Last Name is NOT blank
			{	
				if( ( *itPerson ).second->first == personToMatch.first &&
					( *itPerson ).second->last == personToMatch.last )	// Look for people with this first AND last name
				{
					vecPeople.push_back( *( *itPerson ).second );
				}
			}
		}			
		if( vecPeople.size() == maxNumberOfPeople ) break;				// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

bool cSTD_Map::FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople )
{
	// IF ONLY I COULD USE VECTORS FOR THIS...
	//std::vector<sPerson> tempVec;
	//int currentMax;

	//currentMax = maxNumberOfPeople;

	//for( int i = 0; i != vecPeopleToMatch.size(); i++ )
	//{
	//	tempVec.clear();
	//	if( currentMax == 0 ) break;					// STOP ADDING PEOPLE WHEN REACHES MAX
	//	if( this->FindPeopleByName( tempVec, vecPeopleToMatch[i], currentMax ) )
	//	{
	//		// ADD the results of the individual search to the collective result
	//		for( int j = 0; j != tempVec.size(); j++ )
	//		{
	//			vecPeople.push_back( tempVec[j] );
	//		}
	//		currentMax -= tempVec.size();
	//	}
	//	//if( vecPeople.size() == maxNumberOfPeople ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	//}
	//
	//if( vecPeople.size() != 0 ) return true;

	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		itPerson != this->theMap.end();
		itPerson++ )
	{
		for( int i = 0; i != vecPeopleToMatch.size(); i++ )
		{

			if( vecPeopleToMatch[i].first == "" )									// First Name is blank
			{
				if( vecPeopleToMatch[i].last == "" )								// Last Name is blank
				{
					vecPeople.push_back( *( *itPerson ).second );					// --> Return all persons
				}
				else																// Last Name is NOT blank
				{
					if( ( *itPerson ).second->last == vecPeopleToMatch[i].last )	// Look for people with this last name
					{
						vecPeople.push_back( *( *itPerson ).second );
					}
				}
			}
			else																	// First Name is NOT blank
			{
				if( vecPeopleToMatch[i].last == "" )								// Last Name is blank
				{
					if( ( *itPerson ).second->first == vecPeopleToMatch[i].first )
					{
						vecPeople.push_back( *( *itPerson ).second );				// Return all persons with the first name
					}
				}
				else																// Last Name is NOT blank
				{
					if( ( *itPerson ).second->first == vecPeopleToMatch[i].first &&	// Look for people with this first...
						( *itPerson ).second->last == vecPeopleToMatch[i].last )	// AND last name
					{
						vecPeople.push_back( *( *itPerson ).second );
					}
				}
			}
			if( vecPeople.size() == maxNumberOfPeople ) break;						// STOP ADDING PEOPLE WHEN REACHES MAX
		}
		if( vecPeople.size() == maxNumberOfPeople ) break;							// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	
	if( vecPeople.size() != 0 ) return true;
	
	return false;
}

// Returns false if not found.
bool cSTD_Map::FindPersonByID( sPerson &person, unsigned long long uniqueID )
{
	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		 itPerson != this->theMap.end();
		 itPerson++ )
	{
		if( (*itPerson).second->uniqueID == uniqueID )
		{
			//sPerson *thePerson = ( *itPerson ); // Iterator to Pointer
			//person = ( *thePerson );			  // Pointer to Reference
			person = ( *(*itPerson).second );

			return true;
		}
	}

	return false;
}

// Calculate the distance between 2 points
float distanceAB( sPoint A, sPoint B )
{
	float xSqr = ( A.x - B.x ) * ( A.x - B.x );
	float ySqr = ( A.y - B.y ) * ( A.y - B.y );
	float zSqr = ( A.z - B.z ) * ( A.z - B.z );

	float mySqr = xSqr + ySqr + zSqr;

	float distance = sqrt( mySqr );

	return distance;
}

// Finds the closest people (could be zero), from a point and radius. 
// Assume that location is "less than or equal" to radius
bool cSTD_Map::FindPeople( std::vector<sPerson> &vecPeople, sPoint location, float radius,
	int maxPeopleToReturn )
{
	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		 itPerson != this->theMap.end();
		 itPerson++ )
	{
		if( distanceAB( (*itPerson).second->location, location ) <= radius )
		{
			vecPeople.push_back( *( *itPerson ).second );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

// Finds people with a certain health range (inclusive of the min and max values)
bool cSTD_Map::FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		itPerson != this->theMap.end();
		itPerson++ )
	{
		if( ( *itPerson ).second->health >= minHealth &&
			( *itPerson ).second->health <= maxHealth )
		{
			vecPeople.push_back( *( *itPerson ).second );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Combination of the two functions above
bool cSTD_Map::FindPeople( std::vector<sPerson> &vecPeople,
	sPoint location, float radius,
	float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	for( std::map<int, sPerson*>::iterator itPerson = this->theMap.begin();
		itPerson != this->theMap.end();
		itPerson++ )
	{
		if( ( ( *itPerson ).second->health >= minHealth &&
			  ( *itPerson ).second->health <= maxHealth ) &&
			  distanceAB( ( *itPerson ).second->location, location ) <= radius )
		{
			vecPeople.push_back( *( *itPerson ).second );
		}		
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}
#include <functional>

// Sorts the people, then returns the container of sorted people
// - this is from the data loaded by LoadDataFilesIntoContainer()
bool cSTD_Map::SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType )
{
	vecPeople.clear();

	if( this->theMap.size() != 0 )
	{
		this->mySorter.sortBy = sortType;

		std::map<int, sPerson*> mapCopy;
		mapCopy = theMap;

		while( mapCopy.size() > 0 )
		{			
			vecPeople.push_back( *this->mySorter.findMapEntry( mapCopy ) );
		}

		return true;
	}
	return false;
}

// Can be called after every function. 
// Calls from any of the above functions overwrites this data. 
// Measuring starts from when call is made to just before it returns.
bool cSTD_Map::GetPerformanceFromLastCall( sPerfData &callStats )
{
	return false;
}


// Returns the enum from the cPerson.h file
eContainerType cSTD_Map::getContainerType( void )
{
	return this->type;
}