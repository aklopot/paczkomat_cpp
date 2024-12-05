#include "package.h"

Package::Package(std::string phoneNumber, float height, float width, float length)
    : phoneNumber_(std::move(phoneNumber)), 
      dimensions_(std::make_unique<Dimensions>(height, width, length)) {}

Dimensions Package::getDimensions() const { 
    return *dimensions_; 
}

std::string Package::getPhoneNumber() const { 
    return phoneNumber_; 
}