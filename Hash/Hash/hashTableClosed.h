#pragma once

#include <string.h>
#include "sha1.h"

#define SIZE 10
#define LOGINLENGTH 10

typedef char UserLogin[LOGINLENGTH];

class HashTableClosed
{
public:
	HashTableClosed();
	~HashTableClosed();
	void add(UserLogin usr_login, uint* usr_pwd_sha);
	void resize();
	void del(UserLogin usr_login);
	uint* find(UserLogin usr_login);
	int getMemSize();
	void getUserList(std::string* usr_arr);

private:

	enum enPairStatus
	{
		free,
		engaged,
		deleted
	};

	struct Pair
	{
		Pair() : usr_login(""), usr_pwd_sha(), status(enPairStatus::free) {}

		Pair(UserLogin _usr_login, uint* _usr_pwd_sha) : usr_pwd_sha(_usr_pwd_sha), status(enPairStatus::engaged)
		{
			strcpy(usr_login, _usr_login);
		}

		Pair& operator = (const Pair& other)
		{
			usr_pwd_sha = other.usr_pwd_sha;
			strcpy(usr_login, other.usr_login);
			status = other.status;
			return *this;
		}

		UserLogin usr_login;
		uint* usr_pwd_sha;
		enPairStatus status;
	};

	int hash_func(UserLogin usr_login, int offset);

	Pair* array;
	int mem_size;
	int count;
};