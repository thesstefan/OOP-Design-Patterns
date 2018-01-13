#include <iostream>

#include "exception.h"

Exception::Exception() {
    this->message = nullptr;
}

Exception::Exception(const char *message) {
    this->message = message;
}

Exception& Exception::operator=(const Exception &exception) {
    this->message = exception.message;
}

const char* Exception::what() const {
    return this->message;
}

OutOfRange::OutOfRange(const char *message) : Exception(message) {}
BadAlloc::BadAlloc(const char *message) : Exception(message) {}
Error::Error(const char *message) : Exception(message) {}
