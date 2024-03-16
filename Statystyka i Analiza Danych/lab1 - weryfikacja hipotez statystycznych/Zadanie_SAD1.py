#Zadanie 1
from scipy import stats

# Czas pracy bateryjek radiowych
czas = [35.34, 36.26, 30.54, 38.2, 37.59, 39.18, 33.16, 34.23, 27.9, 36.33, 32.39, 34.89, 35.7, 31.99, 34.03]

# Wartość oczekiwana
mu = 35

# Hipoteza H0 - przeciętny czas pracy bateryjek jest równy 35 (mu = 35)
# Hipoteza H1 - przeciętny czas pracy bateryjek jest różny od 35 (mu =/= 35)

# Analizujemy średnią z populacji, populacja ma rozkład normalny,
# Zbiór jest niewielki (mniejszy od 30) i nie znamy odchylenia standardowego
# Test jest parametryczny, skala ilorazowa
# Zatem wybieramy test t-studenta

# Przeprowadź test t-studenta
statystyka_T, p_wartosc = stats.ttest_1samp(czas, mu)

# Wyświetl wyniki
print("Statystyka testowa:", statystyka_T)
print("P-wartość:", p_wartosc)

# Sprawdź istotność statystyczną na poziomie alfa = 0.05
alfa = 0.05

if p_wartosc < alfa:
    print("Odrzucamy hipotezę zerową - średni czas pracy bateryjek jest różny od 35")
else:
    print("Nie ma podstaw do odrzucenia hipotezy zerowej - średni czas pracy bateryjek jest równy 35")
print("\n")


# Popełniamy tutaj błąd II rodzaju




# Zadanie 2

# Hipoteza H0: obniżenie prędkości do 17 węzłów nie zmieni zużycia paliwa bądź zużycie paliwa będzie większe niż 127.7 (mu >= 127.7)
# Hipoteza H1: obniżenie prędkości do 17 węzłów zmniejszy zużycie paliwa poniżej 127.7 (mu < 127.7)

# Analizujemy średnią z populacji, populacja ma rozkład normalny,
# Zbiór jest niewielki (mniejszy od 30) i nie znamy odchylenia standardowego
# Test jest parametryczny, skala ilorazowa
# Zatem wybieramy test t-studenta


# Zużycie paliwa po zmniejszeniu prędkości do 17 węzłów
zuzycie = [ 101.1, 105.7, 102.6, 113.4, 98.1]

# Wartość oczekiwana
mu = 127.7

# Przeprowadzenie testu t dla dwóch powiązanych próbek
t_statistic, p_wartosc = stats.ttest_1samp(zuzycie, mu, alternative='less')

# Wyświetlenie wyników testu
print("Statystyka t:", t_statistic)
print("Wartość p:", p_wartosc)


# Sprawdź istotność statystyczną na poziomie alfa = 0.01
alfa = 0.01
if p_wartosc < alfa:
    print("Odrzucamy hipotezę zerową - obniżenie prędkości do 17 węzłów nie zmniejszy zużycia paliwa.")
else:
    print("Nie ma podstaw do odrzucenia hipotezy zerowej - obniżenie prędkości do 17 węzłów zmniejszy zużycie paliwa poniżej 127.7")
print("\n")

 # Popełniamy tutaj błąd I rodzaju



# Zadanie 3

wytrzymalosc = [1.36, 1.14, 1.27, 1.15, 1.20, 1.29, 1.27, 1.18, 1.23, 1.36, 1.38, 1.37, 1.30, 1.21, 1.33, 1.28, 1.32, 1.29, 1.33, 1.25]

# Hipoteza H0: dane dotyczące wytrzymałości na ciśnienie wewnętrzne butelek układają się w rozkład normalny
# Hipoteza H1: dane dotyczące wytrzymałości na ciśnienie wewnętrzne butelek nie układają się w rozkład normalny

# Test jest nieparametryczny, skala ilorazowa
# Ponadto mamy jedną próbę
# Zatem wybieramy test Shapiro - Wilka

# Przeprowadź test Shapiro - Wilka
t_statistic, p_wartosc = stats.shapiro(wytrzymalosc)

print ("Statystyka t:", t_statistic)
print ("Wartość p:", p_wartosc)

# Sprawdź istotność statystyczną na poziomie alfa = 0.05
alfa = 0.05

if p_wartosc < alfa:
    print("Odrzucamy hipotezę zerową - dane dotyczące wytrzymałości na ciśnienie wewnętrzne butelek nie układają się w rozkład normalny.")
else:
    print("Nie ma podstaw do odrzucenia hipotezy zerowej - dane dotyczące wytrzymałości na ciśnienie wewnętrzne butelek układają się w rozkład normalny.")
print("\n")

 # Popełniamy tutaj błąd II rodzaju



# Zadanie 4

zanieczyszczenia_przed = [220, 185, 270, 285, 200, 295, 255, 190, 225, 230]
zanieczyszczenia_po = [190, 175, 215, 260, 215, 195, 260, 150, 155, 175]

# Hipoteza H0: Nie nastąpił istotny spadek emisji pyłów w zakładach szczególnie uciążliwych (mu1 = mu2)
# Hipoteza H1: Nastąpił istotny spadek emisji pyłów w zakładach szczególnie uciążliwych (mu1 > mu2)

# Analizujemy średnią z populacji, populacja ma rozkład normalny,
# Zbiór jest niewielki (mniejszy od 30) i nie znamy odchylenia standardowego
# Test jest parametryczny, skala ilorazowa
# Zatem wybieramy test t-studenta

# Przeprowadź test t-studenta
t_statistic, p_wartosc = stats.ttest_rel(zanieczyszczenia_po, zanieczyszczenia_przed, alternative = "less")

print("Statystyka t =", t_statistic)
print("p-wartosc =", p_wartosc)

# Sprawdź istotność statystyczną na poziomie alfa = 0.05
alfa = 0.05
if p_wartosc < alfa:
    print("Odrzucamy hipotezę zerową - nastąpił istotny spadek emisji pyłów w zakładach szczególnie uciążliwych.")

else:
    print("Nie ma podstaw do odrzucenia hipotezy zerowej - nie nastąpił istotny spadek emisji pyłów w zakładach szczególnie uciążliwych")
print("\n")

 # Popełniamy tutaj błąd I rodzaju