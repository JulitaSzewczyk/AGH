#include <iostream>

using namespace std;

void czas(int hours, int minutes) {
	if ((hours > 0) && (hours < 25) && (minutes > 0) && (minutes < 60)) {
		cout << "Czas: " << hours << ":" << minutes;
	}
	else if ((hours > 0) && (hours < 25)) {
		cout << "Podano nieprawidlowa ilosc minut";
	}
	else if ((minutes > 0) && (minutes < 60)) {
		cout << "Podano nieprawidlowa ilosc godzin";
	}
	else {
		cout << "Podano nieprawidlowa ilosc godzin i minut";
	}
}



int main() {

	//Zadanie 1
	double tab[100];
	tab[0] = 0;
	double suma = 0;


	for (int i = 1; i < 100; i++) {
		tab[i] = tab[i - 1] + 1.2;
		//cout << " " << tab[i];
		suma = suma + tab[i];
	}

	double *wsk = &tab[11];

	cout << "12 element tablicy wynosi: " << * wsk << endl;
	cout << "Suma elementow tablicy wynosi: " << suma << endl;



	//Zadanie 2
	int liczba_godzin, liczba_minut;

	cout << "Podaj liczbe godzin i minut: ";
	cin >> liczba_godzin >> liczba_minut;

	czas(liczba_godzin, liczba_minut);
	cout << endl;



	//Zadanie 3
	struct Pizza {
		string nazwa;
		int srednica;
		double waga;
	};

	Pizza Pizza_uzytkownika;
	cout << "Podaj nazwe, srednice i waga pizzy, ktora chcesz zamowic: ";
	cin >> Pizza_uzytkownika.nazwa >> Pizza_uzytkownika.srednica >> Pizza_uzytkownika.waga;
	cout << "Podales: nazwe " << Pizza_uzytkownika.nazwa << ", srednice " << Pizza_uzytkownika.srednica << "cm, wage " << Pizza_uzytkownika.waga << "kg";


	return 0;
}