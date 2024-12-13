#pragma once
#include <memory>

class Message
{
private:
	std::shared_ptr<User> _user_sender;
	std::shared_ptr<User> _user_reviever;
	std::string _message_text;
public:
	Message() = default;
	Message(std::shared_ptr<User> user_sender, std::string message_text, std::shared_ptr<User> user_reciever = nullptr)
	{
		_user_sender = user_sender;
		_message_text = message_text;
		_user_reviever = user_reciever;
	}

	std::shared_ptr<User> get_sender() { return _user_sender; }
	std::string get_message() { return _message_text; }
	std::shared_ptr<User> get_reciever() { return _user_reviever; }

};
