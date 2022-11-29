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
		 // https://metanit.com/cpp/tutorial/7.2.php
	{
		if (login == user.get_user_login())//бежит по массиву проверяет 
			return std::make_shared<User>(user);//получаем указатель по логину
	}
	return nullptr;
}
std::shared_ptr<User> Chat::get_user_by_name(const std::string& name) const
{
	for (auto& user : AllUsers_)
	{
		if (name == user.getUserName())//бежит по массиву проверяет 
			return std::make_shared<User>(user);
	}
	return nullptr;
}
void Chat::show_login_menu()
{//реализовать выбор языка??
	//кодировка ввода решить проблему http://cppstudio.com/post/435/ 
	currentUser_ = nullptr;
	char operation;

	setlocale(LC_ALL, "Russian");
	do
	{
		std::cout << "здравствуй, хочешь войти или зарегистрироваться?" << std::endl;
		std::cout << "1 - зарегистрироваться" << std::endl;
		std::cout << "2 - войти в чат" << std::endl;
		std::cout << "0 - закрыть чат" << std::endl << std::endl;
		std::cin >> operation;
		//цикл
		switch (operation)
		{
		case '1'://регистрация
			try
			{
				registration_in_the_chat();
			}
			catch (UserLoginExp& a)
			{//ловит
				CAT();
				std::cout << "поймал UserLoginExp" << std::endl;
				std::cout << "UserLoginExp пользователь с таким логином уже существует" << std::endl;
				std::cout << a.what() << std::endl;//спросил что случилось 
				show_login_menu();//---------------- не знаю освобождается ли стек ??? или не возникает ли рекурсия
			}
			catch (UserNameExp& a)
			{//ловит
				CAT();
				std::cout << "поймал UserNameExp" << std::endl;
				std::cout << "UserNameExp пользователь с таким менем уже существует" << std::endl; //но можно так
				std::cout << a.what() << std::endl << std::endl;//спросил что случилось 
				show_login_menu(); //---------------- не знаю освобождается ли стек ??? или не возникает ли рекурсия
			}
			catch (std::exception& a)
			{//ловит
				CAT();
				std::cout << "поймал exception" << std::endl << std::endl;
				std::cout << a.what() << std::endl;//спросил что случилось
				show_login_menu();//---------------- не знаю освобождается ли стек ??? или не возникает ли рекурсия
			}
			catch (...)
			{//ловит все вообще

				std::cout << "что то пошло не так!!              (/)__0о__(/)" << std::endl << std::endl;
				show_login_menu();
			}
			break;
		case '2'://войти в чат
			log_ln_to_the_chat();// вход в чат-----------
			break;
		case '0'://закрыть чат
			WorkChat_ = false;
			break;
		default:
			std::cout << "Неизвестный выбор" << std::endl;
			break;
		}
	} while (!currentUser_ && WorkChat_);
}
void Chat::showUserMenu()
{
	char operation;

	std::cout << "Привет, " << currentUser_->getUserName() << std::endl;

	while (currentUser_)
	{
		std::cout << "Menu: (1) Показать сообщения | (2) Написать сообщение | (3) Пользователи | (0) Выйти";
		std::cout << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			show_chat();
			break;
		case '2':
			menu_message();//add_message();
			break;
		case '3':
			show_all_users_name();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "Неизвестный выбор, выберите действие от 1, 2, 3, 0" << std::endl;
			break;
		}
	}
}

