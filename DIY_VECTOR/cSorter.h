#ifndef _cSorter_HG_
#define _cSorter_HG_

#include "iPersonMotron.h"

class cSorter
{
public:
	iPersonMotron::eSortType sortBy;

	bool operator() ( const sPerson* A, const sPerson* B )
	{
		switch( this->sortBy )
		{
		case iPersonMotron::ASC_FIRST_THEN_LAST:
			if( A->first < B->first )
			{
				return true;
			}
			else if( A->first == B->first )
			{
				if( A->last < B->last )
				{
					return true;
				}
			}
			return false;			

		case iPersonMotron::DESC_FIRST_THEN_LAST:
			if( A->first > B->first )
			{
				return true;
			}
			else if( A->first == B->first )
			{
				if( A->last > B->last )
				{
					return true;
				}
			}
			return false;

		case iPersonMotron::ASC_LAST_THEN_FIRST:
			if( A->last < B->last )
			{
				return true;
			}
			else if( A->last == B->last )
			{
				if( A->first < B->first )
				{
					return true;
				}
			}
			return false;
			
		case iPersonMotron::DESC_LAST_THEN_FIRST:
			if( A->last > B->last )
			{
				return true;
			}
			else if( A->last == B->last )
			{
				if( A->first > B->first )
				{
					return true;
				}
			}
			return false;
			
		case iPersonMotron::ASC_BY_ID:
			if( A->uniqueID < B->uniqueID )
			{
				return true;
			}
			return false;
		case iPersonMotron::DESC_BY_ID:
			if( A->uniqueID > B->uniqueID )
			{
				return true;
			}
			return false;
		case iPersonMotron::ASC_BY_HEALTH:
			if( A->health < B->health )
			{
				return true;
			}
			return false;
		case iPersonMotron::DESC_BY_HEALTH:
			if( A->health > B->health )
			{
				return true;
			}
			return false;
		}
		return false;
	}
private:

};

#endif