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
        float* avg_arr;
        string* players_arr;
        int* round_winner_arr;
        int max_roll = 0;
        list<int> max_rounds;
        list<int> max_players;
        list<int> final_winners;

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
                int round_max_sum = 0;
                int round_winner = 0;

                for (int j = 0; j < players; j++) {
                    int sum = 0;
                    for (int k = 0; k < rolls; k++) {
                        int roll = hex_dice_roll();
                        set_results_arr_indice(i, j, k, roll);

                        sum = points_arr[i][j][0] += roll;
                        set_points_arr_indice(i, j, 0, sum);
                        set_avg_arr_indice(i, sum);
                        set_max_roll(i, j, roll);
                    }

                    if (sum > round_max_sum) {
                        round_max_sum = sum;
                        round_winner = j;
                    }
                    else if (sum == round_max_sum) {
                        round_winner = -2;
                    }
                }
                set_round_winner(i, round_winner);
            }

            set_avg_values();
        }

        void set_results_arr_indice(int i, int j, int k, int value) {
            results_arr[i][j][k] = value;
        }

        void set_points_arr_indice(int i, int j, int k, int value) {
            points_arr[i][j][k] = value;
        }

        void set_max_roll(int i, int j, int roll) {
            if(max_roll < roll) {
                max_roll = roll;
                max_rounds.clear();
                max_rounds.push_back(i);
                max_players.clear();
                max_players.push_back(j);
            }
            else if(max_roll == roll) {
                max_rounds.push_back(i);
                max_players.push_back(j);
            }
        }

        void set_avg_arr_indice(int i, int value) {
            avg_arr[i] += float(value);
        }

        void set_avg_values() {
            for(int i = 0; i < players; i++) {
                avg_arr[i] = avg_arr[i] / float(rounds);
            }
        }

        void set_round_winner(int i, int winner) {
            round_winner_arr[i] = winner;
        }

        void set_final_winners() {
            int* won_count = new int[rounds];
            int most_wins = 0;

            for(int i = 0; i < rounds; i++) {
                int winner = round_winner_arr[i];
                won_count[winner] += 1;
            }

            for(int i = 0; i < players; i++) {
                if(won_count[i] > most_wins) {
                    most_wins = won_count[i];
                    final_winners.clear();
                    final_winners.push_back(i);
                }
                else if(won_count[i] == most_wins) {
                    most_wins = won_count[i];
                    final_winners.clear();
                    final_winners.push_back(-2);
                }

            }
//            delete[] won_count;
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
            this->avg_arr = new float[players];
            this-> round_winner_arr = new int[rounds];
            set_results();
            set_final_winners();
        }

        ~DiceGame() {
            free(results_arr);
            free(points_arr);
            free(avg_arr);
            free(round_winner_arr);
        }

        void print_records() {
            cout << endl << "Najwiecej wyrzuconych pol wynosi " << max_roll << ", ";
            auto  iter = max_rounds.begin();

            if(max_players.size() > 1) {
                cout << "przez: " << endl;
                int i = 0;
                for(int player : max_players) {
                    advance(iter, i);
                    cout << players_arr[player] << ", " << " runda " << *iter + 1 << endl;
                    i++;
                }
            }

            else if (max_players.size() == 1) {
                int player = max_players.front();
                cout << " przez " << players_arr[player] << " w rundzie ";

                for(int round : max_rounds) cout << round << " ";
            }
        }

        void print_round_winners(int i) {
            cout << "------------------" << endl;
            int winner = round_winner_arr[i];
            if(round_winner_arr[i] == -2) cout << "Remis";
            else cout << "Zwyciezca rundy " << i + 1 << " jest: " << players_arr[winner];
            cout << endl;
        };

        void print_final_winner() {
            cout << endl << "------------------" << endl;
            cout << "Zwyciezca gry jest: " << endl;

            for(int player : final_winners) {
                if( player == -2) {
                    cout << "remis";
                    break;
                }
                else cout << players_arr[player] << " ";
            }
        }

        void print_avg_values() {
            cout << endl << "------------------" << endl;
            for (int i = 0; i < players; ++i) {
                cout << "Srednia suma pol dla gracza: " << players_arr[i] << " wynosi " << avg_arr[i] << endl;
            }
        }

        void print_results() {
            for (int i = 0; i < rounds; i++) {
                cout << endl;
                cout << "Runda " << i + 1 << ": ";
                cout << endl;

                for (int j = 0; j < players; j++) {
                    cout << players_arr[j] << endl;
                    cout << "rzuty: ";

                    for (int k = 0; k < rolls; k++) {
                        cout << results_arr[i][j][k] << " ";
                    }
                    cout << "\tSuma: " << points_arr[i][j][0];
                    cout << endl;
                }
                print_round_winners(i);

                if(i == rounds - 1)  {
                    print_records();
                }
            }

            print_final_winner();
            print_avg_values();
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


