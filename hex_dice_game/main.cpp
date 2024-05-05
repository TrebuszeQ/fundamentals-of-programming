#include <iostream>
#include <random>


using namespace std;

string read_input_str(const string& msg) {
    string in;
    cout << msg << endl;
    cin >> in;

    return in;
}

bool is_int(const string& str) {
    try { stoi(str); }
    catch (exception e) { return false; }
    return true;
}

int read_int(const string& msg) {
    string n = read_input_str(msg);
    while (true) {
        if (is_int(n)) return stoi(n);
        else cout << "Nieprawidlowa wartosc." << n << endl;
    }
}

int read_round_count() {
    int num = 0;

    while (num > 20 or num < 2) {
        int num = read_int("Podaj liczbe tur gry.");
        if (num < 2 or num > 20) cout << "Liczba tur musi byc wieksza niz 2 i mniejsza niz 20.";
    }

    return num;
}

int hex_dice_roll() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 6);
    int num = dist(gen);
    return num;
}

void dice_game(const int rounds, const int players, const int rolls, int*** results_arr, int*** winners_arr) {
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < players; j++) {
            for (int k = 0; k < rolls; k++) {
                int num = hex_dice_roll();
                results_arr[i][j][k] = num;
                winners_arr += results_arr[i][j][k];
            }
        }
    }
}

void print_results_array(const int rounds, const int players, const int rolls, int*** results_arr, int*** winners_arr) {
    for (int i = 0; i < rounds; i++) {
        cout << endl;
        cout << "Runda " << i + 1 << ": ";
        cout << endl;

        for (int j = 0; j < players; j++) {
            if (j == 0) cout << "\tJas " << ": ";
            else if (j == 1) cout << "\tMalgosia " << ": ";
//            cout << "Gracz " << j + 1 << ": ";

            for (int k = 0; k < rolls; k++) {
                cout << results_arr[i][j][k] << " ";
            }
            cout << "\tSuma: " << winners_arr[i][j][0];
            cout << endl;
        }
    }

}

int*** make_3d_array(int rows, int columns, int depth) {
    int*** arr = new int**[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int*[columns];
        for (int j = 0; j < columns; j++) {
            arr[i][j] = new int[depth];
        }
    }

    return arr;
}

int main() {

    cout << "Gra w rzut szescienna kostka." << endl;
    const int rounds = read_round_count();
    const int players = 2;
    const int rolls = 3;

    int*** results_ptr = make_3d_array(rounds, players, rolls);
    int*** winners_ptr = make_3d_array(rounds, players, 1);
    dice_game(rounds, players, rolls, results_ptr);
    print_results_array(rounds, players, rolls, results_ptr);

    delete results_ptr;
    return 0;
}


