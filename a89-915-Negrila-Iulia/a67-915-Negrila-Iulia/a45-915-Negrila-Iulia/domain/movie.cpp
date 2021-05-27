#include "movie.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <sstream>

Movie::Movie() : title(""), genre(""), year_of_release(0), number_of_likes(0), trailer("") {}

Movie::Movie(const std::string &title, const std::string &genre, const int &year_of_release, const int &number_of_likes,
             const std::string &trailer) {
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->trailer = trailer;
}


bool Movie::operator==(const Movie &m) {

    return (this->title==m.title && this->genre==m.genre);
}


void Movie::play() {
    ShellExecute(NULL, "open", this->get_trailer().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

std::string Movie::to_string() {
    return this->title + " " + this->genre + " " + std::to_string(this->year_of_release) + " "
           + std::to_string(this->number_of_likes) + " " + this->trailer;
}

void Movie::set_genre(const std::string &value) {
    this->genre=value;
}

std::string Movie::user_to_string(){
    return this->title + " " + this->genre + " " + std::to_string(this->year_of_release) + " "
           + std::to_string(this->number_of_likes);
}

std::vector<std::string> split(const std::string &str, char delimiter){
    std::vector<std::string> string_split;
    std::stringstream ss(str);
    std::string element;
    while(getline(ss,element,delimiter))
        string_split.push_back(element);

    return string_split;
}

std::istream &operator>>(std::istream &is, Movie &m) {
    std::string line;
    getline(is, line);

    std::vector<std::string> elements = split(line, ',');
    if (elements.size()!=5)
        return is;

    m.title = elements[0];
    m.genre = elements[1];
    m.year_of_release = stoi(elements[2]);
    m.number_of_likes = stoi(elements[3]);
    m.trailer = elements[4];

    return is;
}

std::ostream &operator<<(std::ostream &os, const Movie &m) {
    os<<m.title<<","<<m.genre<<","<<m.year_of_release
    <<","<<m.number_of_likes<<","<<m.trailer<<"\n";

    return os;
}

