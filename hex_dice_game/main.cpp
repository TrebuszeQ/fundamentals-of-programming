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
    int num = read_int("Podaj liczbe tur gry.");
    return num;
}

int hex_dice_roll() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 6);
    int num = dist(gen);
    return num;
}

void dice_game(const int rounds, const int players, const int rolls, int results_arr[rounds][players][rolls]) {
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < players; j++) {
            for (int k = 0; k < rolls; k++) {
                int num = hex_dice_roll();
                results_arr[i][j][k] = num;
            }
        }
    }
}

void print_results_array(const int rounds, const int players, const int rolls, int results_arr[rounds][players][rolls]) {
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < players; j++) {
            cout << "Gracz " << j + 1 << ", runda " << i + 1 << ": ";
            for (int k = 0; k < rolls; k++) {
                cout << results_arr[i][j][k] << " ";
            }
            cout << endl;
        }
    }

}

int main() {

    cout << "Gra w rzut szescienna kostka." << endl;
    const int rounds = read_round_count();
    const int players = 2;
    const int rolls = 3;

    int* results_ptr[rounds][players][rolls];
    int results[rounds][players][rolls];
//    int* results_ptr2 = new int[rounds][players][rolls];
    dice_game(rounds, players, rolls, results);
    print_results_array(rounds, players, rolls, results);
    return 0;
}


