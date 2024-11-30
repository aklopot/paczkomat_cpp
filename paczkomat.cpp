#include "paczkomat.h"

// Implementacja klasy Box

Box::Box(float height, float width, Size size)
    : height_(height), width_(width), occupied_(false), code_(0), size_(size) {}

// Funkcja prywatne klasy Box

string Box::GetSize() const {
    switch (size_) {
        case Size::SMALL: return "Mala";
        case Size::MEDIUM: return "Srednia";
        case Size::LARGE: return "Duza";
        default: return "Nieznany";
    }
}

int Box::GenerateCode() {
    return rand() % 900000 + 100000;
}

// Funkcje publiczne klasy Box

bool Box::InsertPackage(float height, float width) {
    if (occupied_) {
        cout << endl << "Skrzynka jest juz zajeta!" << endl;
        return false;
    }
    if (height <= height_ && width <= width_) {
        occupied_ = true;
        code_ = GenerateCode();
        cout << endl << "Do skrzynki o rozmiarze " << GetSize() << " [" << height_ << "x" << width_ << "] pomyslenie wlozono paczke o rozmiarze: " << height << "x" << width << endl;
        cout << "Kod do otwarcia: " << code_ << endl;
        return true;
    } else {
        cout << endl << "W skrzynce o rozmarze " << GetSize() << " [" << height_ << "x" << width_ << "] nie miesci sie paczka o rozmarze " << height << "x" << width << "!" << endl;
        return false;
    }
}

bool Box::IsOccupied() const {
    return occupied_;
}

bool Box::CheckCode(int enteredCode) {
    return code_ == enteredCode;
}

void Box::RemovePackage() {
    if (occupied_) {
        occupied_ = false;
        code_ = 0;
        cout << "Paczka pomyslnie wyjeta ze skrzynki o rozmiarze " << GetSize() << endl;
    } else {
        cout << "Skrzynka jest pusta!" << endl;
    }
}

int Box::GetCode() const {
    if (occupied_) {
        return code_;
    } else {
        // Kod -1 oznacza, że skrzynka jest pusta
        return -1;
    }
}

void Box::DisplayBoxStatus() const {
    cout << "Rozmiar: " << GetSize() << ", Wysokosc: " << height_ << ", Szerokosc: " << width_
         << ", Zajeta: " << (occupied_ ? "TAK" : "NIE") << endl;
}

// Implementacja klasy ParcelLocker

ParcelLocker::ParcelLocker(int numSmall, int numMedium, int numLarge) {
    for (int i = 0; i < numSmall; ++i) {
        boxes_.push_back(make_unique<Box>(10, 10, Box::Size::SMALL));
    }
    for (int i = 0; i < numMedium; ++i) {
        boxes_.push_back(make_unique<Box>(20, 20, Box::Size::MEDIUM));
    }
    for (int i = 0; i < numLarge; ++i) {
        boxes_.push_back(make_unique<Box>(30, 30, Box::Size::LARGE));
    }
}

// Funkcje publiczne klasy ParcelLocker

void ParcelLocker::InsertPackage(int boxId, float height, float width) {
    if (boxId <= 0 || boxId > (int)boxes_.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    boxId--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    boxes_[boxId]->InsertPackage(height, width);
}

void ParcelLocker::RemovePackage(int boxId, int code) {
    if (boxId <= 0 || boxId > (int)boxes_.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    boxId--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    if (boxes_[boxId]->IsOccupied() && boxes_[boxId]->CheckCode(code)) {
        boxes_[boxId]->RemovePackage();
    } else {
        cout << "Niepoprawny kod lub skrzynka jest pusta!" << endl;
    }
}

void ParcelLocker::DisplayLockerStatus() const {
    for (size_t i = 0; i < boxes_.size(); ++i) {
        cout << "Skrzynka " << i+1 << ": ";
        boxes_[i]->DisplayBoxStatus();
    }
}

void ParcelLocker::GetCode(int boxId) const {
    if (boxId <= 0 || boxId > (int)boxes_.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    boxId--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    if (boxes_[boxId]->IsOccupied()) {
        cout << "Wysylam kod e-mailem/SMSem :)" << endl;
        cout << "Kod do skrzynki " << boxId+1 << ": " << boxes_[boxId]->GetCode() << endl;
    } else {
        cout << "Skrzynka jest pusta!" << endl;
    }
}