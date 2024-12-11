#include "chat.h"

void Chat::registraion(const std::string& login, const std::string& password, const std::string& name)
{
	for (const auto& user : users)
	{
		if (login == user->getLogin())
		{
			std::cout << "Login already exists \n";
			return;
		}
	}
	users.push_back(std::make_unique<User>(login, password, name));
}

void Chat::logIn(const std::string login, const std::string password)
{
	bool found = false;
	for (const auto& user : users)
	{
		if (login == user->getLogin() && user->validatePassword(password)){
			std::cout << "Wellcome " << user ->getName()<< std::endl;
			found = true;
		}
	}
	if (!found)
		std::cout << "Invalid password or login \n";
}

User& Chat::operator[](size_t index)
{
	if (index >= users.size()) {
		throw std::out_of_range("Index out of range");
	}
	return *users[index];
}

const User& Chat::operator[](size_t index) const
{
	if (index >= users.size()) {
		throw std::out_of_range("Index out of range");
	}
	return *users[index];
}

void Chat::print()
{
	Message message;
	message.sendMessage(users[0]->getLogin(), users[1]->getLogin(), "Hello");
}