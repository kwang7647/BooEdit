#include <iostream>
#include <sstream>
#include "HashMap.hpp"
#include "UserCmnd.hpp"
#include "DebugCmnd.hpp"


// KEVIN WANG 23797282

int main()
{
	HashMap hm;
	UserCmnd uc;
	DebugCmnd dc;
	std::cout<<std::endl;
	
	while(true)
	{
		std::string blah;
		std::getline(std::cin,blah);
		if(uc.isQuit(blah) == true)
		{
			std::cout<<"GOODBYE"<<std::endl;
			std::cout<<std::endl;
			break;
		}
		else
		{
			if(uc.checkAndDoUser(hm,blah) == false)
			{
				if(dc.checkAndDoDebug(hm,blah) == false)
				{
					std::cout<<"INVALID"<<std::endl;
					continue;
				}
			}
		}
	}
    return 0;
}
