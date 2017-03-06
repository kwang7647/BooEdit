#include <iostream>
#include <sstream>
#include "UserCmnd.hpp"
#include "HashMap.hpp"


// KEVIN WANG 23797282


UserCmnd::UserCmnd()
{}

bool UserCmnd::isQuit(std::string& s)
{
	std::istringstream iss{s};
	std::string first;
	iss>>first;
	return first == "QUIT";
}

bool UserCmnd::checkAndDoUser(HashMap& hm, std::string& s ) 
{
	std::istringstream iss{s};
	std::string first;
	iss>>first;
	if(first == "CREATE")
	{
		std::string username;
		iss>> username;
		std::string password;
		iss>> password;
		return (create(hm,username,password));
	}
	else if(first == "LOGIN")
	{
		std::string username;
		iss>> username;
		std::string password;
		iss>> password;
		return (login(hm,username,password));
	}
	else if(first == "REMOVE")
	{
		std::string username;
		iss>>username;
		std::string temp;
		iss>>temp;
		if(temp != "")
			return false;
		else
			return (remove(hm,username));
	}
	else if(first == "CLEAR")
		return clear(hm);
	else
		return false;
}

bool UserCmnd::create(HashMap& hm, const std::string& username, const std::string& password)
{
	if(username == "" || password == "")
	{
		return false;
	}
	else if(hm.contains(username) == true)
	{
		std::cout<<"EXISTS"<<std::endl;
	}
	else
	{
		hm.add(username,password);
		std::cout<<"CREATED"<<std::endl;
	}
	return true;
}

bool UserCmnd::login( HashMap& hm, const std::string& username, const std::string& password)
{
	if(username == "" || password == "")
	{
		return false;
	}
	else if(hm.contains(username) == false || hm.value(username) != password)
	{
		std::cout<<"FAILED"<<std::endl;
	}
	else
	{
		std::cout<<"SUCCEEDED"<<std::endl;
	}
	return true;
}

bool UserCmnd::remove( HashMap& hm, const std::string& username)
{
	if(username == "" || hm.contains(username) == false)
	{
		std::cout<<"NONEXISTANT"<<std::endl;
	}
	else
	{
		hm.remove(username);
		std::cout<<"REMOVED"<<std::endl;
	}
	return true;
}

bool UserCmnd::clear(HashMap& hm)
{
	std::string* allKeys = hm.getAllKeys();
	
	if(allKeys != NULL)
	{
		unsigned int size = hm.size();		
		for( unsigned int x = 0; x<size ;x++)
		{
			hm.remove(allKeys[x]);
		}
	}
	delete[] allKeys;
	std::cout<<"CLEARED"<<std::endl;
	return true;
}
