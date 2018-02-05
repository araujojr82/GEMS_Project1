#include "cDIY_List.h"

extern std::string getRandomString( cList< std::string > theVectorOfStrings );
extern std::string getRandomFirstName( cList< std::string > maleNames, cList< std::string > femaleNames );
extern std::string getRandomLastName( cList< std::string > lastNames );
extern int getRandomAge();
extern float getRandomHealth();
extern sPoint getRandomLocation();

int cDIY_List::uniqueID = 0;

cDIY_List::cDIY_List()
{
	this->type = CUSTOM_DIY_LIST;

	// Initialize the rand() with a time seed
	time_t curTime;
	time( &curTime );

	// Using time as seed for random generation
	srand( ( int )curTime );
}

cDIY_List::~cDIY_List()
{
	delete this;
}

bool cDIY_List::LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
	std::string firstNameMaleFileName,
	std::string lastNameFileName )
{
	listFemaleNames.clear();
	listMaleNames.clear();
	listLastNames.clear();

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
			listFemaleNames.push_back( tempName );
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
			listMaleNames.push_back( tempName );
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
			listLastNames.push_back( tempName );
			lastNameFile >> garbage >> garbage >> garbage;
		}
	}
	return true;
}

int cDIY_List::getPersonID()
{
	this->uniqueID++;

	return this->uniqueID;
}


// Based on the files that have been loaded, generate people.
// Should be a mix of male and female names.
// Unique IDs must be unique								 
bool cDIY_List::GenerateRandomPeople( int numberOfPeople )
{

	for( int i = 0; i != numberOfPeople; i++ )
	{
		sPerson* newPerson = new sPerson();
		newPerson->uniqueID = this->getPersonID();
		newPerson->first = getRandomFirstName( listFemaleNames, listMaleNames );
		newPerson->last = getRandomLastName( listLastNames );
		newPerson->age = getRandomAge();
		newPerson->health = getRandomHealth();
		newPerson->location = getRandomLocation();

		this->theList.push_back( newPerson );
	}

	return false;
}

// Returns only people with this name 
// If the name (first or last) is blank (""), then ignore this parameter.
// For example: 
// - if last name is "", search only by first name
// - if first name is "", search only by last name
// - if both names are blank, return everyone
bool cDIY_List::FindPeopleByName( std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople )
{
	this->theList.moveToFirst();	

	for( int i = 0; i != this->theList.size(); i++ )
	{
		sPerson* tempPerson = this->theList.pCurrent->value;

		if( personToMatch.first == "" )							// First Name is blank
		{
			if( personToMatch.last == "" )						// Last Name is blank
			{	// Return all persons
				vecPeople.push_back( *tempPerson );
			}
			else												// Last Name is NOT blank
			{	// Look for people with this last name
				if( tempPerson->last == personToMatch.last )
				{
					vecPeople.push_back( *tempPerson );
				}
			}
		}
		else													// First Name is NOT blank
		{
			if( personToMatch.last == "" )						// Last Name is blank
			{	// Return all persons with the first name
				if( tempPerson->first == personToMatch.first )
				{
					vecPeople.push_back( *tempPerson );
				}
			}
			else												// Last Name is NOT blank
			{	// Look for people with this first AND last name
				if( tempPerson->first == personToMatch.first &&
					tempPerson->last == personToMatch.last )
				{
					vecPeople.push_back( *tempPerson );
				}
			}
		}
		if( vecPeople.size() == maxNumberOfPeople ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX

		this->theList.moveToNext();
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

bool cDIY_List::FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople )
{
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
		//if( vecPeople.size() == maxNumberOfPeople ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}

	if( vecPeople.size() != 0 ) return true;

	return false;
}

// Returns false if not found.
bool cDIY_List::FindPersonByID( sPerson &person, unsigned long long uniqueID )
{
	this->theList.moveToFirst();

	for( int i = 0; i != this->theList.size(); i++ )
	{
		sPerson* tempPerson = this->theList.pCurrent->value;
		if( tempPerson->uniqueID == uniqueID )
		{
			person = *tempPerson;
			return true;
		}
		this->theList.moveToNext();
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
bool cDIY_List::FindPeople( std::vector<sPerson> &vecPeople, sPoint location, float radius,
	int maxPeopleToReturn )
{
	this->theList.moveToFirst();

	for( int i = 0; i != this->theList.size(); i++ )
	{
		sPerson* tempPerson = this->theList.pCurrent->value;
		if( distanceAB( tempPerson->location, location ) <= radius )
		{
			vecPeople.push_back( *tempPerson );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
		this->theList.moveToNext();
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

// Finds people with a cetain health range (inclusive of the min and max values)
bool cDIY_List::FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	this->theList.moveToFirst();

	for( int i = 0; i != this->theList.size(); i++ )
	{
		sPerson* tempPerson = this->theList.pCurrent->value;
		if( tempPerson->health >= minHealth && tempPerson->health <= maxHealth )
		{
			vecPeople.push_back( *tempPerson );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
		this->theList.moveToNext();
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Combination of the two functions above
bool cDIY_List::FindPeople( std::vector<sPerson> &vecPeople,
	sPoint location, float radius,
	float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	this->theList.moveToFirst();

	for( int i = 0; i != this->theList.size(); i++ )
	{
		sPerson* tempPerson = this->theList.pCurrent->value;

		if( ( tempPerson->health >= minHealth && tempPerson->health <= maxHealth ) &&
			distanceAB( tempPerson->location, location ) <= radius )
		{
			vecPeople.push_back( *tempPerson );
		}

		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
		this->theList.moveToNext();
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Sorts the people, then returns the container of sorted people
// - this is from the data loaded by LoadDataFilesIntoContainer()
bool cDIY_List::SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType )
{
	vecPeople.clear();

	if( this->theList.size() != 0 )
	{
		this->mySorter.sortBy = sortType;	// <-- Sets the sorting type of the functor

		int times = this->theList.size() - 1;

		// The good and old bubble sort...
		while( times > 0 )
		{
			this->theList.moveToFirst();

			for( int i = 0; i != times; i++ )
			{
				sPerson* op_person1 = this->theList.pCurrent->value;			// Copy the first operand (current)
				sPerson* op_person2 = this->theList.pCurrent->pNext->value;		// Copy the next operand (current->next)

				// Compare the next operand ( i+1 ) with the current operand ( i )
				if( this->mySorter( op_person2, op_person1 ) )
				{	// The sorting condition is true, invert the positions of the operands
					this->theList.pCurrent->value = op_person2;
					this->theList.pCurrent->pNext->value = op_person1;
				}
				this->theList.moveToNext();
			}
			times--;	// In each pass go one position less in the vector...
		}

		// Copy the sorted cList to the output vector
		this->theList.moveToFirst();
		for( int i = 0; i != this->theList.size(); i++ )
		{
			vecPeople.push_back( *this->theList.pCurrent->value );
			this->theList.moveToNext();
		}
		return true;
	}

	return false;
}

// Can be called after every function. 
// Calls from any of the above functions overwrites this data. 
// Measuring starts from when call is made to just before it returns.
bool cDIY_List::GetPerformanceFromLastCall( sPerfData &callStats )
{
	return false;
}


// Returns the enum from the cPerson.h file
eContainerType cDIY_List::getContainerType( void )
{
	return this->type;
}