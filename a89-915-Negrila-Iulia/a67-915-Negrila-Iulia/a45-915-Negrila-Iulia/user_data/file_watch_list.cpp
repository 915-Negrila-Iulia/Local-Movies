#include "file_watch_list.h"

FileWatchList::FileWatchList(): WatchList(), file_name{""} {

}

void FileWatchList::set_file_name(const std::string &file_name) {
    this->file_name=file_name;
}