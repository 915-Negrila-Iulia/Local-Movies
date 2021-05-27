#pragma once
#include "file_watch_list.h"

class CSVWatchList: public FileWatchList
{
public:

    //writes watch list to file
    //throw exception if it cannot write
    void write_to_file() override;

    //display watch list using microsoft excel
    void display_watch_list() const override;
};