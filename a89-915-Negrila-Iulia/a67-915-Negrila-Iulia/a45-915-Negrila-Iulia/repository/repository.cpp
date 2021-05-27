#include "repository.h"
#include <exception>
#include <algorithm>
#include <fstream>
#include <string>
#include "repository_exceptions.h"

Repository::Repository(const std::string &file_name) {
    this->file_name=file_name;
    this->read_from_file();
}

void Repository::add_movie(const Movie &m) {
    /*
        Checks if the movie is in the repository
        If not, adds it to the repository
        Throws exception if the movie is already added in the repository
        Input: m -movie
        Output: -
     */
    if(!(find_movie(m.get_title(),m.get_year_of_release())==NullValue))
        throw DuplicateMovieException();
    this->movies.push_back(m);

    this->write_to_file();
}

Movie Repository::find_movie(const std::string &title, const int &year_of_release) {
    /*
        Parse the repository and search for the movie which has
        the given title and year of release
        Input: title -string , year_of_release -integer
        Output: Returns movie having the given title and year of release or
        a NullValue if it cannot be found in the repository
     */

   for(auto movie: this->movies) {
        if (movie.get_title() == title &&
            movie.get_year_of_release() == year_of_release)
            return movie;
    }
    return NullValue;
}

int Repository::get_position(const Movie &m) {
    /*
    Uses 'find' stl algorithm to get an iterator pointing to
    the position of m in repository
    Input: title -string , year_of_release -integer
    Output: Returns position in repository of movie having the given title and year of release or
    a 0 if it cannot be found in the repository
 */
    auto it = std::find(this->movies.begin(), this->movies.end(), m);

    if (it!=this->movies.end())
        return it-this->movies.begin();
    return 0;

//    int i = 0;
//    while (i < this->movies.size()) {
//        if (this->movies[i].get_title() == m.get_title() &&
//            this->movies[i].get_year_of_release() == m.get_year_of_release())
//            return i;
//        i++;
//    }
//    return 0;
}

void Repository::remove_movie(const std::string &title, const int &year_of_release) {
    /*
        Checks if the movie exists in the repository
        If not, throws an exception
        Otherwise, removes the movie from the repository
        Input: title -string, year_of_release -integer
        Title and Year of release are the properties which uniquely identify a movie
        Output: -
     */

    if(this->find_movie(title,year_of_release)==NullValue)
        throw InexistentMovieException();

    Movie m = this->find_movie(title, year_of_release);
    int position = this->get_position(m);
    this->movies.erase(this->movies.begin()+position);

    this->write_to_file();

}

void Repository::update_movie(const std::string &title, const int &year_of_release, const std::string &new_genre,
                              const int &new_number_of_likes, const std::string &new_trailer) {
    /*
        Checks if the movie exists and throws exception if not
        Updates the movie uniquely identified by given data
        By changing its genre, number of likes, link to its trailer
        Input: title -string, new_genre -string, year_of_release -integer
        new_number_of_likes -integer, new_trailer -string
        Output: -
    */

    if(this->find_movie(title,year_of_release)==NullValue)
        throw InexistentMovieException();

    Movie m=this->find_movie(title,year_of_release);

    for (auto&& movie: this->movies) // access by forwarding reference, the type of movie is Movie&
        if (movie == m) {
            movie.set_genre(new_genre);
            movie.set_number_of_likes(new_number_of_likes);
            movie.set_trailer(new_trailer);
            break;
        }

    this->write_to_file();
}

void Repository::first() {
    /*
        Set current position to 0
     */
    this->current=0;
}

void Repository::set_current(int &position){
    /*
        Set current position to a given one
     */
    this->current=position;
}

Movie Repository::get_current() {
    /*
       Returns the movie on the current position in repository
     */
    return this->movies[this->current];
}

void Repository::next() {
    /*
        Gives the next movie from the repository
        In case the current movie is the last one in the repository,
        the next movie will be the first one in the repository
     */
    if (this->current==this->get_movies().size()-1)
        this->current=0;
    else
        this->current++;
}

void Repository::read_from_file() {
    std::ifstream file(this->file_name);

    if (!file.is_open())
        throw FileException("File can't open!");

    Movie m;
    while(file >> m)
        this->movies.push_back(m);

    file.close();
}

void Repository::write_to_file() {
    std::ofstream file(this->file_name);

    if(!file.is_open())
        throw FileException("File can't open!");

    for (auto m : this->movies)
        file << m;

    file.close();
}
