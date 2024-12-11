#include "chat.h"
using namespace std;

int main()
{
	Chat* main = new Chat;
	char login1[] = "maks";
	char pass1[] = "qwerty";
	char login2[] = "admin";
	char pass2[] = "213asfSAF";
	char login3[] = "Satyr";

	main->getUsers();

	main->reg(login1, pass1, strlen(pass1));
	main->reg(login2, pass2, strlen(pass2));

	cout << "Authentification check for user \"" << login1 << "\" completed with result: " << main->login(login1, pass1, strlen(pass1)) << endl;
	cout << "Authentification check for user \"" << login2 << "\" completed with result: " << main->login(login2, pass2, strlen(pass2)) << endl;

	main->getUsers();
	main->delUser(login1);
	main->getUsers();
	cout << "Authentification check for user \"" << login1 << "\" completed with result: " << main->login(login1, pass1, strlen(pass1)) << endl;
	main->delUser(login3);

	delete main;
	return 0;
}
