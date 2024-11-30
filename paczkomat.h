#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Box {
  public:
    enum class Size { SMALL, MEDIUM, LARGE };

  private:
    float height_;
    float width_;
    bool occupied_;
    int code_;
    Size size_;
    string GetSize() const;
    int GenerateCode();
    

  public:
    Box(float height, float width, Size size);
    bool InsertPackage(float height, float width);
    bool IsOccupied() const;
    bool CheckCode(int enteredCode);
    void RemovePackage();
    int GetCode() const;
    void DisplayBoxStatus() const;
};

class ParcelLocker {
  private:
    vector<unique_ptr<Box>> boxes_;

  public:
    ParcelLocker(int numSmall, int numMedium, int numLarge);
    void InsertPackage(int boxId, float height, float width);
    void RemovePackage(int boxId, int code);
    void DisplayLockerStatus() const;
    void GetCode(int boxId) const;
};