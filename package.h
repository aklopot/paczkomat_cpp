#ifndef PACKAGE_H
#define PACKAGE_H

#include "dimensions.h"
#include <string>
#include <memory>

class Package {
public:
    Package(std::string phoneNumber, float height, float width, float length);
    
    Dimensions getDimensions() const;
    std::string getPhoneNumber() const;

private:
    std::string phoneNumber_;
    std::unique_ptr<Dimensions> dimensions_;
};

#endif // PACKAGE_H