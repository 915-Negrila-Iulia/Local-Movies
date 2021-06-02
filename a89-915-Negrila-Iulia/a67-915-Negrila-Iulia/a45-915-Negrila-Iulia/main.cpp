#include <iostream>
#include "ui/ui.h"
#include "tests/tests.h"
#include <crtdbg.h>
#include "user_data/csv_watch_list.h"
#include "repository/repository_exceptions.h"
#include "user_data/html_watch_list.h"

#include <QApplication>
#include <memory>
#include "gui/gui.h"
#include <QMessageBox>

using namespace std;


int main(int argc, char *argv[]) {
    {
        cout<<"Choose user interface[console/gui]: ";
        string choose_ui;
        getline(cin, choose_ui);
        if(choose_ui=="console") {
            //test_all();
            try {
                Repository repo(
                        R"(C:\Users\user1\Documents\GitHub\a89-915-Negrila-Iulia\a67-915-Negrila-Iulia\a45-915-Negrila-Iulia\movies.txt)");

                FileWatchList *wl;
                string file;
                while (true) {
                    cout << "Choose the type of watch list's file[csv/html]: ";
                    cin >> file;
                    cin.ignore();
                    if (file == "csv") {
                        wl = new CSVWatchList{};
                        break;
                    } else if (file == "html") {
                        wl = new HTMLWatchList{};
                        break;
                    } else
                        cout << "sorry, wrong file";
                }
                Service service{repo, wl, Validator{}};
                service.add_movie_to_watch_list(
                        Movie("Schindler's List", "Drama", 1993, 400, "https://www.youtube.com/watch?v=mxphAlJID9U"));
                service.add_movie_to_watch_list(
                        Movie("Une Rencontre", "Love", 2014, 300, "https://www.youtube.com/watch?v=BOOEKikaQ5k"));
                service.add_movie_to_watch_list(
                        Movie("The pianist", "Drama", 2002, 300, "https://www.youtube.com/watch?v=BFwGqLa_oAo"));

                UI ui{service};
                ui.run();
                delete wl;

            } catch (FileException &) {
                cout << "Can't find repository file!" << endl;
                return 1;
            }
            return 0;
        }
        else if(choose_ui=="gui"){
            QApplication a(argc, argv);

            Repository repo(
                    R"(C:\Users\user1\Documents\GitHub\a89-915-Negrila-Iulia\a67-915-Negrila-Iulia\a45-915-Negrila-Iulia\movies.txt)");

            QWidget *choose_file = nullptr;
            int file = QMessageBox::question(
                    choose_file, "file", "Choose file:", QString::fromStdString("CSV"),QString::fromStdString("HTML"));

            unique_ptr<FileWatchList> wl;
            if (file==0)
                wl = make_unique<CSVWatchList>();
            else
                wl = make_unique<HTMLWatchList>();

            Service service{repo, wl.get(), Validator{}};
            service.add_movie_to_watch_list(
                    Movie("Schindler's List", "Drama", 1993, 400, "https://www.youtube.com/watch?v=mxphAlJID9U"));
            service.add_movie_to_watch_list(
                    Movie("Une Rencontre", "Love", 2014, 300, "https://www.youtube.com/watch?v=BOOEKikaQ5k"));
            service.add_movie_to_watch_list(
                    Movie("The pianist", "Drama", 2002, 300, "https://www.youtube.com/watch?v=BFwGqLa_oAo"));

            GUI gui{service};
            gui.setWindowTitle("So many movies, so little time");
            gui.show();

            return a.exec();
        }
        else cout<<"invalid ui";
    }
    return 0;
}