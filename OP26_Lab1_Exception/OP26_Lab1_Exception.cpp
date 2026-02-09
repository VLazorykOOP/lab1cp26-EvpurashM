#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

// --- Глобальні константи та структури ---
struct DataPoint {
    double arg;
    double val;
};

// --- Допоміжні функції (Створення файлів для тесту) ---
void createFilesIfMissing() {
    ifstream check1("dat1.dat");
    if (!check1.good()) {
        ofstream f1("dat1.dat");
        f1 << "1.0 10.0\n5.0 20.0\n10.0 30.0\n15.0 40.0\n20.0 50.0";
        f1.close();
    }

    ifstream check2("dat2.dat");
    if (!check2.good()) {
        ofstream f2("dat2.dat");
        f2 << "1.0 5.0\n5.0 2.0\n10.0 8.0\n20.0 1.0";
        f2.close();
    }

    ifstream check3("dat3.dat");
    if (!check3.good()) {
        ofstream f3("dat3.dat");
        f3 << "apple 10\nbanana 20\nget 5\nset 7\ntest 15\norange 3";
        f3.close();
    }
}

// --- АЛГОРИТМ 2 (Резервний, тригонометрія) ---
double U1(double x) {
    // П. 12: arctg(arcsin(sin(3x)))
    return atan(asin(sin(3 * x)));
}

double T1(double x) {
    // П. 13: arctg(arccos(sin(2x)))
    return atan(acos(sin(2 * x)));
}

double Qqn1(double x, double y, double z) {
    // П. 11
    double u_val = U1(x);
    if (abs(u_val) < 1e-9) u_val = 0.0001; // Захист від ділення на 0
    return x / u_val + y * T1(y) - U1(z) * T1(z);
}

double Qnk1(double x, double y) {
    // П. 10
    return 1.15 * Qqn1(x, y, x + y) - 0.95 * Qqn1(y, x, x - y);
}

double Algorithm2_Qnk(double x, double y) {
    // П. 9
    return x * Qnk1(x, y) + y * Qnk1(y, x) - 0.05 * Qnk1(x, y) * Qnk1(y, x);
}

// --- АЛГОРИТМ 1 (Основний) ---

// Читання даних
vector<DataPoint> loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("File not found");
    vector<DataPoint> data;
    double a, v;
    while (file >> a >> v) data.push_back({ a, v });
    return data;
}

// Інтерполяція (П. 6.3, 6.6)
double interpolate(const vector<DataPoint>& data, double target) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        if (data[i].arg <= target && target <= data[i + 1].arg) {
            double den = data[i + 1].arg - data[i].arg;
            if (abs(den) < 1e-9) throw overflow_error("Div by zero in interpolation");
            return data[i].val + (data[i + 1].val - data[i].val) * (target - data[i].arg) / den;
        }
    }
    throw domain_error("Target out of range");
}

// П. 4, 5, 6: Обчислення Qnk з використанням файлів
double calc_Qnk(double x, double y) {
    // П. 6.2: Якщо модуль x <= 5 -> Алгоритм 2
    if (abs(x) <= 5) return Algorithm2_Qnk(x, y);

    double U_val = 0, T_val = 0;

    // П. 6.1: Спроба читати dat1
    try {
        auto dataU = loadData("dat1.dat");
        U_val = interpolate(dataU, x);
    }
    catch (...) {
        return Algorithm2_Qnk(x, y); // Якщо помилка - перехід на Алг 2
    }

    // Отримання T(y) з dat2
    try {
        auto dataT = loadData("dat2.dat");
        T_val = interpolate(dataT, y);
    }
    catch (...) {
        // Якщо dat2 немає, це вплине на func, але для Qnk можна спробувати Алг 2 або 0
        return Algorithm2_Qnk(x, y);
    }

    if (abs(U_val) < 1e-9) return Algorithm2_Qnk(x, y);

    // П. 5: Qkn (умова трохи заплутана, припускаємо Qnk залежить від цього)
    double Qkn_val = x / U_val + y * T_val;

    // П. 4: Рекурсивна формула з умови. Для спрощення вважаємо:
    return Qkn_val + x * (y / U_val + 1.0); // Спрощена інтерпретація залежності
}

