#include "exception.h"

MException::MException() : message("Error!") {}
MException::MException(std::string  message) : message(std::move(message)) {}

std::ostream& operator <<(std::ostream &os, MException &exc){
    os << "exception: " << exc.message << std::endl;
    return os;
}