#include "cDIY_Map.h"

extern std::string getRandomString( cMap< std::string > theMapOfStrings );
extern std::string getRandomFirstName( cMap< std::string > maleNames, cMap< std::string > femaleNames );
extern std::string getRandomLastName( cMap< std::string > lastNames );
extern int getRandomAge();
extern float getRandomHealth();
extern sPoint getRandomLocation();

int cDIY_Map::uniqueID = 0;

cDIY_Map::cDIY_Map()
{
	this->type = CUSTOM_DIY_MAP;

	// Initialize the rand() with a time seed
	time_t curTime;
	time( &curTime );

	// Using time as seed for random generation
	srand( ( int )curTime );
}

cDIY_Map::~cDIY_Map()
{
	delete this;
}

bool cDIY_Map::LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
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
		while( femaleFile >> tempName )
		{
			mapFemaleNames.insert( tempName, tempName );
			femaleFile >> garbage >> garbage >> garbage;
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
		while( maleFile >> tempName )
		{
			mapMaleNames.insert( tempName, tempName );
			maleFile >> garbage >> garbage >> garbage;
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
		while( lastNameFile >> tempName )
		{
			mapLastNames.insert( tempName, tempName );
			lastNameFile >> garbage >> garbage >> garbage;
		}
	}
	return true;
}

int cDIY_Map::getPersonID()
{
	this->uniqueID++;

	return this->uniqueID;
}


// Based on the files that have been loaded, generate people.
// Should be a mix of male and female names.
// Unique IDs must be unique								 
bool cDIY_Map::GenerateRandomPeople( int numberOfPeople )
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

		this->theMapByFirst.insert( newPerson, newPerson->first );
		this->theMapByLast.insert( newPerson, newPerson->last );
		this->theMapByID.insert( newPerson, std::to_string( newPerson->uniqueID ) );
		this->theMapByHealth.insert( newPerson, std::to_string( newPerson->health ) );
	}

	return true;
}

// Returns only people with this name 
// If the name (first or last) is blank (""), then ignore this parameter.
// For example: 
// - if last name is "", search only by first name
// - if first name is "", search only by last name
// - if both names are blank, return everyone
bool cDIY_Map::FindPeopleByName( std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople )
{	
	cMap<sPerson*>* tempMap;
	cList<sPerson*>* tempList;

	if( personToMatch.last == "" )		
	{
		tempMap = &this->theMapByFirst;							// If Last name is empty, use the First names map

		if( personToMatch.first == "" )							// If First Name is also blank, return everyone
		{
			for( int i = 0; i != tempMap->size(); i++ )
			{	
				tempList = &tempMap->get( i );					// In each step get the cList for this posiiton

				tempList->moveToFirst();						// Move to first element

				for( int i = 0; i != tempList->size(); i++ )	// Loops through the list
				{
					vecPeople.push_back( *tempList->pCurrent->value );					
					tempList->moveToNext();
				}				
			}
		}
		else								
		{									
			tempList = &tempMap->get( personToMatch.first );	// Get the cList of people with this Last name's hash 
											
			tempList->moveToFirst();							// Move to first element

			for( int i = 0; i != tempList->size(); i++ )		// Loops to find people with that last name
			{
				if( tempList->pCurrent->value->first == personToMatch.first )
				{
					vecPeople.push_back( *tempList->pCurrent->value );
				}				
				tempList->moveToNext();
			}			
		}
	}
	else
	{
		tempMap = &this->theMapByLast;							// If Last name exists, use the Last names map
		
		tempList = &tempMap->get( personToMatch.last );			// Get the cList of people with this First name's hash 

		tempList->moveToFirst();								// Move to first element

		for( int i = 0; i != tempList->size(); i++ )			// Loops to find people with that first name
		{
			if( tempList->pCurrent->value->first == personToMatch.first )
			{
				if( personToMatch.first == "" )
					vecPeople.push_back( *tempList->pCurrent->value );	// No need to check for first name
				else
				{
					if( tempList->pCurrent->value->first == personToMatch.first )	// Check first also
					{
						vecPeople.push_back( *tempList->pCurrent->value );
					}
				}
			}
			tempList->moveToNext();
		}
	}

	if( vecPeople.size() != 0 ) return true;

	return false;
}

