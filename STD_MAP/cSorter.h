#ifndef _cSorter_HG_
#define _cSorter_HG_

#include "iPersonMotron.h"

class cSorter
{
public:
	iPersonMotron::eSortType sortBy;

	sPerson* findMapEntry( std::map<int, sPerson*> &theMap )
	{
		sPerson* thePerson = new sPerson();

		// Fill the "base" person with values to be compared later
		switch( sortBy )
		{
		case iPersonMotron::ASC_FIRST_THEN_LAST:
			thePerson->first = "ZZZZZZZZZZZZZZZZZZZZZZ";
			thePerson->last  = "ZZZZZZZZZZZZZZZZZZZZZZ";
			break;
		case iPersonMotron::DESC_FIRST_THEN_LAST:
			thePerson->first = "AAAAAAAAAAAAAAAAAAAAAA";
			thePerson->last  = "AAAAAAAAAAAAAAAAAAAAAA";
			break;
		case iPersonMotron::ASC_LAST_THEN_FIRST:
			thePerson->first = "ZZZZZZZZZZZZZZZZZZZZZZ";
			thePerson->last = "ZZZZZZZZZZZZZZZZZZZZZZ";
			break;
		case iPersonMotron::DESC_LAST_THEN_FIRST:
			thePerson->first = "AAAAAAAAAAAAAAAAAAAAAA";
			thePerson->last = "AAAAAAAAAAAAAAAAAAAAAA";
			break;
		case iPersonMotron::ASC_BY_ID:
			thePerson->uniqueID = INT_MAX;
			break;
		case iPersonMotron::DESC_BY_ID:
			thePerson->uniqueID = 0;
			break;
		case iPersonMotron::ASC_BY_HEALTH:
			thePerson->health = 200.0f;
			break;
		case iPersonMotron::DESC_BY_HEALTH:
			thePerson->health = -1.0f;
			break;
		}

		// Loop through every entry of the map and find the one that attends...
		// the sort mode comparison, by comparing each entry with the "base" person
		for( std::map<int, sPerson*>::iterator itPerson = theMap.begin();
			itPerson != theMap.end();
			itPerson++ )
		{
			switch( this->sortBy )
			{
			case iPersonMotron::ASC_FIRST_THEN_LAST:
				if( thePerson->first > (*itPerson).second->first )
				{
					thePerson = ( *itPerson ).second;
				}
				else if( thePerson->first == (*itPerson).second->first )
				{
					if( thePerson->last > (*itPerson).second->last )
					{
						thePerson = ( *itPerson ).second;
					}
				}
				break;

			case iPersonMotron::DESC_FIRST_THEN_LAST:
				if( thePerson->first < (*itPerson).second->first )
				{
					thePerson = ( *itPerson ).second;
				}
				else if( thePerson->first == (*itPerson).second->first )
				{
					if( thePerson->last < (*itPerson).second->last )
					{
						thePerson = ( *itPerson ).second;
					}
				}
				break;

			case iPersonMotron::ASC_LAST_THEN_FIRST:
				if( thePerson->last > (*itPerson).second->last )
				{
					thePerson = ( *itPerson ).second;
				}
				else if( thePerson->last == (*itPerson).second->last )
				{
					if( thePerson->first > (*itPerson).second->first )
					{
						thePerson = ( *itPerson ).second;
					}
				}
				break;

			case iPersonMotron::DESC_LAST_THEN_FIRST:
				if( thePerson->last < (*itPerson).second->last )
				{
					thePerson = ( *itPerson ).second;
				}
				else if( thePerson->last == (*itPerson).second->last )
				{
					if( thePerson->first < (*itPerson).second->first )
					{
						thePerson = ( *itPerson ).second;
					}
				}
				break;

			case iPersonMotron::ASC_BY_ID:
				if( thePerson->uniqueID > (*itPerson).second->uniqueID )
				{
					thePerson = ( *itPerson ).second;
				}
				break;
			case iPersonMotron::DESC_BY_ID:
				if( thePerson->uniqueID < (*itPerson).second->uniqueID )
				{
					thePerson = ( *itPerson ).second;
				}
				break;
			case iPersonMotron::ASC_BY_HEALTH:
				if( thePerson->health > (*itPerson).second->health )
				{
					thePerson = ( *itPerson ).second;
				}
				break;
			case iPersonMotron::DESC_BY_HEALTH:
				if( thePerson->health < (*itPerson).second->health )
				{
					thePerson = ( *itPerson ).second;
				}
				break;
			}
		}
		theMap.erase( ( int )thePerson->uniqueID );	// Remove the entry found
		return thePerson;
	}
};

#endif