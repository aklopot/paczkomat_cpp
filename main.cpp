#include "parcel_locker.h"
#include <cstdlib>
#include <iostream>
#include <memory>

template<typename Func>
void executeIfParcelLockerExists(const std::unique_ptr<ParcelLocker>& parcelLocker, Func&& action) {
    if (!parcelLocker) {
        std::cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << std::endl;
        return;
    }
    std::forward<Func>(action)();
}

template<typename Func>
void executeIfParcelLockerNotExists(const std::unique_ptr<ParcelLocker>& parcelLocker, const std::string& message, Func&& action) {
    if (parcelLocker) {
        std::cout << std::endl << message << std::endl;
        return;
    }
    std::forward<Func>(action)();
}

char getMenuChoice() {
    char choice;
    bool validChoice;
    
    do {
        std::cout << std::endl << "\t#################################" << std::endl;
        std::cout << "\tCo chcesz wykonac? Wybierz opcje:" << std::endl;
        std::cout << "\t\t1 - STWORZ paczkomat" << std::endl;
        std::cout << "\t\t2 - ZNISZCZ paczkomat" << std::endl;
        std::cout << "\t\t3 - WYSWIETL stan paczkomatu" << std::endl;
        std::cout << "\t\t4 - WLOZ paczke" << std::endl;
        std::cout << "\t\t5 - WYJMIJ paczke" << std::endl;
        std::cout << "\t\t6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)" << std::endl;
        std::cout << "\t\t9 - DEMO programu paczkomat" << std::endl;
        std::cout << "\t\t0 - WYJSCIE z programu" << std::endl;
        std::cout << "\t#################################" << std::endl;
        std::cout << "\tWybierz opcje [1, 2, 3, 4, 5, 6, 9 lub 0]: ";
        
        std::cin >> choice;
        validChoice = (choice == '0' || choice == '1' || choice == '2' || 
                      choice == '3' || choice == '4' || choice == '5' || 
                      choice == '6' || choice == '9');
                      
        if (!validChoice) {
            system("cls");
            std::cout << std::endl << "\tNiepoprawna opcja. Mozesz wybrac tylko [1, 2, 3, 4, 5, 6, 9 lub 0]" << std::endl;
        }
    } while (!validChoice);
    
    system("cls");
    return choice;
}

void runParcelLockerProgram() {
    std::cout << "Program do obslugi Paczkomatu." << std::endl;
    char menuChoice, confirmChoice;
    bool endProgram = false;
    std::unique_ptr<ParcelLocker> parcelLocker;

    do {
        menuChoice = getMenuChoice();
        
        switch (menuChoice) {
            case '1': // 1 - STWORZ paczkomat
                executeIfParcelLockerNotExists(parcelLocker, 
                    "Paczkomat juz zostal utworzony!",
                    [&]() {
                        std::cout << std::endl << "Tworze nowy paczkomat!" << std::endl;
                        int numSmall, numMedium, numLarge;
                        std::cout << "Podaj liczbe malych skrzynek: ";
                        std::cin >> numSmall;
                        std::cout << "Podaj liczbe srednich skrzynek: ";
                        std::cin >> numMedium;
                        std::cout << "Podaj liczbe duzych skrzynek: ";
                        std::cin >> numLarge;
                        parcelLocker = std::make_unique<ParcelLocker>(numSmall, numMedium, numLarge);
                        std::cout << "Paczkomat zostal utworzony." << std::endl;
                    });
                break;
            case '2': // 2 - ZNISZCZ paczkomat
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    std::cout << "\tCzy na pewno chcesz zniszczyc Paczkomat? [T/N]: ";
                    std::cin >> confirmChoice;
                    if (confirmChoice == 'T' || confirmChoice == 't') {
                        parcelLocker.reset();
                        std::cout << "Paczkomat zostal zniszczony." << std::endl;
                    }
                });
                break;
            case '3': // 3 - WYSWIETL stan paczkomatu"
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    parcelLocker->DisplayLockerStatus();
                });
                break;
            case '4': // 4 - WLOZ paczke
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    int boxId;
                    float height, width, length;
                    std::cout << "Podaj ID skrzynki: ";
                    std::cin >> boxId;
                    std::cout << "Podaj wysokosc paczki: ";
                    std::cin >> height;
                    std::cout << "Podaj szerokosc paczki: ";
                    std::cin >> width;
                    std::cout << "Podaj dlugosc paczki: ";
                    std::cin >> length;
                    auto package = std::make_shared<Package>("123456789", height, width, length);
                    parcelLocker->InsertPackage(boxId, package);
                });
                break;
            case '5': // 5 - WYJMIJ paczke
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    int boxId, code;
                    std::cout << "Podaj ID skrzynki: ";
                    std::cin >> boxId;
                    std::cout << "Podaj kod: ";
                    std::cin >> code;
                    parcelLocker->RemovePackage(boxId, code);
                });
                break;
            case '6': // 6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    int boxId;
                    std::cout << "Podaj ID skrzynki: ";
                    std::cin >> boxId;
                    parcelLocker->GetCode(boxId);
                });
                break;
            case '9': // 9 - DEMO programu paczkomat
                executeIfParcelLockerNotExists(parcelLocker,
                    "Przed uruchomieniem DEMO zniszcz obecny paczkomat. Wybiez opcje numer 2!",
                    [&]() {
                        std::cout << "Wersja DEMO paczkomatu!" << std::endl;
                        std::cout << "Tworze paczkomat o ilosci skrzynek: 5-MALE, 4-SREDNIE, 3-DUZE" << std::endl;
                        parcelLocker = std::make_unique<ParcelLocker>(5, 4, 3);
                        std::cout << std::endl << "Dodaje paczke do skrzynki 2 (paczka 8x4x5 - paczka OK):";
                        auto package = std::make_shared<Package>("123456789", 8,4,5);
                        parcelLocker->InsertPackage(2,package);

                        std::cout << std::endl << "Dodaje paczke do skrzynki 6 (paczka 25x20x5 - paczka za duza):";
                        package = std::make_shared<Package>("123456789", 25,20,5);
                        parcelLocker->InsertPackage(6,package);

                        std::cout << std::endl << "Dodaje paczke do skrzynki 10 (paczka 25x20x5 - paczka OK):";
                        package = std::make_shared<Package>("123456789", 25,20,5);
                        parcelLocker->InsertPackage(10,package);

                        std::cout << std::endl << "Dodaje paczke do skrzynki 2 (paczka 9x9x10 - skrzynka zajeta):";
                        package = std::make_shared<Package>("123456789", 9,9,10);
                        parcelLocker->InsertPackage(2,package);

                        std::cout << std::endl << "Dodaje paczke do skrzynki 6 (paczka 9x9x10 - paczka OK):";
                        package = std::make_shared<Package>("123456789", 9,9,10);
                        parcelLocker->InsertPackage(6,package);
                    });
                break;
            case '0': // 0 - WYJSCIE z programu
                std::cout << "\tCzy na pewno chcesz zakonczyc program? [T/N]: ";
                std::cin >> confirmChoice;
                if (confirmChoice == 'T' || confirmChoice == 't') {
                    std::cout << "\tDziekuje za korzystanie z programu do obslugi Paczkomatu!" << std::endl;
                    endProgram = true;
                    if (parcelLocker) {
                        parcelLocker.reset();
                    }
                }
                break;
            default:
                std::cout << std::endl
                     << "\tNieobslugiwana wartosc: [" << menuChoice << "]" << std::endl;
        }
    } while (!endProgram);

    std::cout << std::endl; 
    system("pause"); 
}

int main() {
    runParcelLockerProgram();
    return 0;
}