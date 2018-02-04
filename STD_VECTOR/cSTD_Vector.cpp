#include "cSTD_Vector.h"

extern std::string getRandomString( std::vector< std::string > theVectorOfStrings );
extern std::string getRandomFirstName( std::vector< std::string > maleNames, std::vector< std::string > femaleNames );
extern std::string getRandomLastName( std::vector< std::string > lastNames );
extern int getRandomAge();
extern float getRandomHealth();
extern sPoint getRandomLocation();

int cSTD_Vector::uniqueID = 0;

cSTD_Vector::cSTD_Vector()
{
	this->type = STD_VECTOR;
	//this->uniqueID = 0;

	// Initialize the rand() with a time seed
	time_t curTime;
	time( &curTime );

	// Using time as seed for random generation
	srand( (int)curTime );
}

cSTD_Vector::~cSTD_Vector()
{

}

bool cSTD_Vector::LoadDataFilesIntoContainer( std::string firstNameFemaleFileName,
											  std::string firstNameMaleFileName,
											  std::string lastNameFileName )
{
	vecFemaleNames.clear();
	vecMaleNames.clear();
	vecLastNames.clear();

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
			vecFemaleNames.push_back( tempName );
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
			vecMaleNames.push_back( tempName );
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
			vecLastNames.push_back( tempName );
			lastNameFile >> garbage >> garbage >> garbage;
		}
	}
	return true;
}

int cSTD_Vector::getPersonID()
{
	this->uniqueID++;

	return this->uniqueID;
}


// Based on the files that have been loaded, generate people.
// Should be a mix of male and female names.
// Unique IDs must be unique								 
bool cSTD_Vector::GenerateRandomPeople( int numberOfPeople )
{

	for( int i = 0; i != numberOfPeople; i++ )
	{
		sPerson* newPerson = new sPerson();
		newPerson->uniqueID = this->getPersonID();
		newPerson->first = getRandomFirstName( vecFemaleNames, vecMaleNames );
		newPerson->last = getRandomLastName( vecLastNames );
		newPerson->age = getRandomAge();
		newPerson->health = getRandomHealth();
		newPerson->location = getRandomLocation();

		this->theVector.push_back( newPerson );
	}

	return false;
}

// Returns only people with this name 
// If the name (first or last) is blank (""), then ignore this parameter.
// For example: 
// - if last name is "", search only by first name
// - if first name is "", search only by last name
// - if both names are blank, return everyone
bool cSTD_Vector::FindPeopleByName( std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople )
{

	for( int i = 0; i != this->theVector.size(); i++ )
	{
		if( personToMatch.first == "" )							// First Name is blank
		{
			if( personToMatch.last == "" )						// Last Name is blank
			{	// Return all persons
				vecPeople.push_back( *this->theVector[i] );
			}
			else												// Last Name is NOT blank
			{	// Look for people with this last name
				if( this->theVector[i]->last == personToMatch.last )
				{
					vecPeople.push_back( *this->theVector[i] );
				}
			}
		}
		else													// First Name is NOT blank
		{
			if( personToMatch.last == "" )						// Last Name is blank
			{	// Return all persons with the first name
				if( this->theVector[i]->first == personToMatch.first )
				{
					vecPeople.push_back( *this->theVector[i] );
				}
			}
			else												// Last Name is NOT blank
			{	// Look for people with this first AND last name
				if( this->theVector[i]->first == personToMatch.first && 
					this->theVector[i]->last == personToMatch.last )
				{
					vecPeople.push_back( *this->theVector[i] );
				}
			}
		}				
		if( vecPeople.size() == maxNumberOfPeople ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

bool cSTD_Vector::FindPeopleByName( std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople )
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
bool cSTD_Vector::FindPersonByID( sPerson &person, unsigned long long uniqueID )
{
	for( int i = 0; i != this->theVector.size(); i++ )
	{
		if( this->theVector[i]->uniqueID == uniqueID )
		{
			person = *this->theVector[i];
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
bool cSTD_Vector::FindPeople( std::vector<sPerson> &vecPeople, sPoint location, float radius,
	int maxPeopleToReturn )
{
	for( int i = 0; i != this->theVector.size(); i++ )
	{
		//float distance = distanceAB( this->theVector[i]->location, location );
		if( distanceAB( this->theVector[i]->location, location ) <= radius )
		{
			vecPeople.push_back( *this->theVector[i] );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;

	return false;
}

// Finds people with a cetain health range (inclusive of the min and max values)
bool cSTD_Vector::FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	for( int i = 0; i != this->theVector.size(); i++ )
	{
		if( this->theVector[i]->health >= minHealth && 
			this->theVector[i]->health <= maxHealth )
		{
			vecPeople.push_back( *this->theVector[i] );
		}
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Combination of the two functions above
bool cSTD_Vector::FindPeople( std::vector<sPerson> &vecPeople,
	sPoint location, float radius,
	float minHealth, float maxHealth,
	int maxPeopleToReturn )
{
	for( int i = 0; i != this->theVector.size(); i++ )
	{
		if( ( this->theVector[i]->health >= minHealth && 
			  this->theVector[i]->health <= maxHealth ) && 
			  distanceAB( this->theVector[i]->location, location ) <= radius )
		{
			vecPeople.push_back( *this->theVector[i] );
		}
		
		if( vecPeople.size() == maxPeopleToReturn ) break;	// STOP ADDING PEOPLE WHEN REACHES MAX
	}
	if( vecPeople.size() != 0 ) return true;
	return false;
}

// Sorts the people, then returns the container of sorted people
// - this is from the data loaded by LoadDataFilesIntoContainer()
bool cSTD_Vector::SortPeople( std::vector<sPerson> &vecPeople, eSortType sortType )
{
	vecPeople.clear();

	if( this->theVector.size() != 0 )
	{
		this->mySorter.sortBy = sortType;
		std::sort( this->theVector.begin(), this->theVector.end(), this->mySorter );

		for( int i = 0; i != this->theVector.size(); i++ )
		{
			vecPeople.push_back( *this->theVector[i] );
		}		
		return true;
	}	

	return false;
}

// Can be called after every function. 
// Calls from any of the above functions overwrites this data. 
// Measuring starts from when call is made to just before it returns.
bool cSTD_Vector::GetPerformanceFromLastCall( sPerfData &callStats )
{
	return false;
}


// Returns the enum from the cPerson.h file
eContainerType cSTD_Vector::getContainerType( void )
{
	return this->type;
}