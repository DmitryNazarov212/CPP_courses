
#include "chat.h"

Chat::Chat()
{
    data_count = 0;
    Data = new HashTableClosed;
}

Chat::~Chat()
{
    delete Data;
}

int Chat::getUserCount()
{
    return data_count;
}

void Chat::getUsers()
{
    int n = Data->getMemSize();
    if (data_count == 0)
    {
        std::cout << "User base is empty now" << std::endl;
        return;
    }
    std::string* usrArr = new std::string[n];
    Data->getUserList(usrArr);
    std::cout << "User base contains:" << std::endl;
    for (int i = 0; i < data_count; i++)
    {
        std::cout << usrArr[i] << std::endl;
    }
    delete[] usrArr;
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    Data->add(_login, sha1(_pass, pass_length));
    data_count++;
    std::cout << "Registration for user \"" << _login << "\" complete" << std::endl;
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length)
{
    bool cmpHashes = false;
    if (Data->find(_login) != nullptr)
    {
        cmpHashes = !memcmp(Data->find(_login), sha1(_pass, pass_length), SHA1HASHLENGTHBYTES);
    }
    return cmpHashes;
}

void Chat::delUser(char _login[LOGINLENGTH])
{
    std::cout << "Trying to delete user with login \"" << _login << "\"..." << std::endl;
    if (Data->find(_login) == nullptr)
    {
        std::cout << "User with login \"" << _login << "\" doesn't exist" << std::endl;
        return;
    }

    Data->del(_login);
    data_count--;
    std::cout << "User with login \"" << _login << "\" deleted" << std::endl;
}
