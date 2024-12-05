#ifndef CODE_MANAGER_H
#define CODE_MANAGER_H

#include <unordered_set>
#include <random>

class CodeManager {
public:
    // Generuje unikalny 6-cyfrowy kod
    int generateCode();
    
    // Unieważnia istniejący kod
    void deleteCode(int code);
    
    // Sprawdza, czy kod jest aktualnie używany
    bool isCodeUsed(int code) const;

private:
    std::unordered_set<int> usedCodes_;  // Zbiór aktualnie używanych kodów
    std::mt19937 generator_;             // Generator liczb pseudolosowych
};

#endif // CODE_MANAGER_H
