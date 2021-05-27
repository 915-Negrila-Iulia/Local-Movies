#include "watch_list.h"
#include<algorithm>
#include "../repository/repository_exceptions.h"

void WatchList::add(const Movie &m) {
    /*
        Adds a given movie to the watch list
     */
    if (this->find(m)!=-1)
        throw DuplicateMovieException();
    this->movies.push_back(m);
}

void WatchList::remove(const Movie &m) {
    /*
        Removes a given movie from the watch list
     */
    if (this->find(m)==-1)
        throw InexistentMovieException();
    int position=this->find(m);
    this->movies.erase(this->movies.begin()+position);
}

int WatchList::find(const Movie &m) {
    /*
        Search for a given movie in the watch list
        Input: m -movie
        Output: Position of m in watch list if the given movie exists in the watch list,
                -1 otherwise
     */
    auto it = std::find(this->movies.begin(), this->movies.end(), m);

    if (it!=this->movies.end())
        return it-this->movies.begin();
    return -1;

}