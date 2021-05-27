#pragma once
#include <iostream>
#include <vector>

class Movie{

private:
    std::string title;
    std::string genre;
    int year_of_release;
    int number_of_likes;
    std::string trailer;

public:
    //default constructor
    Movie();

    //constructor with parameters
    Movie(const std::string &title, const std::string &genre, const int &year_of_release, const int &number_of_likes,
          const std::string &trailer);

    std::string get_title() const {return title;}
    std::string get_genre() const {return genre;}
    int get_year_of_release() const {return year_of_release;}
    int get_number_of_likes() const {return number_of_likes;}
    std::string get_trailer() const {return trailer;}

    void set_genre(const std::string &value);
    void set_number_of_likes(const int &value) { this->number_of_likes=value;}
    void set_trailer(const std::string &value) {this->trailer=value;}

    //plays trailer of the current movie
    void play();

    //check if 2 movies are identical by overloading operator ==
    bool operator==(const Movie &m1);

    //return movie's data as a string
    std::string to_string();

    //return movie's data as string without the link of the trailer
    std::string user_to_string();

    friend std::istream &operator>>(std::istream &is, Movie &m);
    friend std::ostream &operator<<(std::ostream &os, const Movie &m);
};