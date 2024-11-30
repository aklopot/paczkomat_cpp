#include "paczkomat.h"
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

int main() {
	srand(time(0)); // Na potrzeby liczb pseudolosowych
    cout << "Program do obslugi Paczkomatu." << endl;
	char wyborMenu, wyborTakNie;
	bool koniecProgramu = false;
	bool paczkomat_utworzony = false;
	unique_ptr<Paczkomat> paczkomat;
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
		cin >> wyborMenu;
		system("cls");
		switch (wyborMenu) {
		case '1': // 1 - STWORZ paczkomat
            if (paczkomat_utworzony) {
				cout << endl << "Paczkomat juz zostal utworzony!" << endl;
			} else {
				cout << endl << "Tworze nowy paczkomat!" << endl;
				int ile_malych, ile_srednich, ile_duzych;
				cout << "Podaj liczbe malych skrzynek: ";
				cin >> ile_malych;
				cout << "Podaj liczbe srednich skrzynek: ";
				cin >> ile_srednich;
				cout << "Podaj liczbe duzych skrzynek: ";
				cin >> ile_duzych;
				paczkomat = make_unique<Paczkomat>(ile_malych, ile_srednich, ile_duzych);
				paczkomat_utworzony = true;
				cout << "Paczkomat zostal utworzony." << endl;
			}
			break;
		case '2': // 2 - ZNISZCZ paczkomat
			if (paczkomat_utworzony) {
				cout << "\tCzy na pewno chcesz zniszczyc Paczkomat? [T/N]: ";
				cin >> wyborTakNie;
				if (wyborTakNie == 'T' || wyborTakNie == 't') {
					paczkomat.reset();
					paczkomat_utworzony = false;
					cout << "Paczkomat zostal zniszczony." << endl;
				}
			} else {
				cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
			}
			break;
		case '3': // 3 - WYSWIETL stan paczkomatu"
			if (!paczkomat_utworzony) {
				cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
			} else {
				paczkomat->wyswietl_stan_paczkomatu();
			}
			break;
		case '4': // 4 - WLOZ paczke
			if (!paczkomat_utworzony) {
				cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
			} else {
				int ID_skrzynki;
				float wys, szer;
				cout << "Podaj ID skrzynki: ";
				cin >> ID_skrzynki;
				cout << "Podaj wysokosc paczki: ";
				cin >> wys;
				cout << "Podaj szerokosc paczki: ";
				cin >> szer;
				paczkomat->wloz_paczke(ID_skrzynki, wys, szer);
			}
			break;
        case '5': // 5 - WYJMIJ paczke
            if (!paczkomat_utworzony) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                int ID_skrzynki, kod;
                cout << "Podaj ID skrzynki: ";
                cin >> ID_skrzynki;
                cout << "Podaj kod: ";
                cin >> kod;
                paczkomat->wyjmij_paczke(ID_skrzynki, kod);
            }
            break;
        case '6': // 6 - WYSLIJ kod do skrzynki e-meilem/SMSem :)
            if (!paczkomat_utworzony) {
                cout << "Paczkomat nie zostal jeszcze utworzony! Wybierz opcje 1, aby utworzyc paczkomat." << endl;
            } else {
                int ID_skrzynki;
                cout << "Podaj ID skrzynki: ";
                cin >> ID_skrzynki;
                paczkomat->pobierz_kod(ID_skrzynki);
            }
            break;
        case '9': // 9 - DEMO programu paczkomat
            if (paczkomat_utworzony) {
                cout << "Przed uruchomieniem DEMO zniszcz obecny paczkomat. Wybiez opcje numer 2!" << endl;
            }
            else {
                cout << "Wersja DEMO paczkomatu!" << endl;
                cout << "Tworze paczkomat o ilosci skrzynek: 5-MALE, 4-SREDNIE, 3-DUZE" << endl;
                paczkomat = make_unique<Paczkomat>(5, 4, 3);
                paczkomat_utworzony = true;
                cout << endl << "Dodaje paczke do skrzynki 2 (paczka 8x4 - paczka OK):";
                paczkomat->wloz_paczke(2,8,4);

                cout << endl << "Dodaje paczke do skrzynki 6 (paczka 25x20 - paczka za duza):";
                paczkomat->wloz_paczke(6,25,20);

                cout << endl << "Dodaje paczke do skrzynki 10 (paczka 25x20 - paczka OK):";
                paczkomat->wloz_paczke(10,25,20);

                cout << endl << "Dodaje paczke do skrzynki 2 (paczka 9x9 - skrzynka zajeta):";
                paczkomat->wloz_paczke(2,9,9);

                cout << endl << "Dodaje paczke do skrzynki 6 (paczka 9x9 - paczka OK):";
                paczkomat->wloz_paczke(6,9,9);
            }
            break;
		case '0': // 0 - WYJSCIE z programu
			cout << "\tCzy na pewno chcesz zakonczyc program? [T/N]: ";
			cin >> wyborTakNie;
			if (wyborTakNie == 'T' || wyborTakNie == 't') {
				cout << "\tDziekuje za korzystanie z programu do obslugi Paczkomatu!" << endl;
				koniecProgramu = true;
				if (paczkomat_utworzony) {
					paczkomat.reset();
				}
			}
			break;
		default:
			cout << endl
				 << "\tNiepoprawna opcja. Mozez wybrac tylko [1, 2, 3, 4, 5 lub 0]"	 << endl;
		}
	} while (!koniecProgramu);
	cout << endl; system("pause"); return 0;
}
