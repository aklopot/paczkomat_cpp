#ifndef PARCEL_LOCKER_H
#define PARCEL_LOCKER_H

#include "locker.h"
#include "code_manager.h"
#include <iostream>
#include <vector>
#include <memory>

class ParcelLocker {
  private:
    vector<unique_ptr<Locker>> boxes_;
    CodeManager codeManager_;

  public:
    ParcelLocker(int numSmall, int numMedium, int numLarge);
    void InsertPackage(int boxId, std::shared_ptr<Package> package);
    void RemovePackage(int boxId, int code);
    void DisplayLockerStatus() const;
    void GetCode(int boxId) const;
};

#endif // PARCEL_LOCKER_H