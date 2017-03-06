#include <iostream>
#include <sstream>
#include "DebugCmnd.hpp"
#include "HashMap.hpp"


// KEVIN WANG 23797282


DebugCmnd::DebugCmnd()
	: isOn{false}
{}

bool DebugCmnd::checkAndDoDebug(HashMap& hm, std::string& s)
{
	std::istringstream iss{s};
	std::string first;
	iss>>first;
	if(first == "DEBUG")
	{
		std::string second;
		iss>>second;
		if(second == "ON")
			return turnDebugOn();
		else if(second == "OFF")
			return turnDebugOff();
		else
			return false;
	}
	else if( isOn == true )
	{
		if(first=="LOGIN")
		{
			std::string second;
			iss>>second;
			if(second == "COUNT")
			{
				//return getLoginCount(hm);
				return getUnsignedIntsFromMap(&HashMap::size, hm);
			}
		}
		else if(first == "BUCKET")
		{
			std::string second;
			iss>>second;
			if(second == "COUNT")
			{
				return getUnsignedIntsFromMap(&HashMap::bucketCount, hm);
			}
		}
		else if(first == "LOAD")
		{
			std::string second;
			iss>>second;
			if(second == "FACTOR")
			{
				return getLoadFactor(hm);
			}
		}
		else if (first == "MAX")
		{
			std::string second;
			iss>>second;
			if(second == "BUCKET")
			{
				std::string third;
				iss>>third;
				if(third == "SIZE")
				{
					return getUnsignedIntsFromMap(&HashMap::maxBucketSize, hm);
				}
			}
		}
		return false;
	}
	else
		return false;
}

bool DebugCmnd::turnDebugOn()
{
	if(isOn == false)
	{
		std::cout<<"NOW ON"<<std::endl;
		isOn = !isOn;
	}
	else
	{
		std::cout<<"ALREADY ON"<<std::endl;
	}
	return true;
}

bool DebugCmnd::turnDebugOff()
{
	if(isOn == true)
	{
		std::cout<<"NOW OFF"<<std::endl;
		isOn = !isOn;
	}
	else
	{
		std::cout<<"ALREADY OFF"<<std::endl;
	}
	return true;
}

bool DebugCmnd::getUnsignedIntsFromMap( unsigned int(HashMap::*func)()const, HashMap& hm)
{
	unsigned int num = (hm.*func)();
	std::cout<<num<<std::endl;
	return true;
}

bool DebugCmnd::getLoadFactor(HashMap& hm)
{
	double num = hm.loadFactor();
	std::cout<<num<<std::endl;
	return true;
}
