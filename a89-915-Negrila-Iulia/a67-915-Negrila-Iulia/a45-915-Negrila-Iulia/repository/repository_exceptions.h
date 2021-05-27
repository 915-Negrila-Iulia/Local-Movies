#pragma once
#include <string>
#include <exception>

class RepositoryException: public std::exception{
protected:
    std::string message;

public:
    RepositoryException();
    RepositoryException(const std::string &msg);

    /*
        A virtual function is a member function which is declared within a base
        class and is re-defined(Overriden) by a derived class
     */
    virtual const char *what();
    virtual ~RepositoryException() {}
};

class DuplicateMovieException: public RepositoryException{
public:
    const char *what();
};

class InexistentMovieException: public RepositoryException{
public:
    const char *what();
};

class FileException: public std::exception{
protected:
    std::string message;

public:
    FileException(const std::string &msg);
    virtual const char *what();
};