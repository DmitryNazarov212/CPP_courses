#include <iostream>
#include "chat.h"
#include "message.h"
#include "messanger.h"
int main()
{
	Messanger messanger;

	messanger.registration("gello", "132", "dima");
	messanger.registration("aello", "132", "tima");
	messanger.registration("fsdf", "112", "sima");
	messanger.registration("qwer", "143", "tima");
	auto current_user = messanger.log_in("gello", "132");

	std::cout << "Current user: " << current_user->getName() << std::endl;

	//messanger.sendMessageToGroup("Hello");
	int senderIndex = 0;
	int recieverIndex = 1;
	messanger.sendMessageToLocal(current_user, messanger.get_user()[recieverIndex], "Hello");
	messanger.showChatHistory(senderIndex,0);

	current_user = messanger.log_out();

	std::cout << "Logged out user: " << std::endl;

	current_user = messanger.log_in("aello", "132");
	
	senderIndex = 1;
	recieverIndex = 0;

	messanger.sendMessageToLocal(current_user, messanger.get_user()[recieverIndex], "Hello1");
	messanger.showChatHistory(senderIndex, 1);
}
