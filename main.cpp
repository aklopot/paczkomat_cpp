#include "parcel_locker.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

template<typename Func>
void executeIfParcelLockerExists(const unique_ptr<ParcelLocker>& parcelLocker, Func&& action) {
    if (!parcelLocker) {
        cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
        return;
    }
    std::forward<Func>(action)();
}

template<typename Func>
void executeIfParcelLockerNotExists(const unique_ptr<ParcelLocker>& parcelLocker, const string& message, Func&& action) {
    if (parcelLocker) {
        cout << endl << message << endl;
        return;
    }
    std::forward<Func>(action)();
}

char getMenuChoice() {
    char choice;
    bool validChoice;
    
    do {
        cout << endl << "\t#################################" << endl;
        cout << "\tCo chcesz wykonac? Wybierz opcje:" << endl;
        cout << "\t\t1 - STWORZ paczkomat" << endl;
        cout << "\t\t2 - ZNISZCZ paczkomat" << endl;
        cout << "\t\t3 - WYSWIETL stan paczkomatu" << endl;
        cout << "\t\t4 - WLOZ paczke" << endl;
        cout << "\t\t5 - WYJMIJ paczke" << endl;
        cout << "\t\t6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)" << endl;
        cout << "\t\t9 - DEMO programu paczkomat" << endl;
        cout << "\t\t0 - WYJSCIE z programu" << endl;
        cout << "\t#################################" << endl;
        cout << "\tWybierz opcje [1, 2, 3, 4, 5, 6, 9 lub 0]: ";
        
        cin >> choice;
        validChoice = (choice == '0' || choice == '1' || choice == '2' || 
                      choice == '3' || choice == '4' || choice == '5' || 
                      choice == '6' || choice == '9');
                      
        if (!validChoice) {
            system("cls");
            cout << endl << "\tNiepoprawna opcja. Mozesz wybrac tylko [1, 2, 3, 4, 5, 6, 9 lub 0]" << endl;
        }
    } while (!validChoice);
    
    system("cls");
    return choice;
}

int main() {
    cout << "Program do obslugi Paczkomatu." << endl;
    char menuChoice, confirmChoice;
    bool endProgram = false;
    unique_ptr<ParcelLocker> parcelLocker;

    do {
        menuChoice = getMenuChoice();
        
        switch (menuChoice) {
            case '1': // 1 - STWORZ paczkomat
                executeIfParcelLockerNotExists(parcelLocker, 
                    "Paczkomat juz zostal utworzony!",
                    [&]() {
                        cout << endl << "Tworze nowy paczkomat!" << endl;
                        int numSmall, numMedium, numLarge;
                        cout << "Podaj liczbe malych skrzynek: ";
                        cin >> numSmall;
                        cout << "Podaj liczbe srednich skrzynek: ";
                        cin >> numMedium;
                        cout << "Podaj liczbe duzych skrzynek: ";
                        cin >> numLarge;
                        parcelLocker = make_unique<ParcelLocker>(numSmall, numMedium, numLarge);
                        cout << "Paczkomat zostal utworzony." << endl;
                    });
                break;
            case '2': // 2 - ZNISZCZ paczkomat
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    cout << "\tCzy na pewno chcesz zniszczyc Paczkomat? [T/N]: ";
                    cin >> confirmChoice;
                    if (confirmChoice == 'T' || confirmChoice == 't') {
                        parcelLocker.reset();
                        cout << "Paczkomat zostal zniszczony." << endl;
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
                    cout << "Podaj ID skrzynki: ";
                    cin >> boxId;
                    cout << "Podaj wysokosc paczki: ";
                    cin >> height;
                    cout << "Podaj szerokosc paczki: ";
                    cin >> width;
                    cout << "Podaj dlugosc paczki: ";
                    cin >> length;
                    auto package = std::make_shared<Package>("123456789", height, width, length);
                    parcelLocker->InsertPackage(boxId, package);
                });
                break;
            case '5': // 5 - WYJMIJ paczke
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    int boxId, code;
                    cout << "Podaj ID skrzynki: ";
                    cin >> boxId;
                    cout << "Podaj kod: ";
                    cin >> code;
                    parcelLocker->RemovePackage(boxId, code);
                });
                break;
            case '6': // 6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)
                executeIfParcelLockerExists(parcelLocker, [&]() {
                    int boxId;
                    cout << "Podaj ID skrzynki: ";
                    cin >> boxId;
                    parcelLocker->GetCode(boxId);
                });
                break;
            case '9': // 9 - DEMO programu paczkomat
                executeIfParcelLockerNotExists(parcelLocker,
                    "Przed uruchomieniem DEMO zniszcz obecny paczkomat. Wybiez opcje numer 2!",
                    [&]() {
                        cout << "Wersja DEMO paczkomatu!" << endl;
                        cout << "Tworze paczkomat o ilosci skrzynek: 5-MALE, 4-SREDNIE, 3-DUZE" << endl;
                        parcelLocker = make_unique<ParcelLocker>(5, 4, 3);
                        cout << endl << "Dodaje paczke do skrzynki 2 (paczka 8x4x5 - paczka OK):";
                        auto package = std::make_shared<Package>("123456789", 8,4,5);
                        parcelLocker->InsertPackage(2,package);

                        cout << endl << "Dodaje paczke do skrzynki 6 (paczka 25x20x5 - paczka za duza):";
                        package = std::make_shared<Package>("123456789", 25,20,5);
                        parcelLocker->InsertPackage(6,package);

                        cout << endl << "Dodaje paczke do skrzynki 10 (paczka 25x20x5 - paczka OK):";
                        package = std::make_shared<Package>("123456789", 25,20,5);
                        parcelLocker->InsertPackage(10,package);

                        cout << endl << "Dodaje paczke do skrzynki 2 (paczka 9x9x10 - skrzynka zajeta):";
                        package = std::make_shared<Package>("123456789", 9,9,10);
                        parcelLocker->InsertPackage(2,package);

                        cout << endl << "Dodaje paczke do skrzynki 6 (paczka 9x9x10 - paczka OK):";
                        package = std::make_shared<Package>("123456789", 9,9,10);
                        parcelLocker->InsertPackage(6,package);
                    });
                break;
            case '0': // 0 - WYJSCIE z programu
                cout << "\tCzy na pewno chcesz zakonczyc program? [T/N]: ";
                cin >> confirmChoice;
                if (confirmChoice == 'T' || confirmChoice == 't') {
                    cout << "\tDziekuje za korzystanie z programu do obslugi Paczkomatu!" << endl;
                    endProgram = true;
                    if (parcelLocker) {
                        parcelLocker.reset();
                    }
                }
                break;
            default:
                cout << endl
                     << "\tNieobslugiwana wartosc: [" << menuChoice << "]" << endl;
        }
    } while (!endProgram);

    cout << endl; 
    system("pause"); 
    return 0;
}