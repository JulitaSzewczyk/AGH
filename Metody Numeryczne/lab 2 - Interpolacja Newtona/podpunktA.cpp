#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

vector<double> wspolczynnikiWielomianu;
vector<double> wspolrzednePunktow;


//Obliczanie wartości wielomianu zadanego w postaci naturalnej dla wartości 𝑥 
double PostacNaturalna(const vector<double>& wspolczynniki, double x) {
    double wartosc = 0;
    for (size_t i = 0; i < wspolczynniki.size(); ++i) {
        wartosc += wspolczynniki[i] * pow(x, i);
    }
    return wartosc;
}

// Obliczanie wartości wielomianu według schematu Hornera
double SchematHornera(const vector<double>& wspolczynniki, double x) {
    double wynik = 0;
    for (int i = wspolczynniki.size() - 1; i >= 0; --i) {
        wynik = wynik * x + wspolczynniki[i];
    }
    return wynik;
}



int main() {
    fstream plik;
    plik.open("DaneH.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    string linia;
    int iloscDanych = 0;

    while (getline(plik, linia) && iloscDanych <= 141) {
        stringstream ss(linia);
        string wartosc;

        while (getline(ss, wartosc, ',') && iloscDanych <= 141) {
            double liczba = stod(wartosc);
            if (iloscDanych <= 9) {
                wspolczynnikiWielomianu.push_back(liczba);
            }
            else {
                wspolrzednePunktow.push_back(liczba);
            }
            iloscDanych++;
        }
    }

    plik.close();


    for (int i = 3; i <= 10; ++i) {
        cout << "Dla wielomianu stopnia " << i << ":" << endl;
        double sumaRoznic = 0.0;
        int liczbaPunktow = 0;


        auto startNaturalna = high_resolution_clock::now();
        for (double x : wspolrzednePunktow) {
            vector<double> aktualneWspolczynniki(wspolczynnikiWielomianu.begin(), wspolczynnikiWielomianu.begin() + i);
            double wartoscNaturalna = PostacNaturalna(aktualneWspolczynniki, x);
            double wartoscHornera = SchematHornera(aktualneWspolczynniki, x);
            sumaRoznic += fabs(wartoscNaturalna - wartoscHornera);
            liczbaPunktow++;
        }
        auto stopNaturalna = high_resolution_clock::now();
        auto czasNaturalna = duration_cast<microseconds>(stopNaturalna - startNaturalna);

 
        auto startHornera = high_resolution_clock::now();
        for (double x : wspolrzednePunktow) {
            vector<double> aktualneWspolczynniki(wspolczynnikiWielomianu.begin(), wspolczynnikiWielomianu.begin() + i);
            double wartoscHornera = SchematHornera(aktualneWspolczynniki, x);
        }
        auto stopHornera = high_resolution_clock::now();
        auto czasHornera = duration_cast<microseconds>(stopHornera - startHornera);

        double sredniaRoznica = sumaRoznic / liczbaPunktow;

        cout << "Czas (postac naturalna): " << czasNaturalna.count() << "us, Czas (schemat Hornera): " << czasHornera.count() << "us" << endl;
        cout << "Srednia roznica wynikow: " << sredniaRoznica << endl;
    }



    return 0;
}
