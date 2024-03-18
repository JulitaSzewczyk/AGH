//dane numer 9

#include <iostream>
#include <fstream>
#include <sstream>  //do dzielenia linii na poszczególne warto?ci
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector <double> wezlyInterpolacji;
vector <double> wartosciFunkcji;

double InterpolacjaLagrangea(const vector<double>& wezlyInterpolacji, const vector<double>& wartosciFunkcji, double punkt_z_klawiatury) {
    double result = 0.0;

    for (int i = 0; i < wezlyInterpolacji.size(); ++i) {
        double f1 = 1.0;
        double f2 = 1.0;

        for (int j = 0; j < wezlyInterpolacji.size(); ++j) {

            if (i != j) {
                f1 *= punkt_z_klawiatury - wezlyInterpolacji[j];
                f2 *= wezlyInterpolacji[i] - wezlyInterpolacji[j];
            }
        }
        result += wartosciFunkcji[i] * f1 / f2;


    }
    return result;
}

void Funkcja(const double poczatek, const double koniec, const int iloscDanych, vector<double>& wezlyInterpolacji, vector<double>& wartosciFunkcji) {
    double krok = (koniec - poczatek) / (iloscDanych);
    for (int i = 0; i <= iloscDanych; ++i) {
        double x = poczatek + i * krok;
        double y = 1 / (1 + x * x);
        wezlyInterpolacji.push_back(x);
        wartosciFunkcji.push_back(y);
    }
}

int main() {
    const double poczatek = -5.0;
    const double koniec = 5.0;
    int ilePunktow;

    cout << "Podaj ilosc punktow: ";
    cin >> ilePunktow;

    Funkcja(poczatek, koniec, ilePunktow, wezlyInterpolacji, wartosciFunkcji);

    int ilePunktowTestowych = ilePunktow * 4;

    double nowyKrok = (koniec - poczatek) / ilePunktowTestowych;

    for (int i = 0; i <= ilePunktowTestowych; i++) {
        double x = poczatek + i * nowyKrok;
        double y = 1 / (1 + x * x);

        double yLan = InterpolacjaLagrangea(wezlyInterpolacji, wartosciFunkcji, x);
        cout << "x = " << x << ", wartosc z Lagrangea: " << yLan << ", wartosc rzeczywista: " << y << ", blad: " << abs(yLan - y) << endl;
    }

    return 0;
}
