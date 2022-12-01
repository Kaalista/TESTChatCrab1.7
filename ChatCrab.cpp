#include <iostream>
#include "ChatCrab.h"
#include "string"
#include<vector>
#include<string>
#include <iostream>
#include <windows.h>


void login();
std::shared_ptr<User> Chat::get_user_by_login(const std::string& login) const
{
	for (auto& user : AllUsers_)
	{
		if (login == user.get_user_login())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::get_user_by_name(const std::string& name) const
{
	for (auto& user : AllUsers_)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

void Chat::show_login_menu()
{
	setlocale(LC_ALL, "Russian");
	currentUser_ = nullptr;
	char operation = 'a';

	do
	{
		if (language_ == '1') {
			std::cout << "\033[33m Здравствуй, хочешь войти или зарегистрироваться?" << std::endl;
			std::cout << "1 - зарегистрироваться" << std::endl;
			std::cout << "2 - войти в чат" << std::endl;
			std::cout << "0 - закрыть чат\033[37m" << std::endl << std::endl;
		}
		else {
			std::cout << "\033[33m Hello, do you want to login or register?" << std::endl;
			std::cout << "1 - Register" << std::endl;
			std::cout << "2 - Login to the chat" << std::endl;
			std::cout << "0 - Close the chat\033[37m" << std::endl << std::endl;
		}

		std::cin >> operation;

		switch (operation)
		{
		case '1':
			registration_in_the_chat();
			break;
		case '2':
			log_ln_to_the_chat();
			break;
		case '0':
			WorkChat_ = false;
			break;
		default:
			if (language_ == '1') { std::cout << "\033[33m Неизвестный выбор\033[37m" << std::endl; }
			else { std::cout << "\033[33m Unknown choice\033[37m" << std::endl; }
			break;
		}
	} while (!currentUser_ && WorkChat_);
}

void Chat::showUserMenu()
{
	char operation;

	if (language_ == '1') { std::cout << "\033[33mПривет, " << currentUser_->getUserName() << "\033[37m" << std::endl; }
	else { std::cout << "\033[33m Hi, " << currentUser_->getUserName() << "\033[37m" << std::endl; }

	while (currentUser_)
	{
		if (language_ == '1') { std::cout << "\033[33m \tменю: (1) Показать сообщения | (2) Написать сообщение | (3) Пользователи | (0) Выйти\033[37m"; }
		else { std::cout << "\033[33m \tMenu:(1) Show Messages | (2) Write a Message | (3) Users | (0) Log out\033[37m"; }

		std::cout << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			show_chat();
			break;
		case '2':
			menu_message();
			break;
		case '3':
			show_all_users_name();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			if (get_language() == '1') { std::cout << "\033[33m Неизвестный выбор, выберите действие от 1, 2, 3, 0\033[37m" << std::endl; }
			else { std::cout << "\033[33m Unknown selection, choose an action from 1, 2, 3, 0\033[37m" << std::endl; }
			break;
		}
	}
}

void Chat::registration_in_the_chat()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string login;
	std::string password;
	std::string name;

	if (language_ == '1') {
		std::cout << "\033[33mВы выбрали 1 - зарегистрироваться" << std::endl;
		std::cout << "\033[34m введите ваш логин\033[37m" << std::endl;
	}
	else {
		std::cout << "\033[33m you have chosen 1 - register" << std::endl;
		std::cout << "\033[34m enter your login\033[37m" << std::endl;
	}

	std::cin >> login;

	if (get_user_by_login(login) || login == "всем")
	{
		throw UserLoginExp();
	}

	if (language_ == '1') { std::cout << "\033[34m введите ваше имя\033[37m" << std::endl; }
	else
	{
		std::cout << "\033[34m enter your name\033[37m" << std::endl;
	}

	std::cin >> name;
	if (get_user_by_name(name) || name == "всем")
	{
		throw UserNameExp();
	}

	if (language_ == '1') { std::cout << "\033[34m Введите ваш пароль\033[37m" << std::endl; }
	else { std::cout << "\033[34m Enter your password\033[37m" << std::endl; }

	std::cin >> password;

	User user = User(login, password, name);
	AllUsers_.push_back(user);

	if (language_ == '1') {
		std::cout << "\033[33m ] Количество пользователей " << size(AllUsers_) << "\033[37m" << std::endl;
	}
	else { std::cout << "\033[33m Number of users " << size(AllUsers_) << "\033[37m" << std::endl; }

	currentUser_ = std::make_shared<User>(user);
}

void Chat::log_ln_to_the_chat()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string login, password;
	char operation;

	do
	{
		if (language_ == '1') { std::cout << "\033[34m Введите логин: \033[37m"; }
		else { std::cout << "\033[33m Enter your login: \033[37m"; }

		std::cin >> login;

		if (language_ == '1') { std::cout << "\033[34m Введите пароль: \033[37m"; }
		else { std::cout << "\033[33m Enter the password: \033[37m"; }

		std::cin >> password;

		currentUser_ = get_user_by_login(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			if (language_ == '1') {
				std::cout << "\033[33m Неверный логин или пароль!!!" << std::endl;
				std::cout << "Нажмите (0) чтобы выйти или любую клавишу для повтора: \033[37m" << std::endl;
			}
			else {
				std::cout << "\033[33m Invalid username or password!!!" << std::endl;
				std::cout << "Invalid username or password!!!Press (0) to exit or any key to repeat: \033[37m" << std::endl;
			}

			std::cin >> operation;
			currentUser_ = nullptr;
			if (operation == 0)
				break;
		}
	} while (!currentUser_);
}

