#pragma once
#include "user.h"
#include <memory>
class Message
{
private:
	struct PrivateMessage
	{
	private:
		const std::string userTo;
		const std::string userFrom;
		std::string message;
	public:
		PrivateMessage(const std::string& userTo, const std::string& userFrom, const std::string& message)
			: userTo(userTo), userFrom(userFrom), message(message){}
	};
	std::vector<std::unique_ptr<PrivateMessage>> messageStorage;
public:
	void sendMessage(const std::string& userTo, const std::string& userFrom, const std::string& message);
};
