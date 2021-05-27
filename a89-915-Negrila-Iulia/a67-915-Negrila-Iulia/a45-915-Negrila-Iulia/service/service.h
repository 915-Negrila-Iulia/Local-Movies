#pragma once
#include "../repository/repository.h"
#include "../domain/validator.h"
#include "../user_data/watch_list.h"
#include "../user_data/file_watch_list.h"

class Service
{
private:
    Repository &repo;
    //WatchList watch_list;
    FileWatchList *watch_list;
    Validator validator;

public:
    Service(Repository &r,FileWatchList* wl, Validator v): repo{r}, watch_list{wl}, validator{v} {}

    Repository& get_repository() const {return repo;}
    //WatchList get_watch_list() const {return watch_list;}
    FileWatchList* get_watch_list() const {return watch_list;}

    std::vector<Movie> get_movies_in_repo() const;

    //Add movie with given data to the repository
    void add_movie_to_repo(const std::string &title, const std::string &genre,
                           const int &year_of_release, const int &number_of_likes,
                           const std::string &trailer);

    //Delete a movie with given name and year of release from the repository
    void remove_movie_from_repo(const std::string &title, const int &year_of_release);

    //Update a movie (given by its name and year of release)
    //by changing its genre, number of likes, link to its trailer
    void update_movie_from_repo(const std::string &title, const int &year_of_release,
                                const std::string &new_genre, const int &new_number_of_likes,
                                const std::string &new_trailer);

    //Add movie to the watch list of the user
    void add_movie_to_watch_list(const Movie&m);

    //Remove a movie from the watch list of the user
    void remove_movie_from_watch_list(const Movie &m);

    std::vector<Movie> get_movies_in_watch_list() const;

    //Gives the first movie having a given genre in repository
    void first_movie(const std::string &genre);

    //Gives the next movie having a given genre in the repository
    void next_movie(const std::string &genre);

    //save watch list to file
    //throw exception if file cannot be opened
    void save_watch_list(const std::string &file_name);

    //open watch list
    //throw exception if file cannot be opened
    void open_watch_list() const;

};