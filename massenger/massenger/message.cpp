#include "message.h"

void Message::sendMessage(const std::string& userTo, const std::string& userFrom, const std::string& message)
{
	messageStorage.push_back(std::make_unique<PrivateMessage>(userTo, userFrom, message));
}
