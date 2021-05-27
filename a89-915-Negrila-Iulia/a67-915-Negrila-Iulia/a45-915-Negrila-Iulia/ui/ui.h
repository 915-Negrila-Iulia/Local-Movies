#pragma once
#include "../service/service.h"

class UI{
private:
    Service service;

public:
    UI(const Service&s): service(s){}
    void run();

private:
    static void print_menu();
    static void print_repo_menu();
    static void print_user_menu();
    static void print_current_movie_user_options();

    void add_movie_ui();
    void remove_movie_ui();
    void update_movie_ui();
    void display_movies_from_repo();

    void user_add_ui();
    void user_remove_ui();
    void display_watch_list_ui();
    void display_current_movie();
};
