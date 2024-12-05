#include "parcel_locker.h"


// Implementacja klasy ParcelLocker

ParcelLocker::ParcelLocker(int numSmall, int numMedium, int numLarge) {
    for (int i = 0; i < numSmall; ++i) {
        boxes_.push_back(make_unique<Locker>(10, 10, 40, Locker::Size::SMALL));
    }
    for (int i = 0; i < numMedium; ++i) {
        boxes_.push_back(make_unique<Locker>(20, 20, 40, Locker::Size::MEDIUM));
    }
    for (int i = 0; i < numLarge; ++i) {
        boxes_.push_back(make_unique<Locker>(30, 30, 40, Locker::Size::LARGE));
    }
}

// Funkcje publiczne klasy ParcelLocker

void ParcelLocker::InsertPackage(int boxId, std::shared_ptr<Package> package) {
    if (boxId <= 0 || boxId > (int)boxes_.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    
    boxId--; // Konwersja z numeracji 1-based na 0-based
    if (boxes_[boxId]->InsertPackage(package)) {
        int newCode = codeManager_.generateCode();
        boxes_[boxId]->SetCode(newCode);
    }
}

void ParcelLocker::RemovePackage(int boxId, int code) {
    if (boxId <= 0 || boxId > (int)boxes_.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    boxId--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    if (boxes_[boxId]->IsOccupied() && boxes_[boxId]->CheckCode(code)) {
        codeManager_.deleteCode(code);
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