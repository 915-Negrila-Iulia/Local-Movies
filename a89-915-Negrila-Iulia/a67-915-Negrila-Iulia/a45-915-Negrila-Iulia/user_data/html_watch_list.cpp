#include "html_watch_list.h"
#include <fstream>
#include <Windows.h>
#include "../repository/repository_exceptions.h"

void HTMLWatchList::write_to_file() {
    std::ofstream f(this->file_name);

    if (!f.is_open())
        throw FileException("File can't open!");

    f <<"<!DOCTYPE html>\n"<<"<html>\n"<<"<head>\n"<<"<title>WatchList</title>\n"
    <<"</head>\n"<<"<body>\n"<<"<table border=\"1\">\n"<<"<tr>\n"<<"<td>Title</td>\n"
    <<"<td>Genre</td>\n"<<"<td>Year</td>\n"<<"<td>Likes</td>\n"<<"<td>Trailer</td>\n"<<"</tr>\n";


    for (auto m: this->movies){
        f<<"<tr>"<<"<td>"<<m.get_title()<<"</td>\n"<<"<td>"<<m.get_genre()<<"</td>\n"
        <<"<td>"<<m.get_year_of_release()<<"</td>\n"<<"<td>"<<m.get_number_of_likes()<<"</td>\n"
        <<"<td><a href=\""<<m.get_trailer()<<"\">Link</a></td>\n"<<"</tr>";
    }

       f<<"</table>\n"
       "</body>\n"
       "</html>";
}

void HTMLWatchList::display_watch_list() const {
    std::string name= "\"" + this->file_name + "\"";
    //ShellExecute(NULL, "open", this->file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteA(NULL, "open", "firefox.exe", this->file_name.c_str(), NULL, SW_SHOWMAXIMIZED);
}

