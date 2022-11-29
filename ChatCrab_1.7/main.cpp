#include <iostream>
#include "ChatCrab.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    Chat chat;
    chat.start(); // startAChat

    while (chat.isChatWork())
    {
        chat.show_login_menu();

        while (chat.getCurrentUser())
        {
            chat.showUserMenu();
        }
    }
    return 0;
}