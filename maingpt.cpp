#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>
#include <random>
#include <string>
#include <cassert>
#include <unordered_set>
#include "code_manager_old.h"
#include "locker_old.h"
#include "locker_system_old.h"
#include "dimensions_old.h"

// Entry point
int main() {
    CodeManager codeManager;
    LockerSystem lockerSystem(codeManager);

    try {
        // Create a package with dimensions
        auto package1 = std::make_shared<Package>("123456789", Dimensions(5, 5, 5));
        std::string code1 = lockerSystem.storePackage(package1);
        std::cout << "Package stored with code: " << code1 << "\n";

        lockerSystem.displayStatus();

        // Retrieve the package
        auto retrievedPackage = lockerSystem.retrievePackage(code1, "123456789");
        if (retrievedPackage) {
            std::cout << "Package retrieved for phone number: " << retrievedPackage.value()->getPhoneNumber() << "\n";
        } else {
            std::cout << "Failed to retrieve package. Check code and phone number.\n";
        }

        lockerSystem.displayStatus();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
