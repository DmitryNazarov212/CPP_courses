#include "chat.h"



void Chat::sendMessage(std::shared_ptr<User> sender, std::shared_ptr<User> reciever, std::string text)
{
	if (sender->getLogin() == reciever->getLogin())
	{
		std::cout << "You cannot send massage to yourself!" << std::endl;
		return;
	}
	message.push_back(std::make_shared<Message>(sender, text, reciever));
}
void Chat::getHistory(int senderIndex, int recieverIndex)
{

	std::cout << message[senderIndex]->get_sender()->getName() << ": " << message[senderIndex]->get_message() << message[recieverIndex]->get_reciever()->getName() << std::endl;
}













//void GroupChat::addParticipant(std::vector<std::shared_ptr<User>> users)
//{
//	for (const auto& user : users)
//	{
//		participants.push_back(user);
//	}
//}
//
//void LocalChat::sendMessage(std::shared_ptr<User> user_sender, std::shared_ptr<User> user_receiver, const std::string& text) {
//	auto message = std::make_shared<Message>(user_sender, text, user_receiver);
//	messages.push_back(message);
//}
//
//const std::vector<std::shared_ptr<Message>>& LocalChat::getMessages() const
//{
//	return messages;
//}

