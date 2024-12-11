#pragma once
#include <iostream> 
#include <vector>
#include <memory>
#include "user.h"
#include "message.h"
class Chat
{
private:
	std::vector<std::unique_ptr<User>> users;
public:

	void registraion(const std::string& login, const std::string& password, const std::string& name);
	void logIn(const std::string login, const std::string password);
	
	User& operator[](size_t index);
	const User& operator[](size_t index) const;
	void print();
	size_t size() const { return users.size(); }
};