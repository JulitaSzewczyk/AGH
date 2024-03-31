#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector <double> wartoscX;
vector <double> wartoscY;

vector<double> ObliczRozniceDzielone(const vector<double>& wartoscX, const vector<double>& wartoscY, int n) {
    vector<vector<double>> tabela(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        tabela[i][0] = wartoscY[i];
    }
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            tabela[i][j] = (tabela[i + 1][j - 1] - tabela[i][j - 1]) / (wartoscX[i + j] - wartoscX[i]);
        }
    }
    vector<double> wspolczynniki(n);
    for (int i = 0; i < n; ++i) {
        wspolczynniki[i] = tabela[0][i];
    }
    return wspolczynniki;
}

double WartoscWielomianuNewtona(const vector<double>& wspolczynniki, const vector<double>& wartoscX, double x, int n) {
    double wynik = wspolczynniki[0];
    for (int i = 1; i < n; ++i) {
        double iloczyn = 1;
        for (int j = 0; j < i; ++j) {
            iloczyn *= (x - wartoscX[j]);
        }
        wynik += wspolczynniki[i] * iloczyn;
    }
    return wynik;
}

double ObliczMSE(const vector<double>& obliczoneY, const vector<double>& oczekiwaneY) {
    double suma = 0;
    for (size_t i = 0; i < obliczoneY.size(); ++i) {
        suma += pow(obliczoneY[i] - oczekiwaneY[i], 2);
    }
    return suma / obliczoneY.size();
}

int main() {
    fstream plik;
    plik.open("DaneN.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    vector<double> wartosciX;
    vector<double> wartosciY;

    string linia;
    int iloscDanych = 0;

    while (getline(plik, linia) && iloscDanych < 210) {
        stringstream ss(linia);
        string wartosc;

        while (getline(ss, wartosc, ',') && iloscDanych < 210) {
            double liczba = stod(wartosc);
            if (iloscDanych < 105) {
                wartoscX.push_back(liczba);
            }
            else {
                wartoscY.push_back(liczba);
            }
            iloscDanych++;
        }
    }
    plik.close();




    int n = wartoscX.size() / 5; 
    vector<double> wybraneX, wybraneY;
    for (int i = 0; i < n; ++i) {
        wybraneX.push_back(wartoscX[i * 5]);
        wybraneY.push_back(wartoscY[i * 5]);
    }

    vector<double> wspolczynniki = ObliczRozniceDzielone(wybraneX, wybraneY, n);


    cout << "Wspolczynniki wielomianu Newtona:" << endl;
    for (size_t i = 0; i < wspolczynniki.size(); ++i) {
        cout << "a" << i << ": " << wspolczynniki[i] << endl;
    }

//   cout << "Podaj wartosc x: ";
//   double x;
//    cin >> x;

//    double wynik = WartoscWielomianuNewtona(wspolczynniki, wybraneX, x, n);
//   cout << "Wartosc wielomianu Newtona dla x = " << x << " wynosi: " << wynik << endl;

    vector<double> obliczoneY;
    for (double xi : wartoscX) {
        obliczoneY.push_back(WartoscWielomianuNewtona(wspolczynniki, wybraneX, xi, n));
    }

    double mse = ObliczMSE(obliczoneY, wartoscY);
    cout << "MSE = " << mse << endl;


    int ilePunktow;
    cout << "Podaj ilosc punktow do porownania: ";
    cin >> ilePunktow;

    ilePunktow = min(ilePunktow, static_cast<int>(wartoscX.size()));

    for (int i = 0; i < ilePunktow; ++i) {
        double yNew = WartoscWielomianuNewtona(wspolczynniki, wybraneX, wartoscX[i], n);
        cout << "x = " << wartoscX[i] << ", wartosc z Newtona: " << yNew << ", wartosc rzeczywista: " << wartoscY[i] << ", blad: " << abs(yNew - wartoscY[i]) << endl;
    }

    return 0;
}
