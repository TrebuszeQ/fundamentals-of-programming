#include <iostream>
#include <string>
#include <list>
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

int* read_arr_msg(int len, int arr[], const string& msg) {
    for (int i = 0; i < len; i++) {
        int input = read_int(msg);
        arr[i] = input;
    }

    return arr;
}

void make_random_arr(int len, int arr[], int start, int end) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(start, end);

    for (int i = 0; i < len; i++) { arr[i] = dist(gen); }
}

void print_arr(int len, int arr[]) {
    cout << endl << "Tablica: [";
    for (int i = 0; i < len; i++) {
        cout << arr[i];
        if (i != len - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int sum_pow_odd_num(int len, const int arr[]) {
    int sigma = 0;
    for (int i = 0; i < len; i ++) { if (arr[i] > 0 and arr[i] % 2 == 1) sigma += arr[i] * arr[i]; }
    return sigma;
}

void find_max_and_indice(int len, const int arr[], int* max, int& ind) {
    ind = 0;
    *max = arr[0];

    for (int i = 0; i < len; i ++) {
        if (arr[i] >= *max) {
            ind = i;
            *max = arr[ind];
        }
    }
}

void copy_arr(const int arr[], int len2, int arr2[]) {
    for(int i = 0; i < len2; i++) {
        arr2[i] = arr[i];
    }
}

int count_even(int len, const int arr[]) {
    int count = 0;
    for(int i = 0; i < len; i++) {
        if (arr[i] >= 0 and arr[i] % 2 == 0) count += 1;
    }
    return count;
}

void copy_even_to_arr(int len, const int arr[], int len2, int arr2[]) {
    int counter = 0;
    for(int i = 0; i < len; i++) {
        if (arr[i] >= 0 and arr[i] % 2 == 0) {
            arr2[counter] = arr[i];
            counter += 1;
        }
    }
}

//int copy_even_to_arr(int len, const int arr[], int arr2[]) {
//    int count = 0;
//    int* temp_ptr;
//
//    for(int i = 0; i < len; i++) {
//        if (arr[i] >= 0 and arr[i] % 2 == 0) {
//            count++;
//            temp_ptr = new int[count];
//            copy_arr(arr, count, arr2);
//            arr2 = temp_ptr;
//            arr2[count - 1] = arr[i];
//        }
//    }
//    delete[] temp_ptr;
//    return count;
//}

int main()
{
    //1
    int len = 5;
    int* ptr_x = new int[len];
    int* ptr_y = new int[len];
    make_random_arr(len, ptr_x, -5, 5);
    make_random_arr(len, ptr_y, -5, 5);

    cout << endl << "------------------";
    cout << endl << "Zadanie 1." << endl;
    print_arr(len, ptr_x);
    print_arr(len, ptr_y);

    //2
    int sum = sum_pow_odd_num(len, ptr_x);

    cout << endl << "------------------";
    cout << endl << "Zadanie 2." << endl;
    cout << "Suma kwadratow liczb nieparzystych wiekszych od 0 wynosi: " << sum << endl;

    //3
    int ind = 0;
    int max;
    int& ind_ref = ind;
    find_max_and_indice(len, ptr_y, &max, ind_ref);

    cout << endl << "------------------";
    cout << endl << "Zadanie 3." << endl;
    cout << "Max: " << max << " indeks: " << ind_ref << endl;

    //4
    int len2 = count_even(len, ptr_x);
    int* ptr_p = new int[len2];
    cout << endl << "------------------";
    cout << endl << "Zadanie 4." << endl;

    copy_even_to_arr(len, ptr_x, len2, ptr_p);
    print_arr(len2, ptr_p);
    delete[]ptr_p;
    
    ptr_p = new int[len2];
    copy_even_to_arr(len, ptr_y, len2, ptr_p);
    print_arr(len2, ptr_p);

    delete[]ptr_x;
    delete[]ptr_y;
    delete[]ptr_p;
    return 0;
}
