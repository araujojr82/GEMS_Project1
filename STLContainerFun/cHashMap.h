#ifndef _cHashMap_HG_
#define _cHashMap_HG_

#include <string>
#include "cList.h"

struct sWizard
{
	sWizard() : health(0.0f), bIsValid(false){}
	std::string first;
	std::string last;
	float health;
	bool bIsValid;	// Used by the hash map to store wizard
};

//map<string,sWizard>
// This is the DIY Map...
class cHashMap
{
public:
	cHashMap();

	bool findWiz(std::string name, 
				 sWizard &theWizard);
	void addWiz(std::string name, sWizard theWizard);

private:
	unsigned int m_genIndexHash(std::string name);
	bool m_getWizAt(unsigned int index);
	unsigned int m_ArraySize;

	sWizard* pWizards;		// = new sWizard[250]
	static const unsigned int INITALARRAYSIZE = 250;
};

#endif 
