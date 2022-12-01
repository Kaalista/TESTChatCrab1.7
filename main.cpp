#include <iostream>
#include "ChatCrab.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Chat chat;
	char language;

	do
	{
		std::cout << "\033[33m\t Выберите язык/Select a language" << std::endl;
		std::cout << "1 - Русский" << std::endl;
		std::cout << "2 - English\033[37m" << std::endl;
		std::cin >> language;
		std::cout << std::endl;
		switch (language)
		{
		case '1':
			std::cout << "\033[33m \t Вы выбрали (1) - Русский\033[37m" << std::endl;
			chat.set_language(language);
			break;
		case '2':
			std::cout << "\033[33m\t You have chosen (2) - English\033[37m" << std::endl;
			chat.set_language(language);
			break;
		default:
			std::cout << "\033[33m\t Неизвестный выбор\033[37m" << std::endl;
			break;
		}
	} while (language != '1' && language != '2');

	chat.start();

	while (chat.isChatWork())
	{
		try
		{
			chat.show_login_menu();
		}
		catch (UserLoginExp& a) {
			if (chat.get_language() == '1') { chat.CAT(); std::cout << "\033[31m UserLoginExp пользователь с таким логином уже существует\033[37m" << std::endl; }
			else { chat.CAT(); std::cout << a.what() << std::endl; }
		}
		catch (UserNameExp& a) {
			if (chat.get_language() == '1') { chat.NOTCAT(); std::cout << "\033[31m UserLoginExp пользователь с таким именем уже существует\033[37m" << std::endl; }
			else { chat.CAT(); std::cout << a.what() << std::endl; }
		}
		catch (std::exception& a) {
			if (chat.get_language() == '1') { chat.CAT(); std::cout << "Ошибка" << std::endl; std::cout << a.what() << std::endl; }
			else { chat.CAT(); std::cout << a.what() << std::endl; }
		}
		catch (...) {
			if (chat.get_language() == '1') { std::cout << "\033[31m что то пошло не так!!    (/)__0о__(/)\033[33m" << std::endl << std::endl; }
			else { std::cout << "\033[31m something went wrong!!    (/)__0о__(/)\033[37m" << std::endl << std::endl; }
		}
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	return 0;
}