void Chat::show_chat() const
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string from;
	std::string to;
	std::cout << "\033[31m\n";
	std::cout << "                                                      .$$$' $.                .$ '$$$\n";
	std::cout << "                                                      $$$. .$$                $$. .$$$.\n";
	std::cout << "                                                      $$$$$$$$                 $$$$$$$$\n";
	std::cout << "           $$                                         '$$$$$$      $     $      $$$$$$'\n";
	std::cout << "           $$                                           '$$$$   .$$0$$$$$0$$$.   $$$$'\n";
	std::cout << "           $$                 $$                          '$$..$$$$$$$$$$$$$$$$..$$'\n";
	std::cout << "           $$                 $$                      .$$.  $$$$$$$$$$$$$$$$$$$$$$' .$$.\n";
	std::cout << "  ..$$$$.  $$$$$$$.   .$$$.  $$$$$                  .$$''$$.:$$$$$$$$$$$$$$$$$$$$: $$  $$\n";
	std::cout << " $$'    '$ $$'   '$$ '    $$  $$                    $'    :$$$$$$$$$$$$$$$$$$$$$$$$'    '$\n";
	std::cout << "$$:        $$     $$ .$$$$$$  $$                    $ .$$$'  '$$$$$$$$$$$$$$$$$$'  .$$$. $\n";
	std::cout << " $$.    .$ $$     $$ $   .$$  $$                     .$' '$$$$'$$$$$$$$$$$$$$$$'$$$$' '$\n";
	std::cout << "  '$$$$$$' $$     $$ '$$$$ $$ '$$$$   2.1           $:       .$'$$$$$$$$$$$$'$.       '$\n";
	std::cout << "                                                     '$     .$$$              '$$$.     $\n";
	std::cout << "                                                            $'                   '$\n\033[37m";

	for (auto& mess : messages_)
	{
		if (currentUser_->get_user_login() == mess.getFrom() || currentUser_->get_user_login() == mess.getTo() || mess.getTo() == "всем")
		{
			if (language_ == '1') { from = (currentUser_->get_user_login() == mess.getFrom()) ? "меня" : get_user_by_login(mess.getFrom())->getUserName(); }
			else { from = (currentUser_->get_user_login() == mess.getFrom()) ? "me" : get_user_by_login(mess.getFrom())->getUserName(); }

			if (language_ == '1') {
				if (mess.getTo() == "всем") { to = "всем"; }
				else { to = (currentUser_->get_user_login() == mess.getTo()) ? "Я" : get_user_by_login(mess.getTo())->getUserName(); }
			}
			else {
				if (mess.getTo() == "всем") { to = "all"; }
				else { to = (currentUser_->get_user_login() == mess.getTo()) ? "Я" : get_user_by_login(mess.getTo())->getUserName(); }
			}

			if (language_ == '1') {
				std::cout << "\033[33m Сообщение от\033[34m " << from << " \033[37m" << to;
				std::cout << " Текст:\033[37m " << mess.getText() << std::endl;
			}
			else {
				std::cout << "\033[33mMessage from\033[34m [" << from << "]\033[37m to whom \033[37m" << to;
				std::cout << "\033[34m Text: \033[37m" << mess.getText() << std::endl;
			}
		}
	}
	std::cout << "\033[31m\n";
	std::cout << "             .$$$$$$$.             .$$$$$$$.           .$$$$$$$. " << std::endl; std::cout << "$$$..   ..$$$'       '$$$..   ..$$$'      '$$$..   ..$$$'     '$$$." << std::endl;
	std::cout << "  '$$$$$$$'             '$$$$$$$'            '$$$$$$$'           '$$$\033[37m" << std::endl << std::endl;
}

