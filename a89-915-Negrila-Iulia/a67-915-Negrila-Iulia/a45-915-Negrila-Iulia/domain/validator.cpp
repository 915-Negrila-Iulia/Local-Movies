#include "validator.h"
#include <exception>
#include <utility>

void Validator::validate_movie(const Movie &m) {

    std::vector<std::string> errors;

    if (m.get_title()=="")
        errors.push_back("Movie must have a title");

    if (m.get_genre()=="")
        errors.push_back("Movie must have a genre");

    if (m.get_year_of_release()<0)
        errors.push_back("Year must be a positive number");

    if (m.get_number_of_likes()<0)
        errors.push_back("Movie cannot have dislikes");

    if (m.get_trailer()=="")
        errors.push_back("Movie must have a link to its trailer");

    if(!isupper(m.get_title()[0]))
        errors.push_back("Title must start with capital letter");

    if(m.get_trailer().find("www")!=0 && m.get_trailer().find("http")!=0)
        errors.push_back("Trailer must begin with 'www' or 'http'");

    if (errors.size()>0)
        throw MovieException(errors);
}

MovieException::MovieException(std::vector<std::string> _errors): errors{_errors}{

}

std::vector<std::string> MovieException::get_errors() const {
    return this->errors;
}
