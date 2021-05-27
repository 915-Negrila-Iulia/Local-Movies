#include "csv_watch_list.h"
#include "../repository/repository_exceptions.h"
#include <fstream>
#include <Windows.h>

void CSVWatchList::write_to_file() {
    std::ofstream f(this->file_name);

    if (!f.is_open())
        throw FileException("File can't open!");

    for (auto movie: this->movies)
        f << movie;

    f.close();
}

void CSVWatchList::display_watch_list() const {
    std::string name= "\"" + this->file_name + "\"";
    ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", name.c_str(), NULL, SW_SHOWMAXIMIZED);
}