void Chat::show_all_users_name() const
{
	std::cout << "-#-#-#-#-Users-#-#-#-#-" << std::endl;
	for (auto& user : AllUsers_)
	{
		std::cout << user.getUserName();
		if (currentUser_->get_user_login() == user.get_user_login())
		{
			if (language_ == '1') { std::cout << "\033[33m(Я)\033[37m"; }
			else { std::cout << "\033[33m(me)\033[37m"; }
		}
		std::cout << std::endl;
	}
	std::cout << "-#-#-#-#-#-#-#-#-#-#" << std::endl;
}

void Chat::add_message()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	std::string to;
	std::string text;

	if (language_ == '1') { std::cout << "\033[33m Кому (Имя пользователя):\033[37m"; }
	else { std::cout << "\033[33m To (User Name):\033[37m"; }

	std::cin >> to;

	if (language_ == '1') { std::cout << "\033[33m Текст: \033[37m"; }
	else { std::cout << "\033[33m text: \033[37m"; }

	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "всем" || get_user_by_name(to)))
	{
		if (language_ == '1') { std::cout << "\033[31m Ошибка отправки сообщения! Пользователь " << to << " не найден! \033[37m" << std::endl; }
		else { std::cout << "\033[33m Error sending a message! User " << to << " not found! \033[37m" << std::endl; }
		return;
	}
	if (to == "всем")
		messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text });
	else
		messages_.push_back(Message{ currentUser_->get_user_login(), get_user_by_name(to)->get_user_login(), text });
}

void Chat::add_message(char a)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	std::string to, text;

	if (language_ == '1') { std::cout << "\033[33m Отправить всем пользователям:\033[37m"; }
	else { std::cout << "\033[33 Send to all users:\033[37m"; }

	to = "всем";

	if (language_ == '1') { std::cout << "\033[33m Текст:\033[37m "; }
	else { std::cout << "\033[33m text:\033[37m "; }

	std::cin.ignore();
	getline(std::cin, text);
	messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text });
}

