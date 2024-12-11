#pragma once
#include "hashTableClosed.h"

class Chat {
public:
    Chat();
    ~Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
    void delUser(char _login[LOGINLENGTH]);
    int getUserCount();
    void getUsers();
private:
    HashTableClosed* Data;
    int data_count;
};