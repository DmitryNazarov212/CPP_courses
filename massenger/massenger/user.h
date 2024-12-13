#pragma once
#include <string>
#include <vector>
class User
{
private:
	const std::string _login;
	const std::string _password;
	const std::string _name;
public:

	User() = default;
	User(const std::string& login, const std::string& password, const std::string& name)
		: _login(login), _password(password), _name(name) {}

	const std::string& getLogin() const {return _login;}
	const std::string& getName() const { return _name; }
	bool validatePassword(const std::string& password) const  { return _password == password; }

	~User() = default;

};