void Chat::shout()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	std::string to = "всем";
	std::string text;

	if (language_ == '1') { std::cout << "\033[33m Наорать на всех пользователей:\033[37m"; }
	else { std::cout << "\033[33m Yell at all users:\033[37m"; }

	if (language_ == '1') { std::cout << "\033[33m Текст: \033[37m"; }
	else { std::cout << "\033[33m text:\033[37m "; }

	std::cin.ignore();
	getline(std::cin, text);

	for (int x = 0; x < size(text); x++) {
		if (text[x] == ' ')
			text[x] = text[x];
		else
			text[x] = toupper(text[x]);
	}
	text = "\033[31m!!!!!!!!!!!!!!!!!!!!!!" + text + "!!!!!!!!!!!!!!!!!!!!!!\033[37m";
	messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text });
}
void Chat::menu_message()
{
	char operation;

	if (language_ == '1') { std::cout << "\033[33m\tМеню: (1) Отправить сообщение кому то | (2) Написать сообщение всем | (3) Наорать на всех в чате | (0) Выйти\033[37m"; }
	else { std::cout << "\033[33m\tMenu: (1) Send a message to someone | (2) Write a message to everyone | (3) Yell at everyone in the chat | (0) Log out\033[37m"; }

	std::cout << std::endl;
	std::cin >> operation;

	switch (operation) {
	case '1':
		add_message();
		break;
	case '2':
		add_message(operation);
		break;
	case '3':
		shout();
		break;
	case'0':
		currentUser_ = nullptr;
		break;
	default:
		if (language_ == '1') { std::cout << "\033[33m Неизвестный выбор, выберите действие от 1, 2, 3, 0\033[37m" << std::endl; }
		else { std::cout << "\033[33m Unknown selection, select action from 1, 2, 3, 0\033[37m" << std::endl; }
		break;
	}
}
void Chat::CAT()
{
	std::cout << "\033[37m";
	std::cout << "____________________________________________________" << std::endl; std::cout << "                  .$$.          .$$." << std::endl; std::cout << "                  $   $.      .$   $" << std::endl;
	std::cout << "                  $    :YYYYYY:    $." << std::endl; std::cout << "                  $    .s.   .s.   '$" << std::endl; std::cout << "                  $   'іі.   .іі'  '$" << std::endl;
	std::cout << "                  $.     '$'       .$" << std::endl; std::cout << "    .$$$$$$$$.    '$.   ._$_.     .$" << std::endl; std::cout << "   $$        $.     :$$         $$:" << std::endl;
	std::cout << "   '$....,   '$    .$' .$$$$$$. '$." << std::endl; std::cout << "       $'    .$   .$' $        $  $." << std::endl; std::cout << "      .$    .$'  .$' $          $  $." << std::endl;
	std::cout << "      $'   $'  $$$$. $.        .$  $$$$." << std::endl; std::cout << "     $' .$'   $'   $ '$       .$' .$   $" << std::endl; std::cout << "    :$  $'    $.   $  $       $' $    $" << std::endl;
	std::cout << "     $. $.    '$.  '$.'$.  .$    $   .$'" << std::endl; std::cout << "      $. $      $.  '$   $ $     $   $'" << std::endl; std::cout << "       $. '$$$$$.$   $   $.$    $   $:" << std::endl;
	std::cout << "         '$$$$$'$'   $   '$'    $    $" << std::endl; std::cout << "                $$$.$'   .$.    '$.$$$" << std::endl; std::cout << "                    '$$$$' '$$$$$'" << std::endl;
	std::cout << "____________________________________________________\033[31m" << std::endl << std::endl;

	if (language_ == '1') { std::cout << "__________не_расстраивайся_пробуй_еще_раз_________" << std::endl; }
	else { std::cout << "______________Don't_worry,_try_again______________" << std::endl; }

	std::cout << "____________________________________________________\033[37m" << std::endl;
}
void Chat::NOTCAT()
{
	std::cout << "\033[37m";
	std::cout << "____________________________________________________" << std::endl << std::endl; std::cout << "           .$      $." << std::endl; std::cout << "           * '*****' *" << std::endl;
	std::cout << "          *  (O) (O) *" << std::endl; std::cout << "         **     V    **" << std::endl; std::cout << "         **          **" << std::endl; std::cout << "         **          **" << std::endl;
	std::cout << "          *.        .*" << std::endl; std::cout << "           ***''''***" << std::endl; std::cout << "____________________________________________________\033[31m" << std::endl << std::endl;

	if (language_ == '1') { std::cout << "__________не_расстраивайся_пробуй_еще_раз_________" << std::endl; }
	else { std::cout << "______________Don't_worry,_try_again______________\033[37m" << std::endl; }
}
