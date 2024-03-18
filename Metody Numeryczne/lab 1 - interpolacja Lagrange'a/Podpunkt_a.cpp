//dane numer 9

#include <iostream>
#include <fstream>
#include <sstream>  //do dzielenia linii na poszczególne wartości
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double podany_punkt;

vector <double> wezlyInterpolacji;
vector <double> wartosciFunkcji;


double InterpolacjaLagrangea(const vector<double>& wezlyInterpolacji, const vector<double>& wartosciFunkcji, double punkt_z_klawiatury) {

    double result = 0.0;

    for (int i = 0; i < wezlyInterpolacji.size(); i+= 5) {
        double f1 = 1.0;
        double f2 = 1.0;

        for (int j = 0; j < wezlyInterpolacji.size(); j += 5) {

            if (i != j) {
                f1 *= punkt_z_klawiatury - wezlyInterpolacji[j];
                f2 *= wezlyInterpolacji[i] - wezlyInterpolacji[j];
            }
        }
        result += wartosciFunkcji[i] * f1 / f2;


    }
    return result;
}

double SredniBladKwadratowy(double wynikiInterpolacji, const vector<double>& wartosciPoczatkowe) {
    double sredniblad = 0.0;

    for (int i = 0; i < wartosciPoczatkowe.size(); ++i) {
        double blad = wynikiInterpolacji - wartosciPoczatkowe[i];
        sredniblad += pow(blad, 2);
    }

    sredniblad /= wartosciPoczatkowe.size();

    return sqrt(sredniblad);
}

double WartoscFunkcji(double x) {
        if (x > -5 && x < 5) {
            double f1 = 1 + (x * x);
            double wynik = 1 / f1;
            return wynik;
        }
}


int main() {
    fstream plik;
    plik.open("Dane.txt", ios::in);

    if (plik.good() == false) {
        cout << "Plik nie istnieje";
        exit(0);
    }


    string linia;
    int iloscDanych = 0;

    while (getline(plik, linia) && iloscDanych < 98) {
        stringstream ss(linia);       //ss - obiekt strumienia danych     //podzielenie linii na poszczególne wartości oddzielone przecinkami
        string wartosc;

            while (getline(ss, wartosc, ',') && iloscDanych < 98) {
                double liczba = stod(wartosc);      //stod - konwersja ciągu znaków na doubla
                if (iloscDanych < 49) {
                    wezlyInterpolacji.push_back(liczba);
                }
                else {
                    wartosciFunkcji.push_back(liczba);
                }
                iloscDanych++;
            }
    }


        cout << "Podaj punkt, dla ktorego chcesz dokonac interpolacji: ";
        cin >> podany_punkt;

        double wynikInterpolacji = InterpolacjaLagrangea(wezlyInterpolacji, wartosciFunkcji, podany_punkt);
        cout << "Wynik interpolacji dla podanego punktu to: " << wynikInterpolacji << endl;
 
        double srednibladkwadrat = SredniBladKwadratowy(wynikInterpolacji, wezlyInterpolacji);    
        cout << "Sredni blad kwadratowy wynosi: " << srednibladkwadrat << endl;

        double wynikfunkcji = WartoscFunkcji(podany_punkt);
        cout << "Wartosc funkcji y = 1/(1+x^2) wynosi: " << wynikfunkcji;
        
        
 //Test wektorów
/*
        cout << "Odczytane z pliku dane i umieszczone w wektorze: ";
    for (double element : wezlyInterpolacji)     //można w ten sposób iterować sobie po elementach wektora
        cout << element << " ";
    for (double element : wartosciFunkcji)     
        cout << element << " ";
*/

        plik.close();

    return 0;
}