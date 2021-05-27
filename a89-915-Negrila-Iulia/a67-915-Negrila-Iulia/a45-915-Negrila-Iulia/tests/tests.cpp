#include "tests.h"
#include <cassert>
#include <exception>

void test_movie() {
    Movie default_movie;
    Movie movie{"Titanic", "Action", 1986, 502,
                "https://www.youtube.com/watch?v=CHekzSiZjrY"};

    //movie.play();

    assert(default_movie.get_title() == "");
    assert(default_movie.get_genre() == "");
    assert(default_movie.get_year_of_release() == 0);
    assert(default_movie.get_number_of_likes() == 0);
    assert(default_movie.get_trailer() == "");

    assert(movie.get_title() == "Titanic");
    assert(movie.get_genre() == "Action");
    assert(movie.get_year_of_release() == 1986);
    assert(movie.get_number_of_likes() == 502);
    assert(movie.get_trailer() == "https://www.youtube.com/watch?v=CHekzSiZjrY");

    Movie identical_movie{"Titanic", "Action", 1986, 502,
                          "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    Movie not_identical{"Titanic", "Drama", 1996, 503,
                        "https://www.youtube.com/watch?v=CHekzSiZjrY"};

    //assert(movie==identical_movie);
    //assert(!(movie==not_identical));

    movie.set_genre("Drama");
    movie.set_number_of_likes(1000);
    movie.set_trailer("...");
    assert(movie.get_genre()=="Drama");
    assert(movie.get_number_of_likes()==1000);
    assert(movie.get_trailer()=="...");

    assert(movie.to_string()=="Titanic Drama 1986 1000 ...");

}

