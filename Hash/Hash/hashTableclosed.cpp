#include "hashTableClosed.h"

HashTableClosed::HashTableClosed()
{
	count = 0;
	mem_size = SIZE;
	array = new Pair[mem_size];
}

HashTableClosed::~HashTableClosed()
{
	delete[] array;
}

int HashTableClosed::hash_func(UserLogin usr_login, int offset)
{
	const double A = 0.7;
	int sum = 0, i = 0;
	for (; i < strlen(usr_login); i++)
	{
		sum += usr_login[i];
	}
	return int(offset * (A * sum - int(A * sum)));
}

void HashTableClosed::add(UserLogin usr_login, uint* usr_pwd_sha)
{
	int index = -1, i = 0;

	for (; i < mem_size; i++)
	{
		index = hash_func(usr_login, i);
		if (array[index].status == enPairStatus::free)
			break;
	}

	if (i >= mem_size) {
		resize();
		add(usr_login, usr_pwd_sha);
	}
	else {
		array[index] = Pair(usr_login, usr_pwd_sha);
		count++;
	}
}

void HashTableClosed::resize()
{
	Pair* save = array;
	int save_ms = mem_size;

	mem_size *= 2;
	array = new Pair[mem_size];
	count = 0;
	for (int i = 0; i < save_ms; i++) {
		Pair& old_pair = save[i];
		if (old_pair.status == enPairStatus::engaged) {
			add(old_pair.usr_login, old_pair.usr_pwd_sha);
		}
	}
	delete[] save;
}

void HashTableClosed::del(UserLogin _usr_login)
{
	int index = -1, i = 0;
	for (; i < mem_size; i++) {
		index = hash_func(_usr_login, i);
		if (array[index].status == enPairStatus::engaged && !strcmp(array[index].usr_login, _usr_login))
		{
			array[index].status = enPairStatus::deleted;
			strcpy(array[index].usr_login, "");
			array[index].usr_pwd_sha = 0;
			count--;
			return;
		}
		else if (array[index].status == enPairStatus::free) {
			return;
		}
	}
}

uint* HashTableClosed::find(UserLogin _usr_login)
{
	for (int i = 0; i < mem_size; i++)
	{
		int index = hash_func(_usr_login, i);
		if (array[index].status == enPairStatus::engaged && !strcmp(array[index].usr_login, _usr_login))
			return array[index].usr_pwd_sha;
		else if (array[index].status == enPairStatus::free)
			return nullptr;
	}
	return nullptr;
}

int HashTableClosed::getMemSize()
{
	return mem_size;
}

void HashTableClosed::getUserList(std::string* usr_arr)
{
	int k = 0, i = 0;
	for (; i < getMemSize(); i++)
	{
		if (array[i].status == enPairStatus::engaged)
		{
			usr_arr[k++] = array[i].usr_login;
		}
	}
}