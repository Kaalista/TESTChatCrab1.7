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
	char language_ = 'a';
	bool WorkChat_ = false;
	std::vector<User> AllUsers_;
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_ = nullptr;

	void registration_in_the_chat();
	void log_ln_to_the_chat();

	void show_chat() const;

	void show_all_users_name() const;

	void add_message();
	void add_message(char a);
	void shout();
	std::vector<User>& get_all_users() { return AllUsers_; }
	std::vector<Message>& get_all_messages() { return messages_; }
	std::shared_ptr<User> get_user_by_login(const std::string& login) const;
	std::shared_ptr<User> get_user_by_name(const std::string& name) const;
public:
	void start() { WorkChat_ = true; }
	bool isChatWork() const { return WorkChat_; }
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void show_login_menu();
	void showUserMenu();
	void CAT();
	void NOTCAT();
	void menu_message();
	void set_language(char language) { language_ = language; };
	char get_language() { return language_; };
};
