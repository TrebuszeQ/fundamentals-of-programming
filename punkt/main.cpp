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
    catch (exception &e) { return false; }
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

void make_random_points_arr(int len, Punkt arr[], int start, int end) {
    double x = 0;
    double y = 0;
    random_device rd;
    mt19937  gen(rd());
    uniform_real_distribution<> dist(start, end);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            x = dist(gen);
            y = dist(gen);
        }
        auto pkt = Punkt();

        pkt.x = x;
        pkt.y = y;
        pkt.odl = measure_distance(x, y);

        arr[i] = pkt;
    }
}

void print_points_arr(Punkt arr[], int len) {
    cout << "Tablica punktow: ";
    for (int i = 0; i < len; i++) {
        printf("(%0.2f, %0.2f) ", arr[i].x, arr[i].y);
    }
    cout << endl;
}

int define_quarter(Punkt pnt) {
    if (pnt.x == 0 and pnt.y == 0) {
        return 0;
    }

    if (pnt.x >= 0 and pnt.y >= 0) {
        return 1;
    }
    else if(pnt.x <= 0 and pnt.y >= 0) {
        return 2;
    }
    else if(pnt.x <= 0 and pnt.y <= 0) {
        return 3;
    }
    else if(pnt.x >= 0 and pnt.y <= 0) {
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
    printf("Ilosc punktow (0,0): %d", qt_arr[0]);
    cout << endl;
    for(int i = 1; i < qt_arr_len; i++) {
        cout << "Ilosc punktow w cwiartce " << i << ": " << qt_arr[i] << endl;
    }
    cout << endl;
}

list<Punkt> make_list_of_points_in_radius(Punkt pnt_arr[], int pnt_arr_len, int radius) {
    list<Punkt> pnts_in_radius;

    for(int i = 0; i < pnt_arr_len; i++) {
        Punkt pnt = pnt_arr[i];
        if (pnt.odl <= radius) {
            pnts_in_radius.push_back(pnt);
        }
    }
    return pnts_in_radius;
}

void print_pnts_within_radius(const list<Punkt> &pnts_in_radius) {
    cout << "Punkty znajdujace sie w okregu to:" << endl;
    for(Punkt pnt : pnts_in_radius) {
        printf("(%.2f,%.2f) ", pnt.x, pnt.y);
    }
    cout << endl;
}

int main() {
    int n = read_int("Podaj ilosc punktow.");
    auto* pts_ptr = new Punkt[n];
    int quarter_arr[5] = {0, 0, 0, 0, 0};
    make_random_points_arr(n, pts_ptr, -10, 10);
    print_points_arr(pts_ptr, n);
    count_points_in_quarter(pts_ptr, n, quarter_arr);
    print_count_arr(quarter_arr, 5);

    int r = read_int("Podaj dlugosc promienia okregu.");
    cout << "Zakladajac ze srodek okregu znajduje się w punkcie S=(0,0)" << endl;
    list<Punkt> pnts_in_radius = make_list_of_points_in_radius(pts_ptr, n, r);
    cout << "Ilosc punktow znajdujacych sie w okregu to: " << pnts_in_radius.size() << "." << endl;
    print_pnts_within_radius(pnts_in_radius);

    delete[] pts_ptr;
    return 0;
}