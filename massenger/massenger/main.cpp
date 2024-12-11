#include <iostream>
#include "chat.h"
#include "message.h"
int main()
{
	Chat chat;
	Message message;
	chat.registraion("gello", "132", "dima");
	chat.registraion("gello", "132", "tima");
	chat.registraion("fsdf", "112", "sima");
	chat.registraion("qwer", "143", "tima");
	chat.logIn("gello", "132");
	chat.print();
}

