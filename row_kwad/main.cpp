#include <iostream>
#include <cmath>

using namespace std;

// funkcja wyswietla wiadomosc i przyjmuje wartosc in
string odczytaj_str(string message) {
    string in = "";
    cout << message << endl;
    cin >> in;

    return in;
}


// funkcja sprawdza czy str jest liczba calkowita
bool jest_int(string str) {
    try {
        stoi(str);
    }

    catch (exception e) {
        return false;
    }

    return true;
}


// funkcja sprawdza czy argument int jest ujemny
bool jest_int_ujemny(int arg) {
    if (arg >= 0) return false;
    else return true;
}


// program wczytuje nieujemna liczbe calkowita.
int odczytaj_int_pozytywny(string message) {
    string n;

    while (true) {
        string n = odczytaj_str(message);

        if (jest_int(n)) {
            int n_int = stoi(n);

            if (!jest_int_ujemny(n_int)) return n_int;
            else printf("Liczba %i jest ujemna.\n", n_int);
        }

        else cout << ("Wprowadzona wartosc nie jest prawidlowa.\n");
    }

    return -1;
}


// sprawdza czy argument jest liczba zmiennoprzecinkowa
bool jest_flt(string str) {
    try {
        stof(str);
    }

    catch (exception e) {
        return false;
    }

    return true;
}


// odczytuje i zwraca zmienna typu float
float odczytaj_flt(string message) {
    string n;
    bool truth = false;

    cout << message;

    do {
        cin >> n;

        if (!jest_flt(n)) cout << "Wprowadzona wartosc nie jest prawidlowa.\n";
        else truth = true;

    } while(!truth);

    return stof(n);
}


// oblicza rownanie kwadratowe i wyswietla miejsca zerowe
bool row_kwad(float a, float b, float c) {
    float d = b * b - 4.0 * (a * c);

    printf("Delta wynosi: %0.2f.\n", d);

    if (a == 0) {
        cout << "Jest to rownanie liniowe, a nie moze wynosic 0.\n";
        return false;
    }


    if (d < 0) {
        cout << "Funkcja kwadratowa nie ma miejsc zerowych.\n";
        return false;
    }

    else if (d == 0) {
        float x1 = -(b/(2*a));
        printf("Funkcja ma jedno miejsce zerowe: %0.2f.\n", x1);
        return true;
    }

    else {
        float x1 = ((-b + sqrt(d))/(2.0*a));
        float x2 = ((-b - sqrt(d))/(2.0*a));
        printf("Funkcja ma dwa miejsca zerowe: %0.2f, oraz %0.2f.\n", x1, x2);
        return true;
    }
}


int main() {
    int opt = 0;

    while (opt != 2) {
        cout << endl;
        cout << "1. Rownanie kwadratowe.\n";
        cout << "2. Wyjscie.\n";
        cout << endl;

        opt = odczytaj_int_pozytywny("Wprowadz numer opcji [typu calkowitego].\n");

        if (opt == 1) row_kwad(odczytaj_flt("Wprowadz wartosc wspolczynnika a [typu float].\n"), odczytaj_flt("Wprowadz wartosc wspolczynnika b [typu float].\n"), odczytaj_flt("Wprowadz wartosc wspolczynnika c [typu float].\n"));

        else if (opt == 2) return 0;
    }

    return 0;
}
