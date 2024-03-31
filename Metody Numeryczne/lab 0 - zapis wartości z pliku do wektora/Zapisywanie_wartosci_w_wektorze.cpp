#include <iostream>
#include <fstream>
#include <sstream>  //do dzielenia linii na poszczególne wartości
#include <string>
#include <vector>

using namespace std;

vector <double> wezlyInterpolacji;
vector <double> wartosciFunkcji;


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

    plik.close();


    //Test wektorów
    cout << "Odczytane z pliku dane i umieszczone w wektorze: ";
    for (double element : wezlyInterpolacji)     //można w ten sposób iterować sobie po elementach wektora
        cout << element << " ";
    for (double element : wartosciFunkcji)
        cout << element << " ";

    return 0;
}