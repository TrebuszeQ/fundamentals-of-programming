#include <iostream>
#include <random>
#include <list>

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

    while (num < 2 or num > 20) {
        num = read_int("Podaj liczbe tur gry.");

        if (num > 20 or num < 2) cout << "Liczba tur musi byc wieksza niz 2 i mniejsza niz 20." << endl;
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

void dice_game(const int rounds, const int players, const int rolls, int*** results_arr, int*** points_arr) {
    for (int i = 0; i < rounds; i++) {

        for (int j = 0; j < players; j++) {

            for (int k = 0; k < rolls; k++) {
                int num = hex_dice_roll();
                results_arr[i][j][k] = num;
                points_arr[i][j][0] += num;
            }

        }
    }
}

void print_results_array(const int rounds, const int players, const int rolls, const string* players_arr, int*** results_arr, int*** points_arr) {
    int* winners = new int[rounds];

    for (int i = 0; i < rounds; i++) {
        cout << endl;
        cout << "Runda " << i + 1 << ": ";
        cout << endl;

        for (int j = 0; j < players; j++) {
            int max_sum = 0;
            int sum = points_arr[i][j][0];
            int max = results_arr[i][j][0];
            cout << players_arr[j] << ": ";

            for (int k = 0; k < rolls; k++) {
                cout << results_arr[i][j][k] << " ";
                if(max < results_arr[i][j][k]) max = results_arr[i][j][k];
            }
            cout << "\tSuma: " << sum;
            cout << endl;

            if(sum > max_sum) {
                max_sum = sum;
                winners[i] = j;
            }
            else if (sum == max_sum) {
                winners[i] = -2;
            }

            if(j == players - 1) {
                int winner = winners[i];
                if(winner != -2) cout << "Zwyciezca rundy " <<  i << " jest: " << players_arr[winner];
                else if(winner == -2) cout << "Remis";
                cout << endl;
            }

        }
    }

    delete[] winners;
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

    string players_arr[2] = {"Jas", "Malgosia"};
    string* players_ptr = players_arr;

    int*** results_ptr = make_3d_array(rounds, players, rolls);
    int*** points_ptr = make_3d_array(rounds, players, 1);
    dice_game(rounds, players, rolls, results_ptr, points_ptr);
    print_results_array(rounds, players, rolls, players_ptr, results_ptr, points_ptr);

    delete[] results_ptr;
    delete[] points_ptr;
    return 0;
}