void Chat::registration_in_the_chat()
{
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	
	std::string login;
	std::string password;//такое объявление не трогать в варианте через запятую не пашет -_-
	std::string name;
	//for (size_t i = 0; i < 2; i++)//для удобства отладки
	//{
		
		std::cout << "вы выбрали 1 - зарегистрироваться" << std::endl;
		std::cout << "введите ваш логин" << std::endl;
		std::cin >> login;

		if (get_user_by_login(login) || login == "всем")
		{
			throw UserLoginExp();
		}
		std::cout << "введите ваш имя" << std::endl;
		std::cin >> name;
		if (get_user_by_name(name) || name == "всем")
		{
			throw UserNameExp();
		}
		std::cout << "введите ваш пороль" << std::endl;
		std::cin >> password;

		User user = User(login, password, name);
		AllUsers_.push_back(user);//добоаление в список юзеров vector<User> AllUsers_
		std::cout << "size(AllUsers_) количество пользователей " << size(AllUsers_) << std::endl;
		currentUser_ = std::make_shared<User>(user);
	//}
}
void Chat::log_ln_to_the_chat()
{
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	std::string login, password;
	char operation;

	do
	{
		std::cout << "Введите логин: ";
		std::cin >> login;
		std::cout << "Введите пароль: ";
		std::cin >> password;

		currentUser_ = get_user_by_login(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			std::cout << "Неверный логин или пороль!!!" << std::endl;
			std::cout << "Нажмите (0) чтобы выйти или любую клавишу для повтора: " << std::endl;
			std::cin >> operation;
			currentUser_ = nullptr;//исправление ошибки входа  по не правельному поролю (ошибка взлома)
			if (operation == 0)
				break;
		}
	} while (!currentUser_);
}
void Chat::show_chat() const
{
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	std::string from;
	std::string to;
	std::cout << "-#-#-#-#-#-#-#-#-#-#-#-#-#-#-Чат-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << std::endl;

	for (auto& mess : messages_)
	{
		if (currentUser_->get_user_login() == mess.getFrom() || currentUser_->get_user_login() == mess.getTo() || mess.getTo() == "всем")
		{
			from = (currentUser_->get_user_login() == mess.getFrom()) ? "Я" : get_user_by_login(mess.getFrom())->getUserName();

			if (mess.getTo() == "всем")
			{
				to = "всем";
			}
			else
			{
				to = (currentUser_->get_user_login() == mess.getTo()) ? "Я" : get_user_by_login(mess.getTo())->getUserName();
			}
			std::cout << "Сообщение от " << from << " кому " << to << std::endl;
			std::cout << "Текст: " << mess.getText() << std::endl;
		}
	}
	std::cout << "-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#" << std::endl;
	//вывод чата с заменой имени текущего пользователя на (me)
	//  и проверкой что доступно текущему юзеру std::vector<Message> messages_; проверка на аll
	//проверка личных сообщениий вывод в std::vector<Message> messages_; по const std::string _to;

	
	//покозать всех пользователей вывести vector<User> AllUsers_ рядом со своим именем (me) void show_all_users_name() const;
	//отправить сообщение кому-то сослаться void add_message();
	//отправить сообщение всем сослаться
	//выход 
}
void Chat::show_all_users_name() const
{//покозать всех пользователей
	std::cout << "-#-#-#-#-Users-#-#-#-#-" << std::endl;
	for (auto& user : AllUsers_)
	{
		std::cout << user.getUserName();
		if (currentUser_->get_user_login() == user.get_user_login())
			std::cout << "(Я)";

		std::cout << std::endl;
	}
	std::cout << "-#-#-#-#-#-#-#-#-#-#" << std::endl;
	// получить имя текущего пользователя
	//вывод vector<User> AllUsers_ только миена
	//если имя текущего пользователя совпадает с именем из списка радом написать (me)
}
void Chat::add_message()
{
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	setlocale(LC_ALL, "Russian");
	std::string to, text;

	std::cout << "Кому (Имя пользователя):";
	std::cin >> to;
	std::cout << "Текст: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "всем" || get_user_by_name(to)))
	{
		std::cout << "Ошибка отправки сообщения! Пользователь " << to << " не найден!" << std::endl;
		return;
	}
	if (to == "всем")

		messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text });
	else
		messages_.push_back(Message{ currentUser_->get_user_login(), get_user_by_name(to)->get_user_login(), text });
}
void Chat::CAT()
{
	std::cout << "____________________________________________________" << std::endl;std::cout << "___________________$$____________$$" << std::endl;
	std::cout << "__________________$___$________$___$" << std::endl;std::cout << "__________________$_____$$$$$$_____$" << std::endl;
	std::cout << "__________________$____sss___sss____$" << std::endl;std::cout << "__________________$____іі_____іі_____$" << std::endl;
	std::cout << "_________________$_______$$$________$" << std::endl;std::cout << "_____$$$$$$$$_____$_______$________$" << std::endl;
	std::cout << "___$$________$_______$$_________$$" << std::endl;std::cout << "____$_________$_____$___$$$$$$___$" << std::endl;
	std::cout << "_______$______$____$__$________$__$" << std::endl;std::cout << "_______$_____$____$__$__________$__$" << std::endl;
	std::cout << "______$____$___$$$$__$__________$__$$$$" << std::endl;std::cout << "_____$___$____$____$__$________$___$___$" << std::endl;
	std::cout << "_____$__$_____$____$__$________$__$____$" << std::endl;std::cout << "____$___$______$____$__$____$_$__$____$" << std::endl; 
	std::cout << "______$__$______$____$___$_$_____$___$" << std::endl;std::cout << "_______$___$$$$$_$___$___$_$____$___$" << std::endl;
	std::cout << "__________$$$$$_$____$____$_____$____$" << std::endl;std::cout << "________________$$$_$_____$______$_$$$" << std::endl;
	std::cout << "_____________________$$$$___$$$$$" << std::endl;std::cout << "____________________________________________________" << std::endl << std::endl;
	std::cout << "__________не_расстаивайся_пробуй_еще_раз_________" << std::endl;std::cout << "____________________________________________________" << std::endl;
}
void Chat::add_message(char a)
{
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	setlocale(LC_ALL, "Russian");
	std::string to, text;

	std::cout << "отправить всем пользователям:";
	to = "всем";
	std::cout << "Текст: ";
	std::cin.ignore();
	getline(std::cin, text);
	messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text });
}
void Chat::shout() {
	SetConsoleCP(1251);// задаем кодировку для вывода символов на экран
	SetConsoleOutputCP(1251); //задаем кодировку для ввода символов с клавиатуры в консоль
	setlocale(LC_ALL, "Russian");
	std::string to;
	std::string text;

	std::cout << "Наорать на всех пользователей:";
	to = "всем";
	std::cout << "Текст: ";
	std::cin.ignore();
	getline(std::cin, text);
	int i = size(text);

	for (int x = 0; x < i; x++) {

		if (text[x] == ' ')
			text[x] = text[x];
		else
		text[x] = toupper(text[x]);//преобразование в верхний регистр
		
	}
	text = "!!!!!!!!!!!!!!!!!!!!!!" + text + "!!!!!!!!!!!!!!!!!!!!!!";//конкатенация строк
	messages_.push_back(Message{ currentUser_->get_user_login(), "всем", text }); 
}
void Chat::menu_message(){

char operation;

std::cout << "Menu: (1) Отправить сообщение кому то | (2) Написать сообщение всем | (3) Наорать на всех в чате | (0) Выйти";
std::cout << std::endl;
std::cin >> operation;

switch (operation)
{
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
	std::cout << "Неизвестный выбор, выберите действие от 1, 2, 3, 0" << std::endl;
	break;
}
}
