#pragma once
#include "movie.h"
#include <string>
#include <vector>

class MovieException
{
private:
    std::vector<std::string> errors;

public:
    MovieException(std::vector<std::string> errors);
    std::vector<std::string> get_errors() const;
};

class Validator{
public:

    Validator() {}

    //Validates a given movie
    static void validate_movie(const Movie &m);
};