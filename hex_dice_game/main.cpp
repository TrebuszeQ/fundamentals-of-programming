#include <iostream>
#include <random>
#include <list>
#include <utility>
#include <vector>

using namespace std;

string read_input_str(const string& msg) {
    string in;
    cout << msg << endl;
    cin >> in;

    return in;
}

bool is_int(const string& str) {
    try { stoi(str); }
    catch (exception &e) {
        return false;
    }
    return true;
}

int read_int(const string& msg) {
    string n = read_input_str(msg);
    while (true) {
        if (is_int(n)) {
            return stoi(n);
        }
        else cout << "Nieprawidlowa wartosc." << n << endl;
    }
}

class DiceGame {
private:
    vector<vector<vector<int>>> results_arr;
    vector<vector<vector<int>>> points_arr;
    int max_roll = 0;
    list<int> round_winner_list;
    list<int> max_rounds;
    list<int> players_max_roll;
    list<int> final_winners;
    vector<double> avg_arr;
    vector<int> won_count;

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
                    set_points_arr_indice(i, j, sum);
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
            set_round_winner(round_winner);
        }

        set_avg_values();
    }

    void set_results_arr_indice(int i, int j, int k, int value) {
        results_arr[i][j][k] = value;
    }

    void set_points_arr_indice(int i, int j, int value) {
        points_arr[i][j][0] = value;
    }

    void set_max_roll(int i, int j, int roll) {
        if(max_roll < roll) {
            max_roll = roll;
            max_rounds.clear();
            max_rounds.push_back(i);
            players_max_roll.clear();
            players_max_roll.push_back(j);
        }
        else if(max_roll == roll) {
            max_rounds.push_back(i);
            players_max_roll.push_back(j);
        }
    }

    void set_avg_arr_indice(int i, int value) {
        avg_arr[i] += value;
    }

    void set_avg_values() {
        for(double& avg : avg_arr) {
            avg /= rounds;
        }
    }

    void set_round_winner(int winner) {
        round_winner_list.push_back(winner);
    }

    void set_final_winners() {

        int most_wins = 0;

        for(int i = 0; i < rounds - 1; i++) {
            int winner = get_int_list_element(i, round_winner_list);
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
    }

public:
    const int rounds = read_round_count();
    int rolls;
    int players;
    vector<string> players_arr;

    explicit DiceGame(int players, vector<string> players_arr, int rolls) {
        this->rolls = rolls;
        this->players_arr = std::move(players_arr);
        this->players = players;
        this->points_arr = vector<vector<vector<int>>>(rounds, vector<vector<int>>(players, vector<int>(1)));
        this->results_arr = vector<vector<vector<int>>>(rounds, vector<vector<int>>(players, vector<int>(rolls)));
        this->avg_arr = vector<double>(players, 0.0);
        this->won_count = vector<int>(players, 0);
        set_results();
        set_final_winners();
    }

    ~DiceGame() = default;

    static int get_int_list_element(int i, const list<int>& list) {
        auto iter = list.begin();
        advance(iter, i);
        return *iter;
    }

    void print_records() {
        cout << endl << "Najwiecej wyrzuconych pol wynosi " << max_roll << ", ";
        if(players_max_roll.size() > 1) {
            cout << "przez: " << endl;
            for(int i = 0; i < players_max_roll.size(); i++) {
                int player = get_int_list_element(i, players_max_roll);
                cout << players_arr[player] << ", " << " runda " << i + 1 << endl;
            }
        }

        else if (players_max_roll.size() == 1) {
            int player = players_max_roll.front();
            cout << " przez " << players_arr[player] << " w rundzie ";

            for(int round : max_rounds) cout << round << " ";
        }
    }

    void print_round_winners(int i) {
        cout << "------------------" << endl;
        int winner = get_int_list_element(i, round_winner_list);
        if(winner == -2) cout << "Remis";
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
    const vector<string> players_arr = {"Jas", "Malgosia"};
    DiceGame dice_game = DiceGame(players, players_arr, 3);
    dice_game.print_results();
    exit(0);
}