#pragma once
#include "file_watch_list.h"

class HTMLWatchList: public FileWatchList
{
public:

    //writes watch list to file
    //throw exception if it cannot write
    void write_to_file() override;

    //display watch list using a browser
    void display_watch_list() const override;

};