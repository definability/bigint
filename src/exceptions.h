#include <exception>

struct DBZException : public exception {
    const char* what () const throw (){
        return "Division by zero";
    }
};