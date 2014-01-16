#pragma once
#include <exception>

struct DBZException : public exception {
    const char* what () const throw (){
        return "Division by zero";
    }
};

struct URException : public exception {
    const char* what () const throw (){
        return "Result is undefined";
    }
};