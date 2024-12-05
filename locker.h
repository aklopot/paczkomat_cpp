#ifndef LOCKER_H
#define LOCKER_H

#include "package.h"
#include <iostream>
#include <memory>

using namespace std;

class Locker {
  public:
    enum class Size { SMALL, MEDIUM, LARGE };

  private:
    Dimensions dimensions_;
    bool occupied_;
    int code_;
    Size size_;
    shared_ptr<Package> package_; // Wskaźnik na przechowywaną paczkę
    string GetSize() const;
    

  public:
    Locker(float height, float width, float length, Size size);
    bool InsertPackage(std::shared_ptr<Package> package);
    bool IsOccupied() const;
    bool CheckCode(int enteredCode);
    void RemovePackage();
    int GetCode() const;
    void DisplayBoxStatus() const;
    void SetCode(int code) { code_ = code; }
};

#endif // LOCKER_H