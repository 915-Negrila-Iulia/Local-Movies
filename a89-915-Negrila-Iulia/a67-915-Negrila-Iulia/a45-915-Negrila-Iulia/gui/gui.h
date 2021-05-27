#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableView>

#include "../service/service.h"
#include "movies_table_model.h"

class GUI : public QWidget {
private:
    Service &service;

    //graphical elements

    QListWidget *movies_list_admin;
    QListWidget *movies_list_user;

    QTableView *movies_table_user;

    QLineEdit *title_line_admin, *genre_line_admin, *year_line_admin,
            *likes_line_admin, *link_line_admin;
    QLineEdit *title_line_user, *year_line_user, *genre_line_user;

    QPushButton *add_button_admin, *delete_button_admin, *update_button_admin;
    QPushButton *add_button_user, *delete_button_user, *next_button_user,
            *save_to_file_button_user, *open_file_button_user, *start_button_user, *stop_button_user;

    QLabel *title_label_admin, *genre_label_admin, *year_label_admin, *likes_label_admin,
            *link_label_admin, *title_label_user, *year_label_user, *genre_label_user,
            *admin_label, *user_label;

public:
    GUI(Service &s);

private:
    void init_GUI();
    void connect_signals_slots();

    void display_movies_admin();
    int get_selected_index_admin() const;
    void add_movie_admin();
    void delete_movie_admin();
    void update_movie_admin();

    void display_movies_user();
    int get_selected_index_user() const;
    void add_movie_user();
    void delete_movie_user();
    void start_parsing_movies();
    void next_movie();
    void stop_parsing_movies();
    void save_to_file();
    void open_file();

    void init_style();

    void button_style_admin(QPushButton *pButton);
    void button_style_user(QPushButton *pButton);
    void label_style(QLabel *label);
    void line_edit_style(QLineEdit *line_edit);
};