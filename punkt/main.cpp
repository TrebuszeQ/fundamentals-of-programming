#include <iostream>
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


struct Punkt {
    double x;
    double y;
    double odl;
};

double measure_distance(double x, double y) {
    return sqrt(x * x + y * y);
}

void make_random_point_arr(int len, Punkt arr[], int start, int end) {
    int x = 0;
    int y = 0;
    random_device rd;
    mt19937  gen(rd());
    uniform_int_distribution<> dist(start, end);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            x = dist(gen);
            y = dist(gen);
        }
        auto pkt = Punkt();

        if (x > y) {
            pkt.x = y;
            pkt.y = x;
            pkt.odl = measure_distance(x, y);
        }
        else {
            pkt.x = x;
            pkt.y = y;
            pkt.odl = measure_distance(x, y);
        }
        arr[i] = pkt;
    }
}

int define_quarter(Punkt pnt) {
    if (pnt.x > 0 and pnt.y > 0) {
        return 1;
    }
    else if(pnt.x < 0 and pnt.y > 0) {
        return 2;
    }
    else if(pnt.x < 0 and pnt.y < 0) {
        return 3;
    }
    else if(pnt.x > 0 and pnt.y < 0) {
        return 4;
    }

    return 0;
}

void count_points_in_quarter(Punkt pts_arr[], int pkt_arr_len, int qt_arr[]) {
    for(int i = 0; i < pkt_arr_len; i++) {
        Punkt pkt = pts_arr[i];
        int quarter = define_quarter(pkt);
        qt_arr[quarter] += 1;
    }
}

void print_count_arr(int qt_arr[], int qt_arr_len) {
    for(int i = 0; i < qt_arr_len - 1; i++) {
        cout << "Ilosc punktow w cwiartce: " << i << qt_arr[i] << endl;
    }
}

int main() {
    int n = read_int("Podaj ilosc punktow.");
    auto* pts_ptr = new Punkt[n];
    int* quarter_arr = new int[4];
    make_random_point_arr(n, pts_ptr, -10, 10);
    count_points_in_quarter(pts_ptr, n, quarter_arr);
    print_count_arr(quarter_arr, 4);

    delete[] pts_ptr;
    delete[] quarter_arr;
    return 0;
}