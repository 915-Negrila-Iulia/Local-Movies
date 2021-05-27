#include "service.h"
#include <exception>

void Service::add_movie_to_repo(const std::string &title, const std::string &genre, const int &year_of_release,
                                const int &number_of_likes, const std::string &trailer) {
    /*
        Creates a movie having the given data
        Validates the movie
        Adds the movie to the repository
        Throws exception if the movie is not valid
        Input: title -string, genre -string, year_of_release -integer
        number_of_likes -integer, trailer -string
        Output: -
     */

    Movie m{title,genre,year_of_release,number_of_likes,trailer};
    this->validator.validate_movie(m);
    this->repo.add_movie(m);
}

void Service::remove_movie_from_repo(const std::string &title, const int &year_of_release) {
    /*
        Deletes the movie having given data from the repository
        Input: title -string, year_of_release -integer
        Title and Year of release are the properties which uniquely identify a movie
        Output: -
     */

    this->repo.remove_movie(title,year_of_release);
}

void Service::update_movie_from_repo(const std::string &title, const int &year_of_release, const std::string &new_genre,
                                     const int &new_number_of_likes, const std::string &new_trailer) {
    /*
        Updates the movie uniquely identified by given data
        Validates the new movie and throws exception if it is not valid
        Input: title -string, new_genre -string, year_of_release -integer
        new_number_of_likes -integer, new_trailer -string
        Output: -
     */

    Movie validate_m{title,new_genre,year_of_release,new_number_of_likes,new_trailer};
    Validator v;
    v.validate_movie(validate_m);

    this->repo.update_movie(title,year_of_release,new_genre,new_number_of_likes,new_trailer);
}

std::vector<Movie> Service::get_movies_in_repo() const {
    /*
        Returns all the movies from the repository as a dynamic vector
     */
    return this->repo.get_movies();
}

void Service::add_movie_to_watch_list(const Movie &m) {
    /*
        Adds movie to the watch list
        The movie must be in the repository
        Input: m -movie
        Output: -
     */
    //this->watch_list.add(m);
    if (this->watch_list == nullptr)
        return;
    this->watch_list->add(m);
}

void Service::remove_movie_from_watch_list(const Movie &m) {
    /*
        Deletes a movie from the watch list
        Gives the user the possibility to like the movie
        Input: m -movie
        Output: -
     */
    //this->watch_list.remove(m);
    if (this->watch_list == nullptr)
        return;
    this->watch_list->remove(m);
}

std::vector<Movie> Service::get_movies_in_watch_list() const {
    //return this->watch_list.get_movies();
    if (this->watch_list == nullptr)
        return std::vector<Movie>();

    return this->watch_list->get_movies();
}

void Service::first_movie(const std::string &genre) {
    if(genre=="-"){
        this->repo.first();
        return;
    }
    for (int i=0; i<this->repo.get_movies().size(); i++)
        if(this->repo.get_movies()[i].get_genre()==genre)
            this->repo.set_current(i);
}

void Service::next_movie(const std::string &genre) {
    this->repo.next();
    if (genre=="-") {
        return;
    }
    while (this->repo.get_current().get_genre()!=genre)
        this->repo.next();
}

void Service::save_watch_list(const std::string &file_name) {
    if(this->watch_list == nullptr)
        return;

    this->watch_list->set_file_name(file_name);
    this->watch_list->write_to_file();
}

void Service::open_watch_list() const {
    if(this->watch_list == nullptr)
        return;

    this->watch_list->display_watch_list();
}
