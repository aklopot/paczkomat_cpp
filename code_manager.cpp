#include "code_manager.h"

int CodeManager::generateCode() {
    std::uniform_int_distribution<int> distribution(100000, 999999);
    int code;
    do {
        code = distribution(generator_);
    } while (usedCodes_.count(code) > 0);
    
    usedCodes_.insert(code);
    return code;
}

void CodeManager::deleteCode(int code) {
    usedCodes_.erase(code);
}

bool CodeManager::isCodeUsed(int code) const {
    return usedCodes_.count(code) > 0;
}