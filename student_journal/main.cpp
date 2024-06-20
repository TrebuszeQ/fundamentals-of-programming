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

string read_input_str(const string& msg) {
    string in;
    cout << msg << endl;
    getline(std::cin, in);

    return in;
}

string str_to_lowercase(const string& str) {
    string result;
    for(char cha : str) {
        result += tolower(cha);
    }
    return result;
}

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
            line = line.substr(0, line_len);
            printf("Odczytana linia: %s\n", line.c_str());
            lines.push_back(line);
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
    cout << endl;
    return lines;
}

void write_students_list_to_file(const string& path, const list<Student>& students) {
    fstream file;

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
    
    try {
        for(auto student : students) {
            file << student.tozsamosc << "|";
            for(auto ocena : student.oceny) {
                file << ocena.c_str() << " ";
            }
            file << "|";
            file << student.srednia_ocen << "|";
            file << student.ocena_koncowa << "\r";
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
                // cout << "line2: " << line2 << endl;
                parts_list.push_back(line2);
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
    auto result = vector<string>();
    for(const string& node : lis) {
        // cout << "node: " << node << endl;
        result.push_back(node);
    }
    // cout << result.size();
    return result;
}

double count_average_grade(const list<int>& grades_list_int) {
    double result = 0;
    for(int grade : grades_list_int) {
        try {
            // cout << grade;
            result += grade;
        }
        catch(exception& e) {
            printf("Wystapil blad podczas konwersji %i na typ double\n", grade);
        }
    }

    if(result > 0 and grades_list_int.size() > 0) {
        result /= grades_list_int.size();
    }
    return result;
};

string determine_grade(double average_grade) {
    string result = "Niedostateczny";
    if(average_grade >= 91) {
        result = "Bardzo dobry";
    }
    else if(average_grade >= 81) {
        result = "Dobry plus";
    }
    else if(average_grade >= 71) {
        result = "Dobry";
    }
    else if(average_grade >= 61) {
        result = "Dostateczny plus";
    }
    else if(average_grade >= 51) {
        result = "Dostateczny";
    }
    return result;
};

double count_average_of_all(const list<Student>& students) {
    double result = 0;
    for(auto student : students) {
        result += student.srednia_ocen;
    }

    if(result > 0 && students.size() > 0) {
        result /= students.size();
    }

    return result;
}

list<Student> create_student_struct_list(list<string>& student_list) {
    list<Student> list_students_struct;
    vector<string> grades_str_v = vector<string>(6, "");
    string grades_str;
    list<string> line_splitted;
    list<string> grades_list;
    for(string& line : student_list) {
        // cout << "line: " << line << endl;
        line_splitted = split_string_by_char(line, '|');
        grades_str = line_splitted.back();
        // cout << "grades_str: " << grades_str << endl;
        list<string> grades_list = list<string>(split_string_by_char(grades_str, ' '));
        list<int> grades_int_list = str_line_to_int_list(grades_str);
        Student stud = *new Student;
        stud.tozsamosc = (line_splitted.front());
        stud.oceny = list_to_vector(grades_list, grades_list.size());
        stud.srednia_ocen = count_average_grade(grades_int_list);
        stud.ocena_koncowa = determine_grade(stud.srednia_ocen);  
        list_students_struct.push_back(stud);
    }

    return list_students_struct;
};
void print_student_data(Student& student) {
    printf("Student: %s\n", student.tozsamosc.c_str());
    cout << "oceny: ";
    for(auto ocena : student.oceny) {
        cout << ocena << " ";
    }
    cout << endl;
    printf("Srednia ocen studenta: %f\n", student.srednia_ocen);
    printf("Ocena koncowa studenta: %s\n", student.ocena_koncowa.c_str());
    cout << endl;
}

void print_students_struct_list(list<Student>& students_list) {
    for(auto student : students_list) {
        print_student_data(student);
    }
}

void print_students_above_average(const list<Student>& students_above_average) {
    cout << "Studenci ze sredenia ocen powyzej sredniej: " << endl;
    for(auto student : students_above_average) {
        cout << student.tozsamosc << endl;
    }
    cout << endl;
}

list<Student> students_with_above_average(const list<Student>& students, double average_sum) {
    list<Student> results;
    for(auto student: students) {
        if(student.srednia_ocen > average_sum) {
            results.push_back(student);
        }
    }
    return results;
}

void print_particular_student(const list<Student>& students) {
    cout << "Podaj litere x aby wyjsc.\n";
    string student_name = "";
    while(student_name != "x") {
        string student_name = read_input_str("Podaj imie i nazwisko studenta (wielkosc liter nie ma znaczenia): \n");
        student_name = str_to_lowercase(student_name);
        int count = 0;
        for(auto student : students) {
            string student_id = str_to_lowercase(student.tozsamosc);
            if(student_id == student_name) {
                print_student_data(student);
                break;
            }
            count++;
            if(count == students.size()) {
                printf("Nie odnaleziono studenta %s\n", student_name.c_str());
                break;
            }
        }
        cout << endl;
    }
    printf("Wyjscie\n");
}

int main() {
    list<string> students_list = open_or_create_file_and_read_to_list("dane.txt");
    list<Student> students_struct_list = create_student_struct_list(students_list);
    print_students_struct_list(students_struct_list);
    double average_sum = count_average_of_all(students_struct_list);
    cout << endl;
    printf("Suma srednich wszystkich studentow wynosi %f\n", average_sum);
    list<Student> students_above_average_list =         students_with_above_average(students_struct_list, average_sum);
    printf("Ilosc studentow z srednia ocen powyzej sredniej wynosi %li\n", students_above_average_list.size());
    cout << endl;
    print_students_above_average(students_above_average_list);
    write_students_list_to_file("studenci_ze_srednia_powyzej_sredniej.txt", students_above_average_list);
    print_particular_student(students_struct_list);
    return 0;
}
