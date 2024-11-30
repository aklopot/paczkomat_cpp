#include "paczkomat.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

int main() {
    srand(time(0)); // Na potrzeby liczb pseudolosowych
    cout << "Program do obslugi Paczkomatu." << endl;
    char menuChoice, confirmChoice;
    bool endProgram = false;
    bool isParcelLockerCreated = false;
    unique_ptr<ParcelLocker> parcelLocker;
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
        cout << "\tWybierz opcje [1, 2, 3, 4, 5 lub 0]: ";
        cin >> menuChoice;
        system("cls");
        switch (menuChoice) {
        case '1': // 1 - STWORZ paczkomat
            if (isParcelLockerCreated) {
                cout << endl << "Paczkomat juz zostal utworzony!" << endl;
            } else {
                cout << endl << "Tworze nowy paczkomat!" << endl;
                int numSmall, numMedium, numLarge;
                cout << "Podaj liczbe malych skrzynek: ";
                cin >> numSmall;
                cout << "Podaj liczbe srednich skrzynek: ";
                cin >> numMedium;
                cout << "Podaj liczbe duzych skrzynek: ";
                cin >> numLarge;
                parcelLocker = make_unique<ParcelLocker>(numSmall, numMedium, numLarge);
                isParcelLockerCreated = true;
                cout << "Paczkomat zostal utworzony." << endl;
            }
            break;
        case '2': // 2 - ZNISZCZ paczkomat
            if (isParcelLockerCreated) {
                cout << "\tCzy na pewno chcesz zniszczyc Paczkomat? [T/N]: ";
                cin >> confirmChoice;
                if (confirmChoice == 'T' || confirmChoice == 't') {
                    parcelLocker.reset();
                    isParcelLockerCreated = false;
                    cout << "Paczkomat zostal zniszczony." << endl;
                }
            } else {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            }
            break;
        case '3': // 3 - WYSWIETL stan paczkomatu"
            if (!isParcelLockerCreated) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                parcelLocker->DisplayLockerStatus();
            }
            break;
        case '4': // 4 - WLOZ paczke
            if (!isParcelLockerCreated) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                int boxId;
                float height, width;
                cout << "Podaj ID skrzynki: ";
                cin >> boxId;
                cout << "Podaj wysokosc paczki: ";
                cin >> height;
                cout << "Podaj szerokosc paczki: ";
                cin >> width;
                parcelLocker->InsertPackage(boxId, height, width);
            }
            break;
        case '5': // 5 - WYJMIJ paczke
            if (!isParcelLockerCreated) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                int boxId, code;
                cout << "Podaj ID skrzynki: ";
                cin >> boxId;
                cout << "Podaj kod: ";
                cin >> code;
                parcelLocker->RemovePackage(boxId, code);
            }
            break;
        case '6': // 6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)
            if (!isParcelLockerCreated) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                int boxId;
                cout << "Podaj ID skrzynki: ";
                cin >> boxId;
                parcelLocker->GetCode(boxId);
            }
            break;
        case '9': // 9 - DEMO programu paczkomat
            if (isParcelLockerCreated) {
                cout << "Przed uruchomieniem DEMO zniszcz obecny paczkomat. Wybiez opcje numer 2!" << endl;
            }
            else {
                cout << "Wersja DEMO paczkomatu!" << endl;
                cout << "Tworze paczkomat o ilosci skrzynek: 5-MALE, 4-SREDNIE, 3-DUZE" << endl;
                parcelLocker = make_unique<ParcelLocker>(5, 4, 3);
                isParcelLockerCreated = true;
                cout << endl << "Dodaje paczke do skrzynki 2 (paczka 8x4 - paczka OK):";
                parcelLocker->InsertPackage(2,8,4);

                cout << endl << "Dodaje paczke do skrzynki 6 (paczka 25x20 - paczka za duza):";
                parcelLocker->InsertPackage(6,25,20);

                cout << endl << "Dodaje paczke do skrzynki 10 (paczka 25x20 - paczka OK):";
                parcelLocker->InsertPackage(10,25,20);

                cout << endl << "Dodaje paczke do skrzynki 2 (paczka 9x9 - skrzynka zajeta):";
                parcelLocker->InsertPackage(2,9,9);

                cout << endl << "Dodaje paczke do skrzynki 6 (paczka 9x9 - paczka OK):";
                parcelLocker->InsertPackage(6,9,9);
            }
            break;
        case '0': // 0 - WYJSCIE z programu
            cout << "\tCzy na pewno chcesz zakonczyc program? [T/N]: ";
            cin >> confirmChoice;
            if (confirmChoice == 'T' || confirmChoice == 't') {
                cout << "\tDziekuje za korzystanie z programu do obslugi Paczkomatu!" << endl;
                endProgram = true;
                if (isParcelLockerCreated) {
                    parcelLocker.reset();
                }
            }
            break;
        default:
            cout << endl
                 << "\tNiepoprawna opcja. Mozez wybrac tylko [1, 2, 3, 4, 5 lub 0]"	 << endl;
        }
    } while (!endProgram);
    cout << endl; system("pause"); return 0;
}