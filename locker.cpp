#include "locker.h"

// Implementacja klasy Locker

Locker::Locker(float height, float width, float length, Size size)
    : dimensions_(height, width, length), occupied_(false), code_(0), size_(size) {}

// Funkcja prywatne klasy Locker

string Locker::GetSize() const {
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
        cout << endl << "Skrzynka jest juz zajeta!" << endl;
        return false;
    }
    
    const Dimensions& packageDim = package->getDimensions();
    if (packageDim.fitsInto(dimensions_)) {
        occupied_ = true;
        package_ = package;
        cout << endl << "Do skrzynki o rozmiarze " << GetSize() 
             << " [" << dimensions_.height_ << "x" << dimensions_.width_ << "x" << dimensions_.length_ << "] "
             << "pomyslnie wlozono paczke o rozmiarze: " 
             << packageDim.height_ << "x" << packageDim.width_ << "x" << packageDim.length_ << endl;
        return true;
    } else {
        cout << endl << "W skrzynce o rozmarze " << GetSize() 
             << " [" << dimensions_.height_ << "x" << dimensions_.width_ << "] "
             << "nie miesci sie paczka o rozmarze " 
             << packageDim.height_ << "x" << packageDim.width_ << "x" << packageDim.length_ << "!" << endl;
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
        cout << "Paczka pomyslnie wyjeta ze skrzynki o rozmiarze " << GetSize() << endl;
    } else {
        cout << "Skrzynka jest pusta!" << endl;
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
    cout << "Rozmiar: " << GetSize() 
         << ", Wysokosc: " << dimensions_.height_
         << ", Szerokosc: " << dimensions_.width_
         << ", Dlugosc: " << dimensions_.length_
         << ", Zajeta: " << (occupied_ ? "TAK" : "NIE") << endl;
}
