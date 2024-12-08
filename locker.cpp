#include "locker.h"

// Implementacja klasy Locker

Locker::Locker(float height, float width, float length, Size size)
    : dimensions_(height, width, length), occupied_(false), code_(0), size_(size) {}

// Funkcja prywatne klasy Locker

std::string Locker::GetSize() const {
    switch (size_) {
        case Size::SMALL: return "Mala";
        case Size::MEDIUM: return "Srednia";
        case Size::LARGE: return "Duza";
        default: return "Nieznany";
    }
}

// Funkcje publiczne klasy Locker

bool Locker::InsertPackage(std::shared_ptr<Package> package) {
    if (occupied_) {
        std::cout << std::endl << "Skrzynka jest juz zajeta!" << std::endl;
        return false;
    }
    
    const Dimensions& packageDim = package->getDimensions();
    if (packageDim.fitsInto(dimensions_)) {
        occupied_ = true;
        package_ = package;
        std::cout << std::endl << "Do skrzynki o rozmiarze " << GetSize() 
             << " [" << dimensions_.height_ << "x" << dimensions_.width_ << "x" << dimensions_.length_ << "] "
             << "pomyslnie wlozono paczke o rozmiarze: " 
             << packageDim.height_ << "x" << packageDim.width_ << "x" << packageDim.length_ << std::endl;
        return true;
    } else {
        std::cout << std::endl << "W skrzynce o rozmarze " << GetSize() 
             << " [" << dimensions_.height_ << "x" << dimensions_.width_ << "] "
             << "nie miesci sie paczka o rozmarze " 
             << packageDim.height_ << "x" << packageDim.width_ << "x" << packageDim.length_ << "!" << std::endl;
        return false;
    }
}

bool Locker::IsOccupied() const {
    return occupied_;
}

bool Locker::CheckCode(int enteredCode) {
    return code_ == enteredCode;
}

void Locker::RemovePackage() {
    if (occupied_) {
        occupied_ = false;
        code_ = 0;
        std::cout << "Paczka pomyslnie wyjeta ze skrzynki o rozmiarze " << GetSize() << std::endl;
    } else {
        std::cout << "Skrzynka jest pusta!" << std::endl;
    }
}

int Locker::GetCode() const {
    if (occupied_) {
        return code_;
    } else {
        // Kod -1 oznacza, że skrzynka jest pusta
        return -1;
    }
}

void Locker::DisplayBoxStatus() const {
    std::cout << "Rozmiar: " << GetSize() 
         << ", Wysokosc: " << dimensions_.height_
         << ", Szerokosc: " << dimensions_.width_
         << ", Dlugosc: " << dimensions_.length_
         << ", Zajeta: " << (occupied_ ? "TAK" : "NIE") << std::endl;
}
