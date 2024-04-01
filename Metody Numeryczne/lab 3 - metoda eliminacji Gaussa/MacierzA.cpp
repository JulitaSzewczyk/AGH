#include <iostream>
#include <fstream>
#include <sstream>  
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>  //do ładnego wyprintowania wartości

using namespace std;

vector<double> wspolczynnikRownania;
vector<double> wyrazWolny;
vector<double> rozwiazania;
vector<int> indeksy;
int n;


void WypiszMacierz(const vector<double>& A, const vector<double>& B, int n) {
    for (int wiersz = 0; wiersz < n; wiersz++) {
        for (int kolumna = 0; kolumna < n; kolumna++) {
            cout << setw(8) << fixed << setprecision(4) << A[wiersz * n + kolumna] << '\t';    //wypisuje tylko 4 liczby po przecinku, żeby wartości się nie rozjeżdżały
        }                                                                                       //i żeby łatwiej się analizowało wynik
        cout << "| " << setw(8) << fixed << setprecision(4) << B[wiersz] << endl;
    }
    cout << endl;
}

void ObliczWynik(const vector<double>& A, const vector<double>& B, vector<double>& x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = B[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i * n + j] * x[j];
        }
        x[i] /= A[i * n + i];
    }
}

//A[i][k] - element do wyzerowania
//A[k][k] - element prowadzący
void MetodaEliminacjiGaussa(vector<double>& A, vector<double>& B, vector<double>& x, int n) {
    for (int k = 0; k < n - 1; k++) {

        int maxIndex = k;
        double maxValue = abs(A[k * n + k]);
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i * n + k]) > maxValue) {
                maxValue = abs(A[i * n + k]);
                maxIndex = i;
            }
        }
        if (k != maxIndex) {
            for (int j = 0; j < n; j++) {
                swap(A[k * n + j], A[maxIndex * n + j]);
            }
            swap(B[k], B[maxIndex]);
        }

        for (int i = k + 1; i < n; i++) {
            double factor = A[i * n + k] / A[k * n + k];
            for (int j = k; j < n; j++) {
                A[i * n + j] -= factor * A[k * n + j];
            }
            B[i] -= factor * B[k];
        }
        cout << "Macierz po kroku " << k + 1 << ":" << endl;
        WypiszMacierz(A, B, n);
    }


    // Sprawdzamy, czy gdzieś po drodze się nie wyzerowało
    if (abs(A[(n - 1) * n + (n - 1)]) < 1e-10 && abs(B[n - 1]) < 1e-10) {
        cout << "Liniowa zaleznosc wektorow. Rownanie ma nieskonczenie wiele rozwiazan." << endl;
        return;
    }
    else if (abs(A[(n - 1) * n + (n - 1)]) < 1e-10 && abs(B[n - 1]) > 1e-10) {
        cout << "Liniowa zaleznosc wektorow. Rownanie jest sprzeczne." << endl;
        return;
    }

    ObliczWynik(A, B, x, n);
}

bool SprawdzRozwiazania(const vector<double>& A, const vector<double>& B, const vector<double>& x, int n) {
    const double tolerancja = 1e-4;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += A[i * n + j] * x[j];
        }
        if (abs(sum - B[i]) > tolerancja) { 
            return false;
        }
    }
    return true;
}

int main() {
    fstream plik;
    plik.open("DaneGA.txt", ios::in);

    if (!plik.good()) {
        cout << "Plik nie istnieje";
        exit(0);
    }

    string linia;
    int iloscDanych = 0;

    while (getline(plik, linia) && iloscDanych < 31) {
        stringstream ss(linia);
        string wartosc;

        while (getline(ss, wartosc, ',') && iloscDanych < 31) {
            double liczba = stod(wartosc);
            if (iloscDanych == 0) {
                n = liczba;
                rozwiazania.resize(n);

                indeksy.resize(n);
                for (int i = 0; i < n; i++) {
                    indeksy[i] = i;
                }
            }

            else if (iloscDanych < 6) {
                wyrazWolny.push_back(liczba);
            }
            else {
                wspolczynnikRownania.push_back(liczba);
            }
            iloscDanych++;
        }
    }
    plik.close();

    cout << "Macierz podstawowa: " << endl;
    WypiszMacierz(wspolczynnikRownania, wyrazWolny, n);
    MetodaEliminacjiGaussa(wspolczynnikRownania, wyrazWolny, rozwiazania, n);

    cout << "Rozwiazania rownania: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << indeksy[i] + 1 << "] = " << setw(8) << fixed << setprecision(4) << rozwiazania[i] << endl;
    }

    if (SprawdzRozwiazania(wspolczynnikRownania, wyrazWolny, rozwiazania, n)) {
        cout << "Rozwiazania zostaly obliczone prawidlowo" << endl;
    }
    else {
        cout << "Rozwiazania zostaly obliczone nieprawidlowo" << endl;
    }


    return 0;
}


//Test wektorów
/*cout << n << endl;

for (double element : wyrazWolny)
    cout << element << " ";

for (double element : wspolczynnikRownania)
    cout << element << " ";
*/