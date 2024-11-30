#include "paczkomat.h"

// Implementacja klasy Skrzynka

Skrzynka::Skrzynka(float wys, float szer, Rozmiar roz)
	: wysokosc(wys), szerokosc(szer), zajeta(false), kod(0), rozmiar(roz) {}

// Funkcja prywatne klasy Skrzynka

string Skrzynka::pobierz_rozmiar() const {
    switch (rozmiar) {
        case Rozmiar::MALA: return "Mala";
        case Rozmiar::SREDNIA: return "Srednia";
        case Rozmiar::DUZA: return "Duza";
        default: return "Nieznany";
    }
}

int Skrzynka::generuj_kod() {
    return rand() % 900000 + 100000;
}

// Funkcje publiczne dlasy Skrzynka

bool Skrzynka::wloz_paczke(float wys, float szer) {
    if (zajeta) {
        cout << endl << "Skrzynka jest juz zajeta!" << endl;
        return false;
    }
    if (wys <= wysokosc && szer <= szerokosc) {
        zajeta = true;
        kod = generuj_kod();
        cout << endl << "Do skrzynki o rozmiarze " << pobierz_rozmiar() << " [" << wysokosc << "x" << szerokosc << "] pomyslenie wlozono paczke o rozmiarze: " << wys << "x" << szer << endl;
        cout << "Kod do otwarcia: " << kod << endl;
        return true;
    } else {
        cout << endl << "W skrzynce o rozmarze " << pobierz_rozmiar() << " [" << wysokosc << "x" << szerokosc << "] nie miesci sie paczka o rozmarze " << wys << "x" << szer << "!" << endl;
        return false;
    }
}

bool Skrzynka::czy_zajeta() const {
    return zajeta;
}

bool Skrzynka::sprawdz_kod(int wpisany_kod) {
    return kod == wpisany_kod;
}

void Skrzynka::wyjmij_paczke() {
    if (zajeta) {
        zajeta = false;
        kod = 0;
        cout << "Paczka pomyslnie wyjeta ze skrzynki o rozmiarze " << pobierz_rozmiar() << endl;
    } else {
        cout << "Skrzynka jest pusta!" << endl;
    }
}

int Skrzynka::pobierz_kod() const {
    if (zajeta) {
        return kod;
    } else {
        // Kod -1 oznacza, że skrzynka jest pusta
        return -1;
    }
}

void Skrzynka::wyswietl_stan_skrzynki() const {
    cout << "Rozmiar: " << pobierz_rozmiar() << ", Wysokosc: " << wysokosc << ", Szerokosc: " << szerokosc
         << ", Zajeta: " << (zajeta ? "TAK" : "NIE") << endl;
}

// Implementacja klasy Paczkomat

Paczkomat::Paczkomat(int ile_malych, int ile_srednich, int ile_duzych) {
	for (int i = 0; i < ile_malych; ++i) {
		skrzynki.push_back(make_unique<Skrzynka>(10, 10, Skrzynka::Rozmiar::MALA));
	}
	for (int i = 0; i < ile_srednich; ++i) {
		skrzynki.push_back(make_unique<Skrzynka>(20, 20, Skrzynka::Rozmiar::SREDNIA));
	}
	for (int i = 0; i < ile_duzych; ++i) {
		skrzynki.push_back(make_unique<Skrzynka>(30, 30, Skrzynka::Rozmiar::DUZA));
	}
}

// Funkcje publiczne klasy Paczkomat

void Paczkomat::wloz_paczke(int ID_skrzynki, float wys, float szer) {
    if (ID_skrzynki <= 0 || ID_skrzynki > (int)skrzynki.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    ID_skrzynki--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    skrzynki[ID_skrzynki]->wloz_paczke(wys, szer);
}

void Paczkomat::wyjmij_paczke(int ID_skrzynki, int kod) {
    if (ID_skrzynki <= 0 || ID_skrzynki > (int)skrzynki.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    ID_skrzynki--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    if (skrzynki[ID_skrzynki]->czy_zajeta() && skrzynki[ID_skrzynki]->sprawdz_kod(kod)) {
        skrzynki[ID_skrzynki]->wyjmij_paczke();
    } else {
        cout << "Niepoprawny kod lub skrzynka jest pusta!" << endl;
    }
}

void Paczkomat::wyswietl_stan_paczkomatu() const {
    for (size_t i = 0; i < skrzynki.size(); ++i) {
        cout << "Skrzynka " << i+1 << ": ";
        skrzynki[i]->wyswietl_stan_skrzynki();
    }
}

void Paczkomat::pobierz_kod(int ID_skrzynki) const {
    if (ID_skrzynki <= 0 || ID_skrzynki > (int)skrzynki.size()) {
        cout << "Niepoprawny numer skrzynki!" << endl;
        return;
    }
    ID_skrzynki--; // Odejmuje do 1 od numeru skrzynki na potrzeby numeracji vectora
    if (skrzynki[ID_skrzynki]->czy_zajeta()) {
        cout << "Wysylam kod e-mailem/SMSem :)" << endl;
        cout << "Kod do skrzynki " << ID_skrzynki+1 << ": " << skrzynki[ID_skrzynki]->pobierz_kod() << endl;
    } else {
        cout << "Skrzynka jest pusta!" << endl;
    }
}