bool cDIY_Map::FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople )
{
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
	//}

	//if( vecPeople.size() != 0 ) return true;

	return false;
}

// Returns false if not found.
bool cDIY_Map::FindPersonByID( sPerson &person, unsigned long long uniqueID )
{

	//for( int i = 0; i != this->theMap.size(); i++ )
	//{
	//	sPerson* tempPerson = this->theMap.pCurrent->value;
	//	if( tempPerson->uniqueID == uniqueID )
	//	{
	//		person = *tempPerson;
	//		return true;
	//	}
	//}

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
bool cDIY_Map::FindPeople( std::vector<sPerson> &vecPeople, sPoint location, float radius,
	int maxPeopleToReturn )
{

	//for( int i = 0; i != this->theMap.size(); i++ )
	//{
	//	sPerson* tempPerson = this->theMap.pCurrent->value;
	//	if( distanceAB( tempPerson->location, location ) <= radius )
	//	{
	//		vecPeople.push_back( *tempPerson );
	//	}
	//	if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	//}
	//if( vecPeople.size() != 0 ) return true;

	return false;
}

// Finds people with a cetain health range (inclusive of the min and max values)
bool cDIY_Map::FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	//for( int i = 0; i != this->theMap.size(); i++ )
	//{
	//	sPerson* tempPerson = this->theMap.pCurrent->value;
	//	if( tempPerson->health >= minHealth && tempPerson->health <= maxHealth )
	//	{
	//		vecPeople.push_back( *tempPerson );
	//	}
	//	if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	//}
	//if( vecPeople.size() != 0 ) return true;
	return false;
}

// Combination of the two functions above
bool cDIY_Map::FindPeople( std::vector<sPerson> &vecPeople,
	sPoint location, float radius,
	float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	//for( int i = 0; i != this->theMap.size(); i++ )
	//{
	//	sPerson* tempPerson = this->theMap.pCurrent->value;

	//	if( ( tempPerson->health >= minHealth && tempPerson->health <= maxHealth ) &&
	//		distanceAB( tempPerson->location, location ) <= radius )
	//	{
	//		vecPeople.push_back( *tempPerson );
	//	}

	//	if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	//}
	//if( vecPeople.size() != 0 ) return true;
	return false;
}

// Sorts the people, then returns the container of sorted people
// - this is from the data loaded by LoadDataFilesIntoContainer()
bool cDIY_Map::SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType )
{
	vecPeople.clear();

	//if( this->theMap.size() != 0 )
	//{
	//	this->mySorter.sortBy = sortType;	// <-- Sets the sorting type of the functor

	//	int times = this->theMap.size() - 1;

	//	// The good and old bubble sort...
	//	while( times > 0 )
	//	{
	//		for( int i = 0; i != times; i++ )
	//		{
	//			sPerson* op_person1 = this->theMap.pCurrent->value;			// Copy the first operand (current)
	//			sPerson* op_person2 = this->theMap.pCurrent->pNext->value;		// Copy the next operand (current->next)

	//			// Compare the next operand ( i+1 ) with the current operand ( i )
	//			if( this->mySorter( op_person2, op_person1 ) )
	//			{	// The sorting condition is true, invert the positions of the operands
	//				this->theMap.pCurrent->value = op_person2;
	//				this->theMap.pCurrent->pNext->value = op_person1;
	//			}
	//		}
	//		times--;	// In each pass go one position less in the vector...
	//	}

	//	// Copy the sorted cMap to the output vector
	//	for( int i = 0; i != this->theMap.size(); i++ )
	//	{
	//		vecPeople.push_back( *this->theMap.pCurrent->value );
	//	}
	//	return true;
	//}

	return false;
}

// Can be called after every function. 
// Calls from any of the above functions overwrites this data. 
// Measuring starts from when call is made to just before it returns.
bool cDIY_Map::GetPerformanceFromLastCall( sPerfData &callStats )
{
	return false;
}


// Returns the enum from the cPerson.h file
eContainerType cDIY_Map::getContainerType( void )
{
	return this->type;
}