#include <iostream>
#ifndef USERCMND_HPP
#define USERCMND_HPP
#include "HashMap.hpp"


// KEVIN WANG 23797282


class UserCmnd
{

public:	

	UserCmnd();

	bool isQuit( std::string& s);

	bool checkAndDoUser(HashMap& hm, std::string& s);

private:

	bool create( HashMap& hm, const std::string& username, const std::string& password);

	bool login( HashMap& hm, const std::string& username, const std::string& password);

	bool remove( HashMap& hm, const std::string& username);

	bool clear( HashMap& hm);
};


#endif //USERCMND_HPP

