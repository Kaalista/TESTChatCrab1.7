#pragma once
#include<vector>
#include<exception>
#include<memory>
#include"Message.h"

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: login is busy"; }

};
struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: Name is busy"; }
};

class Chat
{
	bool WorkChat_ = false; //WorkChat_ isChatWork_
	std::vector<User> AllUsers_;// users_ AllUsers_
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_ = nullptr; //текущий пользователь

	void registration_in_the_chat();//регестрация в чате
	void log_ln_to_the_chat();// вход в чат

	void show_chat() const;//показать чат

	void show_all_users_name() const;// показать всех пользователей

	void add_message();//добавить сообщение
	void add_message(char a);
	void shout();
	std::vector<User>& get_all_users() { return AllUsers_; }//получить список пользователей
	std::vector<Message>& get_all_messages() { return messages_; }// получить все сообщения
	std::shared_ptr<User> get_user_by_login(const std::string& login) const;//getAUserLogin
	std::shared_ptr<User> get_user_by_name(const std::string& name) const;//getAUserName
public:
	void start() { WorkChat_ = true; }
	bool isChatWork() const { return WorkChat_; }
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void show_login_menu();
	void showUserMenu();
	void CAT();
	void menu_message();
	
};
