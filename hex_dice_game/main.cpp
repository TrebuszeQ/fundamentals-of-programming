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

class DiceGame {
    private:
        int*** results_arr;
        int*** points_arr;
        int* winners;
        string* players_arr;
        int** records{};
        int sum_max = 0;
        int max_roll = 0;
        list<int> max_rounds;
        list<int> max_players;


        static int hex_dice_roll() {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, 6);
            int num = dist(gen);
            return num;
        }

        static int read_round_count() {
            int num = 0;

            while (num < 2 or num > 20) {
                num = read_int("Podaj liczbe tur gry.");

                if (num > 20 or num < 2) cout << "Liczba tur musi byc wieksza niz 2 i mniejsza niz 20." << endl;
            }

            return num;
        }

        void set_results() {
            for (int i = 0; i < rounds; i++) {

                for (int j = 0; j < players; j++) {
                    int sum = points_arr[i][j][0];
                    int max = results_arr[i][j][0];

                    for (int k = 0; k < rolls; k++) {
                        int roll = hex_dice_roll();
                        results_arr[i][j][k] = roll;
                        points_arr[i][j][0] += roll;

                        if(max < results_arr[i][j][k]) {
                            max = results_arr[i][j][k];
                            max_rounds.clear();
                            max_rounds.push_back(j);
                            max_players.clear();
                            max_players.push_back(i);
                        }
                        else if(max == results_arr[i][j][k]) {
                            max_rounds.push_back(j);
                            max_players.push_back(i);
                        }


                    }

                    if(sum > sum_max) {
                        sum_max = sum;
                        winners[i] = j;
                    }
                    else if (sum == sum_max) {
                        winners[i] = -2;
                    }
                }
            }
        }

    public:
        int rounds;
        int players;
        int rolls;

        DiceGame(int players, int rolls, string* players_arr) {
            this->rounds = read_round_count();
            this->players = players;
            this->rolls = rolls;
            this->players_arr = players_arr;
            this->results_arr = make_3d_array(rounds, players, rolls);
            this->points_arr = make_3d_array(rounds, players, 1);
            this->winners = new int[rounds];
            set_results();
        }

        ~DiceGame() {
            free(results_arr);
            free(points_arr);
            free(winners);
        }

        void print_records() {
            cout << endl << "Najwiecej wyrzuconych pol to " << max_roll;
            if(max_players.size() > 1) {
                for(int player : max_players) cout << " przez " << players_arr[player] << " ";
                cout << " w rundach ";

                for(int round : max_rounds) cout << round << " ";
            }
            else if (max_players.size() == 1) {
                int player = max_players.front();
                cout << " przez " << players_arr[player] << " w rundzie";

                for(int round : max_rounds) cout << round << " ";
            }
        }

        void print_results() {
            for (int i = 0; i < rounds; i++) {
                cout << endl;
                cout << "Runda " << i + 1 << ": ";
                cout << endl;

                for (int j = 0; j < players; j++) {
                    cout << players_arr[j] << ": ";

                    for (int k = 0; k < rolls; k++) {
                        cout << results_arr[i][j][k] << " ";
                    }
                    cout << "\tSuma: " << points_arr[i][j][0];
                    cout << endl;

                    if(j == players - 1) {
                        int winner = winners[i];
                        if(winner != -2) cout << "Zwyciezca rundy " <<  i << " jest: " << players_arr[winner];
                        else if(winner == -2) cout << "Remis";
                        cout << endl;
                    }

                    if(i == rounds - 1) print_records();
                }
            }
        }

};

int main() {

    cout << "Gra w rzut szescienna kostka." << endl;
    const int players = 2;
    string players_arr[players] = {"Jas", "Malgosia"};
    string* players_ptr = players_arr;

    DiceGame dice_game = DiceGame(players, 3, players_ptr);
    dice_game.print_results();

    return 0;
}


