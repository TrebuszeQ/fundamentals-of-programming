#include <fstream>
#include <iostream>
#include <random>
#include <list>
#include <vector>

using namespace std;

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
    cout << endl;
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
            cout << endl;
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
    cout << endl;
    file.close();
}

list<string> open_or_create_file_and_read_to_list(const string& path) {
    list<string> lines;
    ifstream file;

    try {

        if (!file) {
            printf("Plik %s nie istnieje.", path.c_str());
            cout << endl;
            printf("Plik %s stworzony pomyslnie.", path.c_str());
            cout << endl;
        }
        file.open(path, ios::out);
        printf("Plik %s otwarty pomyslnie.", path.c_str());
        cout << endl;
        string line;
        try {
            while (getline(file, line)) {
                int line_len = line.length();
                line = line.substr(0, line_len - 1);
                lines.push_back(line);
                printf("Odczytana linia: %s", line.c_str());
                cout << endl;
            }
            printf("Plik %s odczytany pomyslnie.", path.c_str());
            cout << endl;
        }
        catch(exception& e) {
            printf("Plik nie mogl zostac odczytany z powodu bledu %s.", e.what());
            cout << endl;
        }
    }
    catch (const exception& e) {
        printf("Plik nie mogl zostac otwarty z powodu bledu %s.", e.what());
        cout << endl;
    }
    file.close();
    cout << endl;
    return lines;
}

void open_or_create_file_and_write_text(const string& path, const string& text) {
    fstream file;
    try {
        if (!file) {
            printf("Plik %s nie istnieje.", path.c_str());
            cout << endl;
            printf("Plik %s stworzony pomyslnie.", path.c_str());
            cout << endl;
        }
        file.open(path, ios::out);
        printf("Plik %s otwarty pomyslnie.", path.c_str());
        cout << endl;
        file << text;
        printf("Plik %s nadpisany tekstem:\n%s", path.c_str(), text.c_str());
        cout << endl;
        printf("Plik %s odczytany pomyslnie.", path.c_str());
        cout << endl;

    }
    catch (const exception &e) {
        printf("Plik nie mogl zostac otwarty z powodu bledu %s.", e.what());
        cout << endl;
    }
    cout << endl;
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

int find_char_position(const string& str, const char& ch) {
    int result = 0;
    for(char ch2 : str) {
        if(ch2 == ch) {
            return result;
        }
        result += 1;
    }
    return -2;
}

list<string> split_string_by_char(const string& line, const char& delimeter) {
    list<string> parts_list;
    int end;
    string line2 = line;
    for(int i = 0; i < line.length(); i++) {
        try {
            string part;
            end = find_char_position(line2, delimeter);
            int line2_len = line2.length();
            if(end == -2) {
                part = line2;
                parts_list.push_back(part);
                break;
            }
            else {
                part = line2.substr(0, end);
            }
            parts_list.push_back(part);
            int part_len = part.length();
            line2 = line2.substr(part_len + 1, line2_len - part_len);
        }
        catch(exception& e) {
            printf("Wystapil blad %s, podczas ciecia linii %s w miejscu %i.", e.what(), line.c_str(), i);
        }
    }

    return parts_list;
}

vector<vector<string>> list_to_2d_array(int columns, list<string>& lis) {
    auto workers_arr = vector<vector<string>>(columns, vector<string>(0));
    int i = 0;
    for(string line : lis) {
        list<string> splitted_line = split_string_by_char(line, ' ');
        int parts_len = splitted_line.size();
        int j = 0;
        auto entries_arr = vector<string>(parts_len, "");
        for(string& part : splitted_line) {
            entries_arr[j] = part;
            j += 1;
        }
        workers_arr[i] = entries_arr;
        i += 1;
    }
    return workers_arr;
}

double count_average_worker_salary_by_seniority(vector<vector<string>>& arr, int col, int seniority) {
    double result = 0;
    int count = 0;
    for(int i = 0; i < col; i++) {
        int seniority2;
        int salary;
        try {
            seniority2 = stoi(arr[i][1]);
            salary = stoi(arr[i][2]);
        }
        catch(exception& e) {
            printf("Nie mozna bylo odczytac zawartosci tablicy z powodu bledu %s.", e.what());
            return 0.0;
        }
        if(seniority2 > seniority) {
            result += double(salary);
            count += 1;
        }
    }
    if(result > 0) {
        result /= count;
    }

    printf("Srednia placa pracownikow o stazu wiekszym od %i wynosi %f.", seniority, result);
    cout << endl;
    return result;
}

string filter_out_by_seniority_to_text(vector<vector<string>>& arr, int columns, int seniority) {
    string result;
    for(int i = 0; i < columns; i++) {
        int seniority2 = stoi(arr[i][1]);
        string name = arr[i][0];
        if(seniority2 > seniority) {
            result += name + "\n";
        }
    }
    return result;
}

void zadanie1(int columns, int rows) {
    printf("Zadanie 1");
    cout << endl;
    vector<vector<int>> arr = vector<vector<int>>(columns, vector<int>(rows));
    fill_random_2d_array(arr, columns, rows, 1, 6);
    print_2d_arr_matrice(arr, rows, columns);
    cout << "-------------------" << endl;
    string text = arr_to_text(arr, columns, rows);
    string filename = "2d_matrice.txt";
    open_or_create_file(filename);
    cout << "-------------------" << endl;
    open_or_create_file_and_write_text(filename, text);
    cout << "-------------------" << endl;
    sum_under_diagonal_verbose(arr, columns);
    cout << "-------------------" << endl << endl;
}


void zadanie2() {
    printf("Zadanie 2");
    cout << endl;
    list<string> lines = open_or_create_file_and_read_to_list("pracownicy.txt");
    cout << "-------------------" << endl;
    int columns =  lines.size();
    auto workers_arr= list_to_2d_array(columns, lines);
    double avg_salary = count_average_worker_salary_by_seniority(workers_arr, columns, 10);
    cout << "-------------------" << endl;
    string above_10_workers = filter_out_by_seniority_to_text(workers_arr, columns, 10);
    open_or_create_file_and_write_text("pracownicy2.txt", above_10_workers);
    cout << "-------------------" << endl << endl;
}



int main() {
    printf("Zadanie dodatkowe - Hubert Dabrowski D5 PUW");
    cout << endl << endl;
    zadanie1(6, 6);
    zadanie2();
    return 0;
}
