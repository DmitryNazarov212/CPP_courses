#include <iostream>  
#include <fstream>  
#include <string>  
#include <sys/stat.h>  

using namespace std;
class User {  
private:  
    string _name;  
    string _login;  
    string _pass;  

public: 
    User() = default;
    User(string name, string login, string pass): _name(name), _login(login), _pass(pass) {}; 

    friend ostream& operator<<(ostream &os, const User &user);
    friend fstream& operator >>(fstream& is, User& user);


    void saveToFile(const string &filename, User& obj) const {  
        ofstream ofs(filename);  
        ofs << obj;
        ofs.close();  
        chmod(filename.c_str(), S_IRUSR | S_IWUSR);  
    }  

    void loadFromFile(const string &filename, User& obj) {  
        fstream user_file = fstream(filename);  
        if (user_file) {  
            user_file >> obj;
            cout << obj << endl;
        } else {  
            cout << "Не удалось открыть файл: " << filename << endl;  
        }  
    }  
};  

class Message {  
private:  
    string _text;  
    string _sender;  
    string _receiver;  

public: 
    Message() = default; 
    Message(string text, string sender, string receiver): _text(text), _sender(sender), _receiver(receiver) {};
    
    friend ostream& operator<<(ostream &os, const Message &msg); 
    friend fstream& operator>>(fstream &is, Message &msg);

    void saveToFile(const string &filename, Message& obj) const {  
        ofstream ofs(filename);  
        ofs << obj;
        ofs.close();  
        chmod(filename.c_str(), S_IRUSR | S_IWUSR);  
    }  

    void loadFromFile(const string &filename, Message& obj) {  
         fstream user_file = fstream(filename);  
        if (user_file) {  
            user_file >> obj;
            cout << obj << endl;
        } else {  
             cout << "Не удалось открыть файл: " << filename << endl; 
        }  
    }  
}; 

ostream& operator<<(ostream &os, const User &obj) {  
    os << obj._name << endl;  
    os << obj._login << endl;  
    os << obj._pass << endl;  
    return os;  
}  
fstream& operator >>(fstream& is, User& obj)
{
    is >> obj._name;
    is >> obj._login;
    is >> obj._pass;
    return is;
}

ostream& operator<<(ostream &os, const Message &obj) {  
    os << obj._text << endl;  
    os << obj._sender << endl;  
    os << obj._receiver << endl;  
    return os;  
}  
fstream& operator>>(fstream& is, Message& obj)
{
    is >> obj._text;
    is >> obj._sender;
    is >> obj._receiver;
    return is;
}

int main() {  
    User user("Alice", "alice123", "securepassword");  
    user.saveToFile("user_data.txt", user);  
  
    User loadedUser;  
    loadedUser.loadFromFile("user_data.txt", loadedUser);  
 
    
    Message msg ("Hello, Bob!", "Alice", "Bob");  
    msg.saveToFile("message_data.txt", msg);  

    Message loadedMsg;  
    loadedMsg.loadFromFile("message_data.txt", loadedMsg);  

    return 0;  
}