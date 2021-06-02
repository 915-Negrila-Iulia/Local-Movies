#include "gui.h"
#include "../repository/repository_exceptions.h"
#include <qlayout.h>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <string>
#include <QMessageBox>
#include <QStandardItem>
#include "movies_table_model.h"
#include "../user_data/html_watch_list.h"
#include <QHeaderView>

GUI::GUI(Service &s) : service{s} {
    this->init_GUI();
    this->init_style();
    this->display_movies_admin();
    this->display_movies_user();
    this->connect_signals_slots();
    this->stop_parsing_movies();
}

void GUI::init_GUI() {
    this->movies_list_admin = new QListWidget{};
    this->movies_list_user = new QListWidget{};

    this->movies_table_user = new QTableView{};

    this->model = new MoviesTableModel(this->service.get_watch_list());
    this->movies_table_user->setModel(this->model);


    this->title_line_admin = new QLineEdit{};
    this->genre_line_admin = new QLineEdit{};
    this->year_line_admin = new QLineEdit{};
    this->likes_line_admin = new QLineEdit{};
    this->link_line_admin = new QLineEdit{};

    this->title_line_user = new QLineEdit{};
    this->year_line_user = new QLineEdit{};
    this->genre_line_user = new QLineEdit{};

    this->add_button_admin = new QPushButton{"Add"};
    this->delete_button_admin = new QPushButton{"Delete"};
    this->update_button_admin = new QPushButton{"Update"};

    this->add_button_user = new QPushButton{"Add"};
    this->delete_button_user = new QPushButton{"Delete"};
    this->next_button_user = new QPushButton{"Next"};
    this->save_to_file_button_user = new QPushButton{"Save to file"};
    this->open_file_button_user = new QPushButton{"Open file"};
    this->start_button_user = new QPushButton{"Start"};
    this->stop_button_user = new QPushButton{"Stop"};

    this->admin_label = new QLabel{"Admin"};
    this->user_label = new QLabel{"User"};

    QHBoxLayout *main_layout = new QHBoxLayout{this};
    QVBoxLayout *admin_layout = new QVBoxLayout{};
    QVBoxLayout *user_layout = new QVBoxLayout{};

    main_layout->addLayout(admin_layout);
    main_layout->addLayout(user_layout);

    admin_layout->addWidget(this->admin_label);
    admin_layout->addWidget(this->movies_list_admin);

    user_layout->addWidget(this->user_label);
    //user_layout->addWidget(this->movies_list_user);
    user_layout->addWidget(this->movies_table_user);
    this->movies_table_user->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFormLayout *admin_movies_details = new QFormLayout{};

    this->title_label_admin = new QLabel{"Title"};
    this->genre_label_admin = new QLabel{"Genre"};
    this->year_label_admin = new QLabel{"Year of release"};
    this->likes_label_admin = new QLabel{"Likes"};
    this->link_label_admin = new QLabel{"Link"};

    admin_movies_details->addRow(this->title_label_admin, this->title_line_admin);
    admin_movies_details->addRow(this->genre_label_admin, this->genre_line_admin);
    admin_movies_details->addRow(this->year_label_admin, this->year_line_admin);
    admin_movies_details->addRow(this->likes_label_admin, this->likes_line_admin);
    admin_movies_details->addRow(this->link_label_admin, this->link_line_admin);

    admin_layout->addLayout(admin_movies_details);

    QFormLayout *user_movies_details = new QFormLayout{};
    this->title_line_user->setReadOnly(true);
    this->year_line_user->setReadOnly(true);
    this->title_label_user = new QLabel{"Title"};
    this->year_label_user = new QLabel{"Year of release"};
    user_movies_details->addRow(this->title_label_user, this->title_line_user);
    user_movies_details->addRow(this->year_label_user, this->year_line_user);

    user_layout->addLayout(user_movies_details);

    QVBoxLayout *show_movies_layout = new QVBoxLayout{};

    QFormLayout *genre_details = new QFormLayout{};
    this->genre_label_user = new QLabel{"Give genre"};
    genre_details->addRow(this->genre_label_user, this->genre_line_user);
    this->genre_line_user->setText("-");
    show_movies_layout->addLayout(genre_details);

    QHBoxLayout *parse_movies_buttons = new QHBoxLayout{};
    parse_movies_buttons->addWidget(this->start_button_user);
    parse_movies_buttons->addWidget(this->next_button_user);
    parse_movies_buttons->addWidget(this->stop_button_user);
    show_movies_layout->addLayout(parse_movies_buttons);

    user_layout->addLayout(show_movies_layout);

    QGridLayout *admin_buttons = new QGridLayout{};
    admin_buttons->addWidget(this->add_button_admin, 0, 0);
    admin_buttons->addWidget(this->delete_button_admin, 0, 1);
    admin_buttons->addWidget(this->update_button_admin, 0, 2);

    admin_layout->addLayout(admin_buttons);

    QGridLayout *user_buttons = new QGridLayout{};
    user_buttons->addWidget(add_button_user, 0, 0);
    user_buttons->addWidget(delete_button_user, 0, 1);
    user_buttons->addWidget(save_to_file_button_user, 1, 0);
    user_buttons->addWidget(open_file_button_user, 1, 1);

    user_layout->addLayout(user_buttons);
}

