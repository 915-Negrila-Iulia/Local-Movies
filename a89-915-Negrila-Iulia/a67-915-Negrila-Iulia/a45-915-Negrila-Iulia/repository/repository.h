#pragma once

#include "../domain/movie.h"
#define NullValue Movie("0", "0", 0, 0,"0")

#include <vector>

class Repository {
private:
    std::vector<Movie> movies;
    int current;
    std::string file_name;

public:
    //Constructor with parameters
    //Initialises an object of type Repository
    //by reading data from a given file
    Repository(const std::string &file_name);

    //Adds a given movie to the repository
    void add_movie(const Movie &m);

    //Removes the movie uniquely identified by given data from the repository
    void remove_movie(const std::string &title, const int &year_of_release);

    //Updates a movie
    void update_movie(const std::string &title, const int &year_of_release,
                      const std::string &new_genre, const int &new_number_of_likes,
                      const std::string &new_trailer);

    //Finds and returns a movie
    //Movies are uniquely identified by their name and year of release
    Movie find_movie(const std::string &title, const int &year_of_release);

    //Returns a dynamic vector containing all the movies from the repository
    std::vector<Movie>get_movies() const {return movies;}

    //Returns position of an element int the repository
    int get_position(const Movie &m);

    //Get the first movie in repository
    void first();

    //Set position of the current element
    void set_current(int &position);

    //Get the current movie
    Movie get_current();

    //Gives the next movie in the repository
    void next();

private:
    void read_from_file();
    void write_to_file();
};