void test_validator(){
    Validator v;
    Movie m1{"Titanic", "Action", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    v.validate_movie(m1);

    Movie m2{"", "Action", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    try{
        v.validate_movie(m2);
    }catch (std::exception&e){
        assert(true);
    }

    Movie m3{"Titanic", "", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    try{
        v.validate_movie(m3);
    }catch (std::exception&e){
        assert(true);
    }

    Movie m4{"Titanic", "Action", -45, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    try{
        v.validate_movie(m4);
    }catch (std::exception&e){
        assert(true);
    }

    Movie m5{"Titanic", "Action", 1997, -99,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    try{
        v.validate_movie(m5);
    }catch (std::exception&e){
        assert(true);
    }

    Movie m6{"Titanic", "Action", 1997, 502,
             ""};
    try{
        v.validate_movie(m6);
    }catch (std::exception&e){
        assert(true);
    }

}

void test_template_dynamic_vector(){
    Movie m1{"Titanic", "Action", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    Movie m2{"The Wizard of Oz", "Animation", 1939, 325,
             "https://www.youtube.com/watch?v=njdreZRjvpc"};
    Movie m3{"The pianist", "Drama", 2002, 300,
            "https://www.youtube.com/watch?v=BFwGqLa_oAo"};

    TemplateDynamicVector<Movie> dv(1);
    TemplateDynamicVector<Movie> copy_dv{dv};
    TemplateDynamicVector<Movie> new_dv(5);

    assert(dv.get_length()==0);
    assert(dv.get_capacity()==1);
    assert(copy_dv.get_length()==0);
    assert(copy_dv.get_capacity()==1);

    dv.add(m1);
    dv.add(m2);
    assert(dv.get_length()==2);
    assert(dv.get_capacity()==2);
    assert(copy_dv.get_length()==0);
    assert(copy_dv.get_capacity()==1);
    //assert(!(dv[0]==copy_dv[0]));

    dv.add(m3);
    assert(dv.get_length()==3);
    assert(dv.get_capacity()==4);

   // assert(dv[1]==m2);

    dv.remove(m2);
    assert(dv.get_length()==2);
    assert(dv.get_capacity()==4);

    new_dv=dv;
    assert(new_dv.get_length()==2);
    assert(new_dv.get_capacity()==4);
   // assert(dv[0]==new_dv[0]);
   // assert(dv[1]==new_dv[1]);

}

void test_repository(){
    Repository repo("");
    assert(repo.get_movies().size()==0);
    assert(repo.get_movies().capacity()==0);

    Movie m1{"Titanic", "Action", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    Movie m2{"The Wizard of Oz", "Animation", 1939, 325,
             "https://www.youtube.com/watch?v=njdreZRjvpc"};

    repo.add_movie(m1);
    repo.add_movie(m2);
    assert(repo.get_movies().size()==2);
    assert(repo.get_movies().capacity()==2);
  //  assert(repo.find_movie("Titanic",1997)==m1);

    try {
        repo.add_movie(m1);
    }
    catch(std::exception&e){
        assert(true);
    }

    repo.remove_movie(m1.get_title(),m1.get_year_of_release());
    assert(repo.get_movies().size()==1);
    assert(repo.get_movies().capacity()==1);
  //  assert(repo.find_movie("Titanic",1997)==NullValue);

    try {
        repo.remove_movie(m1.get_title(), m1.get_year_of_release());
    }
    catch(std::exception&e){
        assert(true);
    }

    assert(repo.get_movies().size()==1);
    assert(repo.get_movies().capacity()==1);

    repo.update_movie(m2.get_title(),m2.get_year_of_release(),"Comedy",
                      999,"https://www.youtube.com/watch?v=njdreZRjvpc");
    assert(repo.get_movies()[0].get_genre()=="Comedy");
    assert(repo.get_movies()[0].get_number_of_likes()==999);
    assert(repo.get_movies()[0].get_title()=="The Wizard of Oz");

    repo.remove_movie(m2.get_title(),m2.get_year_of_release());
    assert(repo.get_movies().size()==0);
    assert(repo.get_movies().capacity()==0);

    try {
        repo.update_movie(m2.get_title(),m2.get_year_of_release(),"Comedy",
                          999,"https://www.youtube.com/watch?v=njdreZRjvpc");
    }
    catch(std::exception&e){
        assert(true);
    }

}


void test_service(){
    WatchList wl;
    Repository repo("");
    Service serv{repo, nullptr,Validator{}};
    assert(serv.get_repository().get_movies().capacity()==0);
    assert(serv.get_repository().get_movies().size()==0);

    serv.add_movie_to_repo("Titanic", "Action", 1997, 502,
                           "https://www.youtube.com/watch?v=CHekzSiZjrY");
    serv.add_movie_to_repo("The Wizard of Oz", "Animation", 1939, 325,
                           "https://www.youtube.com/watch?v=njdreZRjvpc");
    serv.add_movie_to_repo("The pianist", "Drama", 2002, 300,
                           "https://www.youtube.com/watch?v=BFwGqLa_oAo");
    serv.add_movie_to_watch_list(repo.find_movie("Titanic",1997));
    serv.add_movie_to_watch_list(repo.find_movie("The pianist",2002));

    assert(serv.get_repository().get_movies().capacity()==3);
    assert(serv.get_repository().get_movies().size()==3);
    assert(serv.get_movies_in_repo().capacity()==3);
    assert(serv.get_movies_in_watch_list().size()==2);

    try{
        serv.add_movie_to_repo("Titanic", "Action", 1997, 502,
                               "https://www.youtube.com/watch?v=CHekzSiZjrY");
    }catch (std::exception&e){
        assert(true);
    }

    try{
        serv.add_movie_to_repo("Titanic", "", 1997, 502,
                               "");
    }catch (std::exception&e){
        assert(true);
    }

    serv.first_movie("-");
    assert(serv.get_repository().get_current().get_title()=="Titanic");
    serv.next_movie("-");
    serv.next_movie("-");
    assert(serv.get_repository().get_current().get_title()=="The pianist");
    serv.next_movie("-");
    assert(serv.get_repository().get_current().get_title()=="Titanic");

    serv.first_movie("Drama");
    assert(serv.get_repository().get_current().get_title()=="The pianist");
    serv.next_movie("Drama");
    assert(serv.get_repository().get_current().get_title()=="The pianist");

    serv.remove_movie_from_watch_list(repo.find_movie("Titanic",1997));
    serv.remove_movie_from_repo("Titanic",1997);

    assert(serv.get_repository().get_movies().capacity()==2);
    assert(serv.get_repository().get_movies().size()==2);
    assert(serv.get_movies_in_repo().capacity()==2);
    assert(serv.get_movies_in_watch_list().size()==1);

    try{
        serv.remove_movie_from_repo("Titanic", 1997);
    }catch (std::exception&e){
        assert(true);
    }

    Movie m=serv.get_movies_in_repo()[0];
    serv.update_movie_from_repo(serv.get_movies_in_repo()[0].get_title(),
                                serv.get_movies_in_repo()[0].get_year_of_release(),
                                "Comedy", 350,
                                "https://www.youtube.com/watch?v=njdreZRjvpc");
    Movie update_m=serv.get_movies_in_repo()[0];
    assert(update_m.get_genre()=="Comedy");
    assert(update_m.get_number_of_likes()==350);
    assert(update_m.get_trailer()==m.get_trailer());

}

void test_watch_list(){
    WatchList wl{};
    Movie m1{"Titanic", "Action", 1997, 502,
             "https://www.youtube.com/watch?v=CHekzSiZjrY"};
    Movie m2{"The Wizard of Oz", "Animation", 1939, 325,
             "https://www.youtube.com/watch?v=njdreZRjvpc"};

    assert(wl.get_movies().size()==0);
    wl.add(m1);
    wl.add(m2);
    assert(wl.get_movies().size()==2);
    assert(wl.get_movies()[0].get_title()=="Titanic");

    wl.remove(m2);
    assert(wl.get_movies().size()==1);
    assert(wl.get_movies()[0].get_title()=="Titanic");

    try{
        wl.remove(m2);
    }
    catch (std::exception &e){
        assert(true);
    }

    assert(wl.find(m1)==0);
    assert(wl.find(m2)==-1);

    try{
        wl.add(m1);
    }
    catch (std::exception &e){
        assert(true);
    }

}


void test_all() {
    test_movie();
    test_validator();
    //test_template_dynamic_vector();
    test_repository();
    test_service();
    test_watch_list();
}