void GUI::display_movies_admin() {
    this->movies_list_admin->clear();

    for (auto &&m: this->service.get_movies_in_repo())
        this->movies_list_admin->addItem(
                QString::fromStdString(m.get_title() + " " + std::to_string(m.get_year_of_release())));
}

void GUI::connect_signals_slots() {

    //using a lambda function
    QObject::connect(this->movies_list_admin, &QListWidget::itemSelectionChanged, [this]() {
        int selected_index = this->get_selected_index_admin();

        if (selected_index < 0) {
            return;
        }

        Movie m = this->service.get_movies_in_repo()[selected_index];
        this->title_line_admin->setText(QString::fromStdString(m.get_title()));
        this->genre_line_admin->setText(QString::fromStdString(m.get_genre()));
        this->year_line_admin->setText(QString::fromStdString(std::to_string(m.get_year_of_release())));
        this->likes_line_admin->setText(QString::fromStdString(std::to_string(m.get_number_of_likes())));
        this->link_line_admin->setText(QString::fromStdString(m.get_trailer()));
    });

    //call function 'add_movie_admin' when the signal 'clicked' is emitted by button 'add_button_admin'
    //'this' is the object which contains the function 'add_movie_admin'
    QObject::connect(this->add_button_admin, &QPushButton::clicked, this, &GUI::add_movie_admin);

    QObject::connect(this->delete_button_admin, &QPushButton::clicked, this, &GUI::delete_movie_admin);

    QObject::connect(this->update_button_admin, &QPushButton::clicked, this, &GUI::update_movie_admin);

    QObject::connect(this->movies_table_user, &QTableView::clicked, [this]() {
        int selected_index = this->get_selected_index_user();

        if (selected_index < 0) {
            return;
        }

        Movie m = this->service.get_movies_in_watch_list()[selected_index];
        this->title_line_user->setText(QString::fromStdString(m.get_title()));
        this->year_line_user->setText(QString::fromStdString(std::to_string(m.get_year_of_release())));
    });

    QObject::connect(this->start_button_user, &QPushButton::clicked, this, &GUI::start_parsing_movies);
    QObject::connect(this->next_button_user, &QPushButton::clicked, this, &GUI::next_movie);
    QObject::connect(this->stop_button_user, &QPushButton::clicked, this, &GUI::stop_parsing_movies);

    QObject::connect(this->add_button_user, &QPushButton::clicked, this, &GUI::add_movie_user);

    QObject::connect(this->delete_button_user, &QPushButton::clicked, this, &GUI::delete_movie_user);

    QObject::connect(this->save_to_file_button_user, &QPushButton::clicked, this, &GUI::save_to_file);
    QObject::connect(this->open_file_button_user, &QPushButton::clicked, this, &GUI::open_file);

}

