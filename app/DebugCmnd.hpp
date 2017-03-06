#include <iostream>
#ifndef DEBUGCMND_HPP
#define DEBUGCMND_HPP
#include "HashMap.hpp"


// KEVIN WANG 23797282


class DebugCmnd
{

public:

	DebugCmnd();

	bool checkAndDoDebug(HashMap& hm, std::string& s);


private:

	bool isOn;

	bool turnDebugOn();

	bool turnDebugOff();

	bool getUnsignedIntsFromMap( unsigned int(HashMap::*func)()const, HashMap& hm);

	bool getLoadFactor(HashMap& hm);

};


#endif //DEBUGCMND_HPP