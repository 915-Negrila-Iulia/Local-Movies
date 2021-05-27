#include "ui.h"
#include <iostream>
#include <string>
#include <crtdbg.h>
#include "../repository/repository_exceptions.h"
#include <algorithm>
#include <limits>

using namespace std;

void UI::print_menu() {
    cout << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Administrator mode" << endl;
    cout << "2 - User mode" << endl;
    cout << endl;
}

void UI::print_repo_menu() {
    cout << endl;
    cout << "Choose option:" << endl;
    cout << "0 - Back" << endl;
    cout << "1 - Add movie" << endl;
    cout << "2 - Remove movie" << endl;
    cout << "3 - Update movie" << endl;
    cout << "4 - Display movies" << endl;
    cout << endl;
}

void UI::print_user_menu() {
    cout << endl;
    cout << "Choose option: " << endl;
    cout << "0 - Back" << endl;
    cout << "1 - See movies in the database" << endl;
    cout << "2 - See all the movies saved in your watch list" << endl;
    cout << "3 - Remove movie from the watch list" << endl;
    cout << "4 - Save watch list to file" << endl;
    cout << "5 - Open file containing the watch list" << endl;
    cout << endl;
}

void UI::print_current_movie_user_options() {
    cout << endl;
    cout << "Choose option: " << endl;
    cout << "0 - Back" << endl;
    cout << "1 - Add movie to watch list" << endl;
    cout << "2 - Go to the next movie" << endl;
    cout << endl;
}

void read_valid_int(int &a) {
    cin.exceptions(std::ios_base::failbit);
    bool validInput;
    do {
        try {
            validInput = true;
            cin >> a;
        }
        catch (std::ios_base::failure &fail) {
            validInput = false;
            // Cleanup the stream state
            cin.clear();
            std::string dummy;
            cin >> dummy; // Consume the invalid input
            cout << "Please input a number." << std::endl;
        }
    } while (!validInput);
    cin.ignore();
}

void UI::add_movie_ui() {
    int year_of_release, number_of_likes;

    cout << "Give title: ";
    std::string title;
    getline(cin, title);

    cout << "Give genre: ";
    std::string genre;
    getline(cin, genre);

    cout << "Give year of release: ";
//    cin>>year_of_release;
//    cin.ignore();
    read_valid_int(year_of_release);

    cout << "Give number of likes: ";
//    cin >> number_of_likes;
//    cin.ignore();
    read_valid_int(number_of_likes);

    cout << "Give link to trailer: ";
    std::string trailer;
    getline(cin, trailer);

    try {
        this->service.add_movie_to_repo(title, genre, year_of_release, number_of_likes, trailer);
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors())
            cout << error << endl;
    }
    catch (RepositoryException &e) {
        cout << e.what() << endl;
    }
    catch (FileException &e) {
        cout << e.what() << endl;
    }
}

void UI::remove_movie_ui() {
    int year_of_release;

    cout << "Give title: ";
    std::string title;
    getline(cin, title);

    cout << "Give year of release: ";
//    cin >> year_of_release;
//    cin.ignore();
    read_valid_int(year_of_release);

    try {
        this->service.remove_movie_from_repo(title, year_of_release);
    }
    catch (RepositoryException &e) {
        cout << e.what() << endl;
    }
    catch (FileException &e) {
        cout << e.what() << endl;
    }
}

void UI::update_movie_ui() {
    cout << "Give title: ";
    std::string title;
    getline(cin, title);

    cout << "Give year of release: ";
    int year_of_release;
//    cin >> year_of_release;
//    cin.ignore();
    read_valid_int(year_of_release);

    this->service.get_repository().find_movie(title, year_of_release);

    cout << "Give new genre: ";
    std::string new_genre;
    getline(cin, new_genre);

    cout << "Give new number of likes: ";
    int new_number_of_likes;
//    cin >> new_number_of_likes;
//    cin.ignore();
    read_valid_int(new_number_of_likes);

    cout << "Give new link to trailer: ";
    std::string new_trailer;
    getline(cin, new_trailer);

    try {
        this->service.update_movie_from_repo(title, year_of_release, new_genre, new_number_of_likes, new_trailer);
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors())
            cout << error << endl;
    }
    catch (RepositoryException &e) {
        cout << e.what() << endl;
    }
    catch (FileException &e) {
        cout << e.what() << endl;
    }
}