int GUI::get_selected_index_admin() const {

    QModelIndexList selected_indexes = this->movies_list_admin->selectionModel()->selectedIndexes();

    if (selected_indexes.size() == 0) {
        this->title_line_admin->clear();
        this->genre_line_admin->clear();
        this->year_line_admin->clear();
        this->likes_line_admin->clear();
        this->link_line_admin->clear();
        return -1;
    }

    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

void GUI::add_movie_admin() {
    std::string title = this->title_line_admin->text().toStdString();
    std::string genre = this->genre_line_admin->text().toStdString();
    int year = this->year_line_admin->text().toInt();
    int likes = this->likes_line_admin->text().toInt();
    std::string link = this->link_line_admin->text().toStdString();

    try {
        this->service.add_movie_to_repo(title, genre, year, likes, link);
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors()) {
            //convert std::string to char*
            char *c_error = const_cast<char *>(error.c_str());
            QMessageBox::critical(this, "Error", c_error);
        }
    }
    catch (RepositoryException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (FileException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    this->display_movies_admin();

    int last_movie = this->service.get_movies_in_repo().size() - 1;
    this->movies_list_admin->setCurrentRow(last_movie);
}

void GUI::delete_movie_admin() {
    int selected_index = this->get_selected_index_admin();
    if (selected_index < 0) {
        //'this' is the parent of the message box
        QMessageBox::critical(this, "Error", "No movie was selected");
        return;
    }

    Movie m = this->service.get_movies_in_repo()[selected_index];
    try {
        this->service.remove_movie_from_repo(m.get_title(), m.get_year_of_release());
    }
    catch (RepositoryException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (FileException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    this->display_movies_admin();
}

void GUI::update_movie_admin() {

    int selected_index = this->get_selected_index_admin();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "No movie was selected");
        return;
    }

    Movie m = this->service.get_movies_in_repo()[get_selected_index_admin()];

    std::string title = this->title_line_admin->text().toStdString();
    std::string genre = this->genre_line_admin->text().toStdString();
    int year = this->year_line_admin->text().toInt();
    int likes = this->likes_line_admin->text().toInt();
    std::string link = this->link_line_admin->text().toStdString();

    if (m.get_title() != title) {
        QMessageBox::critical(this, "Error", "Can't change title");
        return;
    }

    if (m.get_year_of_release() != year) {
        QMessageBox::critical(this, "Error", "Can't change year of release");
        return;
    }

    try {
        this->service.update_movie_from_repo(title, year, genre, likes, link);
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors()) {
            char *c_error = const_cast<char *>(error.c_str());
            QMessageBox::critical(this, "Error", c_error);
        }
    }
    catch (RepositoryException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (FileException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    this->display_movies_admin();
}

void GUI::display_movies_user() {
    this->movies_list_user->clear();

    for (auto &&m: this->service.get_movies_in_watch_list())
        this->movies_list_user->addItem(
                QString::fromStdString(m.get_title() + " " + std::to_string(m.get_year_of_release())));

}

int GUI::get_selected_index_user() const {

    auto selected_indexes = this->movies_table_user->selectionModel()->selectedIndexes();

    if (selected_indexes.size() == 0) {
        this->title_line_user->clear();
        this->year_line_user->clear();
        return -1;
    }

    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

void GUI::add_movie_user() {

    std::string title = this->title_line_user->text().toStdString();
    int year = this->year_line_user->text().toInt();

    Movie m = this->service.get_repository().find_movie(title, year);
    if (m == NullValue) {
        QMessageBox::critical(this, "Error", "This movie is not available");
        return;
    }

    try {
        this->service.add_movie_to_watch_list(m);
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors()) {
            char *c_error = const_cast<char *>(error.c_str());
            QMessageBox::critical(this, "Error", c_error);
        }
    }
    catch (RepositoryException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    this->display_movies_user();
    this->model = new MoviesTableModel(this->service.get_watch_list());
    this->movies_table_user->setModel(this->model);

    int last_movie = this->service.get_movies_in_watch_list().size() - 1;
    this->movies_list_user->setCurrentRow(last_movie);
}

void GUI::delete_movie_user() {

    int selected_index = this->get_selected_index_user();
    if (selected_index < 0) {
        //'this' is the parent of the message box
        QMessageBox::critical(this, "Error", "No movie was selected");
        return;
    }

    Movie m = this->service.get_movies_in_watch_list()[selected_index];
    try {
        this->service.remove_movie_from_watch_list(m);
    }
    catch (RepositoryException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (FileException &e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    QMessageBox::StandardButton rate_movie = QMessageBox::question(
            this, "feedback", "Did you like this movie?", QMessageBox::Yes | QMessageBox::No);

    if (rate_movie == QMessageBox::Yes)
        this->service.update_movie_from_repo(m.get_title(), m.get_year_of_release(), m.get_genre(),
                                             m.get_number_of_likes() + 1, m.get_trailer());

    this->display_movies_user();
    this->model = new MoviesTableModel(this->service.get_watch_list());
    this->movies_table_user->setModel(this->model);

}

void GUI::start_parsing_movies() {

    this->next_button_user->setEnabled(true);
    this->add_button_user->setEnabled(true);
    this->delete_button_user->setEnabled(false);
    this->save_to_file_button_user->setEnabled(false);
    this->open_file_button_user->setEnabled(false);

    std::string genre = this->genre_line_user->text().toStdString();
    this->service.first_movie(genre);
    Movie m = this->service.get_repository().get_current();
    m.play();

    this->title_line_user->setText(QString::fromStdString(m.get_title()));
    this->year_line_user->setText(QString::fromStdString(std::to_string(m.get_year_of_release())));

}

void GUI::next_movie() {

    std::string genre = this->genre_line_user->text().toStdString();
    this->service.next_movie(genre);
    Movie m = this->service.get_repository().get_current();
    m.play();

    this->title_line_user->setText(QString::fromStdString(m.get_title()));
    this->year_line_user->setText(QString::fromStdString(std::to_string(m.get_year_of_release())));

}

void GUI::stop_parsing_movies() {

    this->next_button_user->setEnabled(false);
    this->add_button_user->setEnabled(false);
    this->delete_button_user->setEnabled(true);
    this->save_to_file_button_user->setEnabled(true);
    this->open_file_button_user->setEnabled(true);

}

void GUI::save_to_file() {
    this->service.save_watch_list(
            R"(C:\Users\user1\Documents\GitHub\a89-915-Negrila-Iulia\a67-915-Negrila-Iulia\a45-915-Negrila-Iulia\watch_list)");
}

void GUI::open_file() {
    this->service.open_watch_list();
}

void GUI::init_style(){
    auto palette = this->palette();
    palette.setColor(QPalette::Window, QColor(232, 220, 255));
    this->setPalette(palette);

    label_style(this->admin_label);
    label_style(this->user_label);

    button_style_admin(add_button_admin);
    button_style_admin(delete_button_admin);
    button_style_admin(update_button_admin);

    button_style_user(add_button_user);
    button_style_user(delete_button_user);
    button_style_user(save_to_file_button_user);
    button_style_user(open_file_button_user);
    button_style_user(start_button_user);
    button_style_user(stop_button_user);
    button_style_user(next_button_user);

    label_style(title_label_admin);
    label_style(genre_label_admin);
    label_style(year_label_admin);
    label_style(likes_label_admin);
    label_style(link_label_admin);

    label_style(title_label_user);
    label_style(year_label_user);
    label_style(genre_label_user);

    line_edit_style(title_line_admin);
    line_edit_style(genre_line_admin);
    line_edit_style(year_line_admin);
    line_edit_style(likes_line_admin);
    line_edit_style(link_line_admin);

    line_edit_style(title_line_user);
    line_edit_style(year_line_user);
    line_edit_style(genre_line_user);

    movies_list_admin->setStyleSheet("font: 9pt \"MS Shell Dlg 2\";\n"
                                     "border: 5px solid rgba(255, 119, 119, 255);\n"
                                     "border-radius: 10px;");
    movies_list_user->setStyleSheet("font: 9pt \"MS Shell Dlg 2\";\n"
                                    "border: 5px solid rgba(147, 151, 255, 255);\n"
                                    "border-radius: 10px;");
    movies_table_user->setStyleSheet("font: 9pt \"MS Shell Dlg 2\";\n"
                                     "border: 5px solid rgba(147, 151, 255, 255);\n"
                                     "border-radius: 10px;\n");
    this->movies_table_user->horizontalHeader()->setStyleSheet("border: none;");
    this->movies_table_user->verticalHeader()->setStyleSheet("border: none;");

}

void GUI::button_style_admin(QPushButton *button) {
    button->setStyleSheet("background-color: rgba(255, 119, 119, 255);\n"
                         "border-style: outset;\n"
                         "border-radius: 5px;\n"
                         "border-color: rgba(144, 83, 113, 255);\n"
                         "border-width: 2px;\n"
                         "font: kerning 8px;\n"
                         "min-width: 5em;\n"
                         "padding: 5px;");
}

void GUI::button_style_user(QPushButton *button) {
    button->setStyleSheet("background-color: rgba(147, 151, 255, 255);\n"
                          "border-style: outset;\n"
                          "border-radius: 5px;\n"
                          "border-color: rgba(144, 83, 113, 255);\n"
                          "border-width: 2px;\n"
                          "font: kerning 8px;\n"
                          "min-width: 5em;\n"
                          "padding: 5px;");
}

void GUI::label_style(QLabel *label){
    label->setStyleSheet("font: 9pt \"MS Shell Dlg 2\";\n"
                         "color: rgba(144, 83, 113, 255);\n"
                         "font-weight: bold;");
}

void GUI::line_edit_style(QLineEdit *line_edit){

    line_edit->setStyleSheet("font: 9pt \"MS Shell Dlg 2\";\n");
}