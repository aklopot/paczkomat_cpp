#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Skrzynka {
  public:
	enum class Rozmiar { MALA, SREDNIA, DUZA };

  private:
	float wysokosc;
	float szerokosc;
	bool zajeta;
	int kod;
	Rozmiar rozmiar;
	string pobierz_rozmiar() const;
	int generuj_kod();
	

  public:
	Skrzynka(float wys, float szer, Rozmiar roz);
	bool wloz_paczke(float wys, float szer);
	bool czy_zajeta() const;
	bool sprawdz_kod(int wpisany_kod);
	void wyjmij_paczke();
	int pobierz_kod() const;
	void wyswietl_stan_skrzynki() const;
};

class Paczkomat {
  private:
	vector<unique_ptr<Skrzynka>> skrzynki;

  public:
	Paczkomat(int ile_malych, int ile_srednich, int ile_duzych);
	void wloz_paczke(int ID_skrzynki, float wys, float szer);
	void wyjmij_paczke(int ID_skrzynki, int kod);
	void wyswietl_stan_paczkomatu() const;
	void pobierz_kod(int ID_skrzynki) const;
};