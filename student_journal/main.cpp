#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;
struct Student {
    string tozsamosc;
    vector<string> oceny = vector<string>(6, "");

    double srednia_ocen = 0;
    string ocena_koncowa;
};

list<string> open_or_create_file_and_read_to_list(const string&path) {
    list<string> lines;
    ifstream file;

    if(!file) {
        printf("Plik %s nie istnieje.\n", path.c_str());
        try {
            file.open(path, ios::out);
        }
        catch(exception& e) {
            printf("PLik %s nie mogl zostac stworzony.\n", e.what());
        }
        printf("Plik %s stworzony pomyslnie.\n", path.c_str());
    }
    else {
        try {
            file.open(path, ios::out);
        }
        catch (exception &e) {
            printf("Plik %s otwarty pomyslnie.\n", e.what());
        }
    }
    string line;
    try {
        while(getline(file, line)) {
            int line_len = line.length();
            line = line.substr(0, line_len - 1);
            printf("Odczytana linia: %s\n", line.c_str());
        }
    }
    catch (exception& e) {
        printf("Wystapil blad podczas odczytu pliku %s\n.", e.what());
    }
    try {
        file.close();
    }
    catch(exception& e) {
        printf("Wystapil blad podczas zamykania pliku %s\n.", e.what());
    }
    return lines;
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
    for(int i = 0;i < line.length(); i ++) {
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
            printf("Podczas ciecia linii %s w miejscu %i, wystapil blad %s.", line.c_str(), i, e.what());
            return parts_list;
        }
    }
    return parts_list;
}

list<int> str_line_to_int_list(const string& line) {
    list<int> int_list;
    list<string> line_splitted = split_string_by_char(line, ' ');
    for(const string& grade : line_splitted) {
        int grade_int = 0;
        try {
            grade_int = stoi(grade);
        }
        catch(exception &e) {
            printf("Wystapil blad podczas konwersji %s na typ integer.", grade.c_str());
        }
        int_list.push_back(grade_int);
    }
    return int_list;
}

vector<string> list_to_vector(const list<string>& lis, int len) {
    auto result = vector<string>(len, "");
    for(const string& node : lis) {
        result.push_back(node);
    }
    return result;
}

double count_average_grade(const list<int>& grade_list) {
    double result = 0;
    for(int grade : grade_list) {
        result += grade;
    }

    int grede_list_s = grade_list.size();
    if(result > 0 and grede_list_s > 0) {
        result /= grede_list_s;
    }
    return result;
};

list<Student> str_student_list_to_student(list<string>& student_list) {
    list<Student> list_student_struct;
    vector<string> grades_str;
    vector<string> grades_str_vector;
    list<int> grades_list;
    list<string> line_splitted;
    for(string& line : student_list) {
        line_splitted = split_string_by_char(line, '|');
        grades_str = line_splitted.back();
        grades_list = str_line_to_int_list(line_splitted.back());
    }
    Student stud = *new Student;
    stud.oceny = list_to_vector(grades_str, grades_str.size());
    stud.srednia_ocen = count_average_grade(grades_list);
}

int main() {
    list<string> students_list = open_or_create_file_and_read_to_list("dane.txt");


    return 0;
}
