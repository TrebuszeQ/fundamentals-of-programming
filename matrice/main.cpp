#include <fstream>
#include <iostream>
#include <random>
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
    } catch (exception e) {
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

int **make_2d_array(int rows, int columns) {
    int **arr = new int *[rows];
    for (int i = 0; i < rows - 1; i++) {
        arr[i] = new int[columns];
    }

    return arr;
}

int random_num(int p, int k) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(p, k);
    int num = dist(gen);
    return num;
}

int **fill_random_2d_array(int **arr, int rows, int columns, int p, int k) {
    for (int i = 0; i < columns - 1; i++) {
        for (int j = 0; j < rows - 1; j++) {
            arr[i][j] = random_num(p, k);
        }
    }

    return arr;
}

void print_2d_arr_matrice(int **arr, int columns, int rows) {
    for (int i = 0; i < columns - 1; i++) {
        cout << " | ";
        for (int j = 0; j < rows - 1; j++) {
            cout << arr[i][j] << " ";
        }
        cout << " | " << endl;
    }
}

string print_2d_arr_matrice(int **arr, int columns, int rows) {
    string text = "";
    for (int i = 0; i < columns - 1; i++) {
        text + " | ";
        for (int j = 0; j < rows - 1; j++) {
            text + stoi(arr[i][j]) + " ";
        }
        cout << " | " << endl;
    }
}

void open_or_create_file(string filename) {
    fstream file;
    try {
        file.open(filename, ios::out);
        if (!file) {
            cout << "File " << filename << " not created!" << endl;
        } else {
            cout << "File " << filename << " created successfully!" << endl;

        }
    } catch (const exception &e) {

        cout << "Couldn't open " << filename << " file!" << endl;
        cerr << e.what();
    }
    file.close();
}

void write_text_to_file(string filename, string text) {
    fstream file;
    try {
        file.open(filename, ios::out);
        file << text;
        cout << text << " written to "
             << "filename";
    } catch (const exception &e) {
        cerr << e.what();
    }
    file.close();
}

int main() {
    int rows = 6;
    int columns = 6;
    int **a = make_2d_array(columns, rows);
    a = fill_random_2d_array(a, columns, rows, 1, 6);
    print_2d_arr_matrice(a, columns, rows);
    string text = "";
    string filename = "2d_matrice.txt";
    open_or_create_file(filename);
    write_text_to_file(filename, text);
    return 0;
}
