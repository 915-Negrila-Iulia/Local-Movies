#pragma once
#include "../domain/movie.h"
#include <vector>

class WatchList{
protected:
    std::vector<Movie> movies;

public:
    WatchList() {}
    virtual ~WatchList() {}

    //add movie to the watch list
    void add(const Movie &m);

    //remove movie from the watch list
    void remove(const Movie &m);

    //check if a movie is in the watch list
    int find(const Movie &m);

    //get movies from watch list
    std::vector<Movie> get_movies () const {return movies;}
};