void UI::display_movies_from_repo() {

    for (auto &&movie: this->service.get_movies_in_repo()) {
        auto movies = this->service.get_movies_in_repo();
        int position = find(movies.begin(), movies.end(), movie) - movies.begin();
        cout << position + 1 << ". " << movie.to_string() << endl;
    }
}

void UI::user_add_ui() {
    try {
        service.add_movie_to_watch_list(service.get_repository().get_current());
        cout << "Added " << service.get_repository().get_current().get_title()
             << " to your watch list" << endl;
    }
    catch (MovieException &e) {
        for (auto error: e.get_errors())
            cout << error << endl;
    }
    catch (RepositoryException &e) {
        cout << e.what() << endl;
    }
}

void UI::user_remove_ui() {
    int year_of_release;

    cout << "Give title: ";
    std::string title;
    getline(cin, title);

    cout << "Give year of release: ";
//    cin >> year_of_release;
//    cin.ignore();
    read_valid_int(year_of_release);

    Movie m = service.get_repository().find_movie(title, year_of_release);

    if (!(m == NullValue)) {
        cout << "Did you like the movie? [yes/no]" << endl;
        std::string answer;
        getline(cin, answer);
        if (answer == "yes")
            service.update_movie_from_repo(m.get_title(), m.get_year_of_release(),
                                           m.get_genre(), m.get_number_of_likes() + 1, m.get_trailer());
    }
    try {
        service.remove_movie_from_watch_list(m);
        cout << "Removed " << m.get_title() << " from your watch list" << endl;
    }
    catch (RepositoryException &e) {
        cout << e.what() << endl;
    }
}

void UI::display_watch_list_ui() {
    cout << "Here is your watch list: " << endl;

    for (auto &&movie: this->service.get_movies_in_watch_list()) {
        auto movies = this->service.get_movies_in_watch_list();
        int position = find(movies.begin(), movies.end(), movie) - movies.begin();
        cout << position + 1 << ". " << movie.to_string() << endl;
    }

}

void UI::display_current_movie() {
    cout << service.get_repository().get_current().user_to_string() << endl;
    service.get_repository().get_current().play();
}

void UI::run() {
    while (true) {

        print_menu();
        int command;
        cout << "Give command: ";
        cin >> command;
        cin.ignore();
        if (command == 0)
            break;

        if (command == 1) {
            //administrator mode
            while (true) {
                try {
                    UI::print_repo_menu();
                    int option_repo;
                    cout << "Give option: ";
                    cin >> option_repo;
                    cin.ignore();
                    if (option_repo == 0)
                        break;
                    switch (option_repo) {
                        case 1:
                            this->add_movie_ui();
                            break;
                        case 2:
                            this->remove_movie_ui();
                            break;
                        case 3:
                            this->update_movie_ui();
                            break;
                        case 4:
                            this->display_movies_from_repo();
                    }
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        }

        if (command == 2) {
            //user mode
            while (true) {
                try {
                    UI::print_user_menu();
                    int option_user;
                    cout << "Give option: ";
                    cin >> option_user;
                    cin.ignore();
                    if (option_user == 0)
                        break;
                    else if (option_user == 1) {
                        cout << "Choose a genre ('-' for all the movies): ";
                        std::string genre;
                        getline(cin, genre);
                        this->service.first_movie(genre);
                        UI::display_current_movie();
                        while (true) {
                            try {
                                UI::print_current_movie_user_options();
                                int option_user2;
                                cout << "Give option: ";
                                cin >> option_user2;
                                cin.ignore();
                                if (option_user2 == 0)
                                    break;
                                switch (option_user2) {
                                    case 1:
                                        this->user_add_ui();
                                        break;
                                    case 2: {
                                        this->service.next_movie(genre);
                                        display_current_movie();
                                    }
                                }
                            } catch (exception &e) {
                                cout << e.what() << endl;
                            }
                        }
                    } else if (option_user == 2)
                        display_watch_list_ui();
                    else if (option_user == 3)
                        user_remove_ui();
                    else if (option_user == 4) {
                        this->service.save_watch_list(
                                R"(C:\Users\user1\Documents\GitHub\a89-915-Negrila-Iulia\a67-915-Negrila-Iulia\a45-915-Negrila-Iulia\watch_list)");
                    } else if (option_user == 5) {
                        this->service.open_watch_list();
                    }

                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            }
        }
    }
}

