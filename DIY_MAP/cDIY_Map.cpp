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
}

cDIY_Map::~cDIY_Map()
{
	delete this;
}

bool cDIY_Map::LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
	std::string firstNameMaleFileName,
	std::string lastNameFileName )
{
	startPerformanceData();

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
	
	stopPerformanceData();
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
	startPerformanceData();

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

	stopPerformanceData();
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
	if( b_runPerformanceData ) startPerformanceData();

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

	if( b_runPerformanceData ) stopPerformanceData();

	if( vecPeople.size() != 0 ) return true;
	return false;
}

bool cDIY_Map::FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople )
{
	startPerformanceData();
	b_runPerformanceData = false;

	std::vector<sPerson> tempVec;
	int currentMax;

	currentMax = maxNumberOfPeople;

	for( int i = 0; i != vecPeopleToMatch.size(); i++ )
	{
		tempVec.clear();
		if( currentMax == 0 ) break;					// STOP ADDING PEOPLE WHEN REACHES MAX
		if( this->FindPeopleByName( tempVec, vecPeopleToMatch[i], currentMax ) )
		{
			// ADD the results of the individual search to the collective result
			for( int j = 0; j != tempVec.size(); j++ )
			{
				vecPeople.push_back( tempVec[j] );
			}
			currentMax -= tempVec.size();
		}
	}

	stopPerformanceData();
	b_runPerformanceData = true;

	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Returns false if not found.
bool cDIY_Map::FindPersonByID( sPerson &person, unsigned long long uniqueID )
{
	startPerformanceData();

	cList<sPerson*>* tempList;		
	tempList = &this->theMapByID.get( uniqueID );	// Get the cList of people with this Last name's hash 
	tempList->moveToFirst();							// Move to first element

	for( int i = 0; i != tempList->size(); i++ )		// Loops to find people with that last name
	{
		if( tempList->pCurrent->value->uniqueID == uniqueID )
		{
			person = *tempList->pCurrent->value;
			stopPerformanceData();
			return true;
		}
		tempList->moveToNext();
	}

	stopPerformanceData();
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
	startPerformanceData();

	cMap<sPerson*>* tempMap = &this->theMapByID;
	cList<sPerson*>* tempList;

	for( int i = 0; i != tempMap->size(); i++ )
	{
		tempList = &this->theMapByID.get( i );	// Get the cList of people with this Last name's hash 
		tempList->moveToFirst();							// Move to first element

		for( int i = 0; i != tempList->size(); i++ )		// Loops to find people with that last name
		{
			sPerson* tempPerson = tempList->pCurrent->value;

			if( distanceAB( tempPerson->location, location ) <= radius )
			{
				vecPeople.push_back( *tempPerson );
			}
			if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
			tempList->moveToNext();
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	
	stopPerformanceData();
	
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Finds people with a certain health range (inclusive of the min and max values)
bool cDIY_Map::FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	startPerformanceData();

	cMap<sPerson*>* tempMap = &this->theMapByID;
	cList<sPerson*>* tempList;

	for( int i = 0; i != tempMap->size(); i++ )
	{
		tempList = &this->theMapByID.get( i );	// Get the cList of people with this Last name's hash 
		tempList->moveToFirst();							// Move to first element

		for( int i = 0; i != tempList->size(); i++ )		// Loops to find people with that last name
		{
			sPerson* tempPerson = tempList->pCurrent->value;

			if( tempPerson->health >= minHealth && tempPerson->health <= maxHealth )
			{
				vecPeople.push_back( *tempPerson );
			}
			if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
			tempList->moveToNext();
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}

	stopPerformanceData();

	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Combination of the two functions above
bool cDIY_Map::FindPeople( std::vector<sPerson> &vecPeople,
	sPoint location, float radius,
	float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	startPerformanceData();

	cMap<sPerson*>* tempMap = &this->theMapByID;
	cList<sPerson*>* tempList;

	for( int i = 0; i != tempMap->size(); i++ )
	{
		tempList = &this->theMapByID.get( i );	// Get the cList of people with this Last name's hash 
		tempList->moveToFirst();							// Move to first element

		for( int i = 0; i != tempList->size(); i++ )		// Loops to find people with that last name
		{
			sPerson* tempPerson = tempList->pCurrent->value;

			if( ( tempPerson->health >= minHealth && tempPerson->health <= maxHealth ) &&
				distanceAB( tempPerson->location, location ) <= radius )
			{
				vecPeople.push_back( *tempPerson );
			}
			if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
			tempList->moveToNext();
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}

	stopPerformanceData();
	
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Sorts the people, then returns the container of sorted people
// - this is from the data loaded by LoadDataFilesIntoContainer()
bool cDIY_Map::SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType )
{
	startPerformanceData();

	vecPeople.clear();

	cMap<sPerson*>* tempMap = NULL;
	int begin;
	int end;
	int step;
	bool backwards = false;

	switch( sortType )								// Choosing which map to use
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
		tempMap = &this->theMapByFirst;
		break;
	case iPersonMotron::DESC_FIRST_THEN_LAST:
		tempMap = &this->theMapByFirst;
		backwards = true;
		break;
	case iPersonMotron::ASC_LAST_THEN_FIRST:
		tempMap = &this->theMapByLast;
		break;
	case iPersonMotron::DESC_LAST_THEN_FIRST:
		tempMap = &this->theMapByLast;
		backwards = true;
		break;
	case iPersonMotron::ASC_BY_ID:
		tempMap = &this->theMapByID;
		break;
	case iPersonMotron::DESC_BY_ID:
		tempMap = &this->theMapByID;
		backwards = true;
		break;
	case iPersonMotron::ASC_BY_HEALTH:
		tempMap = &this->theMapByHealth;
		break;
	case iPersonMotron::DESC_BY_HEALTH:
		tempMap = &this->theMapByHealth;
		backwards = true;
		break;	
	}

	if( backwards )
	{
		begin = tempMap->size() - 1;
		end = -1;
		step = -1;		// Invert the loop variables to loop backwards
	}
	else
	{
		begin = 0;
		end = tempMap->size();		
		step = 1;
	}

	// This is the number of passes for the bubble sort
	int times = tempMap->size() - 1;
	
	cList<sPerson*> tempList;

	if( tempMap->size() != 0 )
	{
		this->mySorter.sortBy = sortType;	// <-- Sets the sorting type of the functor

		// The good and old bubble sort...
		while( times > 0 )
		{
			for( int i = begin; i != end; i += step )
			{
				tempList = tempMap->get( i );
				if( tempList.isValid )
				{
					if( tempList.size() > 1 ) // Check if theres anything to sort
					{
						tempList.moveToFirst();
						for( int j = 0; j != tempList.size() - 1; j++ )
						{
							sPerson* op_person1 = tempList.pCurrent->value;			// Copy the begin operand (current)
							sPerson* op_person2 = tempList.pCurrent->pNext->value;		// Copy the next operand (current->next)

																						// Compare the next operand ( i+1 ) with the current operand ( i )
							if( this->mySorter( op_person2, op_person1 ) )
							{	// The sorting condition is true, invert the positions of the operands
								tempList.pCurrent->value = op_person2;
								tempList.pCurrent->pNext->value = op_person1;								
								tempMap->set( i, tempList );
							}
							tempList.moveToNext();
						}
					}
				}
			}
			times--;	// In each pass go one position less in the vector...
		}

		// Copy the sorted cMap to the output vector
		for( int i = begin; i != end; i += step )
		{
			tempList = tempMap->get( i );					// In each step get the cList for this posiiton

			tempList.moveToFirst();						// Move to first element

			if( i == 1199 )
			{
				i = i;
			}
			

			for( int i = 0; i != tempList.size(); i++ )	// Loops through the list
			{
				vecPeople.push_back( *tempList.pCurrent->value );
				tempList.moveToNext();
			}
		}		
	}
	
	stopPerformanceData();
	return true;
}

// Can be called after every function. 
// Calls from any of the above functions overwrites this data. 
// Measuring starts from when call is made to just before it returns.
bool cDIY_Map::GetPerformanceFromLastCall( sPerfData &callStats )
{
	callStats = this->theCallStats;
	return true;
}

void cDIY_Map::startPerformanceData( void )
{
	this->theCallStats = sPerfData();
	this->start = std::chrono::system_clock::time_point();
	this->start = std::chrono::system_clock::now();

	uint64_t currentUsedRAM( 0 );

	PROCESS_MEMORY_COUNTERS info;
	GetProcessMemoryInfo( GetCurrentProcess(), &info, sizeof( info ) );
	currentUsedRAM = info.WorkingSetSize;

	this->theCallStats.memoryUsageBytes_min = ( float )currentUsedRAM;

	return;
}

void cDIY_Map::stopPerformanceData()
{
	std::chrono::system_clock::time_point done;
	done = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = done - this->start;

	this->theCallStats.elapsedCallTime_ms = ( float )
		std::chrono::duration_cast< std::chrono::milliseconds >( diff ).count();

	uint64_t currentUsedRAM( 0 );

	PROCESS_MEMORY_COUNTERS info;
	GetProcessMemoryInfo( GetCurrentProcess(), &info, sizeof( info ) );
	currentUsedRAM = info.WorkingSetSize;

	this->theCallStats.memoryUsageBytes_max = ( float )currentUsedRAM;
	this->theCallStats.memoryUsageBytes_avg = ( this->theCallStats.memoryUsageBytes_max +
		this->theCallStats.memoryUsageBytes_max ) / 2;

	return;
}

// Returns the enum from the cPerson.h file
eContainerType cDIY_Map::getContainerType( void )
{
	return this->type;
}