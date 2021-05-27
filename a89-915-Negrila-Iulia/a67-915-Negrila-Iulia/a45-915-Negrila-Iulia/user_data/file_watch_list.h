#pragma once
#include "watch_list.h"

class FileWatchList: public WatchList
{
protected:
    std::string file_name;
public:
    FileWatchList();
    virtual ~FileWatchList() {}

    void set_file_name(const std::string &file_name);
    virtual void write_to_file() = 0;
    virtual void display_watch_list()const = 0;
};