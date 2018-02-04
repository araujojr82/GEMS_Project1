
#include "cSmartArray.h"

int main_VECTOR_SmartArray()
{
	cSmartArray myVec;
	
	sPerson Bob;
	Bob.first = "Bob"; Bob.last = "Smith";

	for ( int count = 0; count != 10000000000; count++ )
	{
		myVec.insert_at_end(Bob);			//	myvec.push_back(Bob);
	}

//	myVec.assignAtIndex( 3, Bob );		//	myVec[3] = Bob;


	sPerson testPerson = myVec.lookUpAtIndex( 9 );		// testPerson = myVec[3];

	return 0;
}





















//class Box
//{
//	template < class T >
//	operator+(T &a)
//		//operator+( Box &a );
//		//operator+( Tube &a );
//		//operator+( Bag &a );
//}
//class Bag
//{
//	operator+(Box &a);
//	operator+=(Box &a);
//	operator+(Tube &a);
//	operator+=(Tube &a);
//	operator+(Bag &a);
//	operator+=(Bag &a);
//}
//class Tube
//{
//	operator+(Box &a);
//	operator+(Tube &a);
//	operator+(Bag &a);
//}
//
//
//void OhGawdNo()
//{
//	Tube Sally_tube;
//	Bag Sally_Bag;
//	Box Sally_smallBox;
//
//	Box BigOrder;
//	//BigOrder = BigOrder.operator+( Sally_tube );
//	BigOrder = BigOrder + Sally_tube;
//	BigOrder += Sally_tube;
//
//	BigOrder = BigOrder + Sally_Bag;
//	BigOrder = BigOrder + Sally_smallBox;
//}