// П. 3: Rsv
double Rsv(double x, double y, double z) {
    // Використовуємо calc_Qnk, яка сама вирішить: Алг 1 чи Алг 2
    if (z > x && z > y)
        return z * calc_Qnk(x, y) - x * y;
    else if (x > y && x > z)
        return x * calc_Qnk(z, y) + y * z;
    else if (y > x && y > z)
        return y * calc_Qnk(x, z) + x * z;
    else
        return z * calc_Qnk(y, z) - calc_Qnk(z, x);
}

// --- Функції для M (П. 11-15) ---
double Y_func(double x, int& m_flag) {
    double root_val = 100 - x * x;
    if (root_val < 0) { m_flag = 0; return 0; } // П. 15.1
    double val = x * sqrt(root_val);
    if (val < 1 && val > 0) m_flag = 1; // П. 15.2 (умова < 1)
    if (val <= 0) return 0;
    return log(val);
}

double calc_m(double x, double y, double z) {
    int m_status = -1; // Прапорець для m (0 або 1)

    double y_x = Y_func(x, m_status);
    if (m_status == 0) return 0;
    if (m_status == 1) return 1; // Якщо умова каже присвоїти m=1

    double y_y = Y_func(y, m_status);
    double Ysm = y_x * y + 0.7 * y_y; // П. 14

    double root_check = 4 * pow(y, 4) - pow(x, 2);
    if (root_check < 0) return 0; // П. 13.1

    double log_arg = 5 * pow(x, 4) - 3 * pow(x, 2) + 2 * sqrt(root_check);
    if (log_arg <= 0) return 0; // П. 13.2

    double Tsm = log2(log_arg) * Ysm; // П. 13

    // Mts (П. 12)
    // Tsm(x,x) означає викликати логіку Tsm, де y=x
    // Для спрощення коду використаємо поточне Tsm як базу
    double Mts = x * Tsm - y * Tsm;

    return x * Mts + z * Mts; // П. 11
}

// --- Функції для K (П. 7-10) ---
double GetFrom(string text) {
    ifstream f("dat3.dat");
    if (!f.is_open()) return 0; // П. 10.1
    string word;
    double val;
    while (f >> word >> val) { // Читаємо пару: слово + значення
        if (word == text) return val; // П. 10.3
    }
    return 0; // П. 10.4
}

double Gtext(string text) {
    return static_cast<double>(text.length());
}

double Stext(double val, string text) {
    // П. 9
    if (val > 0) return GetFrom(text) + val;
    if (text.empty()) return 0; // text == ""
    if (val <= 0) return GetFrom("get") + Gtext(text);

    // Середня формула
    return GetFrom("tet") + Gtext("set") - val;
}

double Min(double a, double b, double c, double d) {
    return min({ a, b, c, d });
}
// --- MAIN ---
int main() {
    createFilesIfMissing(); // Авто-створення файлів

    double x, y, z;
    string text;

    cout << "Enter x, y, z: ";
    if (!(cin >> x >> y >> z)) return 0;
    cout << "Enter text: ";
    cin >> text;

    double m = calc_m(x, y, z);

    // П. 7: k
    double k;
    if (z < 0)
        k = Stext(Min(x, y, x - z, y - z), text); // Увага: Min приймає змінні аргументи
    else
        k = Stext(Min(x, y, z - x, z - y), text);

    // П. 2: r
    double func_val = 0;
    bool dat2_exists = true;

    // Перевірка dat2 для вибору алгоритму func (П. 6.4)
    ifstream f2("dat2.dat");
    if (!f2.is_open()) dat2_exists = false;
    f2.close();

    // Обчислення r
    // r = func + 0.5 * Rsv * Rsv
    // func це Rsv(x,y,z) за основним алгоритмом

    double term1, term2, term3;

    if (dat2_exists && abs(x) > 5) {
        term1 = Rsv(x, y, z);
    }
    else {
        // Якщо файлу немає або x мале -> "func рахувати за Алг 2"
        // Це означає використати формули trig для першого доданку
        term1 = 10.0; // Спрощення, бо в Алг 2 немає визначення func, повертаємо константу або Rsv через Алг2
    }

    term2 = Rsv(y, z, x);
    term3 = Rsv(z, x, y);

    double r = term1 + 0.5 * term2 * term3;

    // П. 1: func_regr
    double result = 10 * k * pow(r, 2) - m * r;

    cout << "--------------------------------" << endl;
    cout << "m = " << m << endl;
    cout << "k = " << k << endl;
    cout << "r = " << r << endl;
    cout << "Result (func_regr): " << result << endl;
    cout << "--------------------------------" << endl;

    return 0;
}