#include <fstream>
#include <iostream>
#include <random>
#include <list>
#include <vector>

using namespace std;

string read_input_str(const string &msg) {
    string in;
    cout << msg << endl;
    cin >> in;

    return in;
}

bool is_int(const string &str) {
    try {
        stoi(str);
    } catch (exception& e) {
        return false;
    }
    return true;
}

int read_int(const string &msg) {
    string n = read_input_str(msg);
    while (true) {
        if (is_int(n))
            return stoi(n);
        else
            cout << "Nieprawidlowa wartosc." << n << endl;
    }
}

int random_num(int p, int k) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(p, k);
    int num = dist(gen);
    return num;
}

void fill_random_2d_array(vector<vector<int>>& arr, int columns, int rows, int p, int k) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            arr[i][j] = random_num(p, k);
        }
    }
}

void print_2d_arr_matrice(vector<vector<int>>& arr, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        cout << "| ";
        for (int j = 0; j < rows; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

string arr_to_text(vector<vector<int>>& arr, int columns, int rows) {
    string text;
    for(int i = 0; i < columns; i++) {
        text += "|";
        for(int j = 0; j < rows; j++) {
            int num = arr[i][j];
            text += " ";
            text += to_string(num);
        }
        text += " |\n";
    }

    return text;
}

void open_or_create_file(const string& filename) {
    fstream file;
    try {

        if (!file) {
            printf("Plik %s nie istnieje.", filename.c_str());
            printf("Plik %s stworzony pomyslnie.", filename.c_str());
            cout << endl;
        }
        file.open(filename, ios::out);
        printf("Plik %s otwarty pomyslnie.", filename.c_str());
        cout << endl;
    }
    catch (const exception& e) {
        printf("Plik nie mogl zostac otwarty z powodu bledu %s.", e.what());
        cout << endl;
    }
    file.close();
}

list<string> open_or_create_file_and_read_to_list(const string& path) {
    list<string> lines;
    ifstream file;

    try {

        if (!file) {
            printf("Sciezka %s nie istnieje.", path.c_str());
            printf("Sciezka %s stworzona pomyslnie.", path.c_str());
            cout << endl;
        }
        file.open(path, ios::in);
        printf("Sciezka %s otwarta pomyslnie.", path.c_str());
        cout << endl;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
//          Drukuje linie tylko podczas debugowania.
            printf("Odczytana linia: %s", line.c_str());
        }
        printf("Sciezka %s odczytana pomyslnie.", path.c_str());
        cout << endl;

    }
    catch (const exception& e) {
        printf("sciezka nie mogla zostac otwarta z powodu bledu %s.", e.what());
        cout << endl;
    }
    file.close();

    return lines;
}

void open_or_create_file_and_write_text(const string& path, const string& text) {
    fstream file;
    try {
        if (!file) {
            printf("Sciezka %s nie istnieje.", path.c_str());
            printf("Sciezka %s stworzona pomyslnie.", path.c_str());
            cout << endl;
        }
        file.open(path, ios::in);
        printf("Sciezka %s otwarta pomyslnie.", path.c_str());
        cout << endl;
        file << text;
        printf("Sciezka %s nadpisana tekstem:\n%s.", path.c_str(), text.c_str());
        cout << endl;
        printf("Sciezka %s odczytana pomyslnie.", path.c_str());
        cout << endl;

    }
    catch (const exception &e) {
        printf("Plik nie mogl zostac otwarty z powodu bledu %s.", e.what());
        cout << endl;
    }

    file.close();
}

int sum_under_diagonal_verbose(vector<vector<int>>& arr, int columns) {
    int sum = 0;
    int breaker = 1;
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < breaker; j++) {
            printf(" %d ", arr[i][j]);
            sum += arr[i][j];
        }
        cout << endl;
        breaker += 1;
    }
    printf("suma: %d", sum);
    cout << endl;
    cout << endl;
    return sum;
}

void zadanie1(int columns, int rows) {
    printf("Zadanie 1");
    cout << endl << endl;
    vector<vector<int>> arr = vector<vector<int>>(columns, vector<int>(rows));
    fill_random_2d_array(arr, columns, rows, 1, 6);
    print_2d_arr_matrice(arr, rows, columns);
    cout << endl;
    string text = arr_to_text(arr, columns, rows);
    string filename = "2d_matrice.txt";
    open_or_create_file(filename);
    cout << endl;
    open_or_create_file_and_write_text(filename, text);
    cout << endl;
    sum_under_diagonal_verbose(arr, columns);
    cout << endl;
}

list<string> split_string_by_char(string& line, char delimeter) {
    list<string> parts_list;
    int end = 0;
    for(char ch : line) {
        if(ch == delimeter) {
            string part = line.substr(0, end);
            parts_list.push_back(part);
            end = 0;
        }
        end += 1;
    }

    return parts_list;
}

vector<vector<string>> write_list_to_2d_array(int columns, list<string>& lis) {
    auto workers_arr_ptr = vector<vector<string>>(columns, vector<string>(0));
    for(int i = 0; i < columns; i++) {
        for(string line : lis) {
            list<string> splitted_line = split_string_by_char(line, ' ');
            int parts_len = lis.size();
            int j = 0;
            auto entries_arr = vector<string>(parts_len, "");
            for(string& part : splitted_line) {
                entries_arr[j] = part;
                j += 1;
            }
            workers_arr_ptr[i] = entries_arr;
        }
    }
    return workers_arr_ptr;
}

void zadanie2() {
    printf("Zadanie 2");
    cout << endl << endl;
    list<string> lines = open_or_create_file_and_read_to_list("pracownicy.txt");
    int columns =  lines.size();
    auto workers_arr_ptr = write_list_to_2d_array(columns, lines);


}

int main() {
    printf("Zadanie dodatkowe - Hubert Dabrowski D5 PUW");
    cout << endl << endl;
    zadanie1(6, 6);
    zadanie2();
    return 0;
}
