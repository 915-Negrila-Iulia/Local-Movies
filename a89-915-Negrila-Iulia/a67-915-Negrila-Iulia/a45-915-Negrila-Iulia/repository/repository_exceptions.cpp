#include "repository_exceptions.h"

RepositoryException::RepositoryException(): exception{}, message{""} {

}

RepositoryException::RepositoryException(const std::string &msg): message{msg} {

}

const char * RepositoryException::what(){
    /*
        c_str returns a const char* that points to a null-terminated string
        (i.e. a C-style string). It is useful when you want to pass the "contents"
        of an std::string to a function that expects to work with a C-style string
     */
    return this->message.c_str();
}

const char *DuplicateMovieException::what() {
    return "Movie already exists!";
}

const char *InexistentMovieException::what() {
    return "Movie does not exist!";
}

FileException::FileException(const std::string &msg): message(msg) {

}

const char *FileException::what() {
    return message.c_str();
}
