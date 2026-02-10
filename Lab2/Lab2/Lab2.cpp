#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Константи (можна змінити під ваші умови)
const double PI = 3.14159265358979323846;

// Структура для координат
struct Point {
    double x, y;
};

// Базовий клас для всіх юнітів
class Unit {
protected:
    Point position;
    double speed; // V

public:
    Unit(double x, double y, double v) : position{ x, y }, speed(v) {}
    virtual ~Unit() {}

    // Чисто віртуальний метод руху, який кожен реалізує по-своєму
    virtual void move(double dt) = 0;

    void printPosition() const {
        std::cout << "(" << std::fixed << std::setprecision(2)
            << position.x << ", " << position.y << ")";
    }

    // Геттер для типу юніта (для красивого виводу)
    virtual std::string getType() const = 0;
};

// --- Клас РОЗРОБНИКА ---
class Developer : public Unit {
private:
    double changeDirInterval; // N (секунди)
    double timeSinceLastChange;
    double moveAngle; // Поточний кут руху в радіанах

public:
    Developer(double x, double y, double v, double n_seconds)
        : Unit(x, y, v), changeDirInterval(n_seconds), timeSinceLastChange(0) {
        // Початковий випадковий напрямок
        changeDirection();
    }

    void changeDirection() {
        // Генеруємо випадковий кут від 0 до 2*PI
        moveAngle = ((double)rand() / RAND_MAX) * 2 * PI;
        std::cout << "\n--- [Dev changed direction] ---\n";
    }

    void move(double dt) override {
        // 1. Перевірка таймера для зміни напрямку
        timeSinceLastChange += dt;
        if (timeSinceLastChange >= changeDirInterval) {
            changeDirection();
            timeSinceLastChange = 0; // Скидаємо таймер (або віднімаємо N для точності)
        }

        // 2. Рух по прямій
        double dx = speed * std::cos(moveAngle) * dt;
        double dy = speed * std::sin(moveAngle) * dt;

        position.x += dx;
        position.y += dy;
    }

    std::string getType() const override { return "Developer"; }
};

// --- Клас МЕНЕДЖЕРА ---
class Manager : public Unit {
private:
    Point center; // Центр кола
    double radius; // R
    double currentAngle; // Кут на колі (тета)

public:
    Manager(double centerX, double centerY, double r, double v)
        : Unit(centerX + r, centerY, v), center{ centerX, centerY }, radius(r), currentAngle(0) {
    }

    void move(double dt) override {
        // Кутова швидкість w = V / R
        double angularSpeed = speed / radius;

        // Оновлюємо кут
        currentAngle += angularSpeed * dt;

        // Нормалізуємо кут (щоб не зростав нескінченно), хоча sin/cos впораються і так
        if (currentAngle > 2 * PI) currentAngle -= 2 * PI;

        // Параметричне рівняння кола
        position.x = center.x + radius * std::cos(currentAngle);
        position.y = center.y + radius * std::sin(currentAngle);
    }

    std::string getType() const override { return "Manager  "; }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Ініціалізація генератора випадкових чисел

    // Параметри симуляції
    double dt = 0.5; // Крок часу (наприклад, пів секунди за ітерацію)
    double N = 2.0;  // Розробник змінює напрямок кожні 2 секунди
    double R = 10.0; // Радіус кола менеджера
    double V = 2.0;  // Швидкість руху

    std::vector<Unit*> employees;

    // Створюємо розробника в точці (0,0)
    employees.push_back(new Developer(0, 0, V, N));

    // Створюємо менеджера, що кружляє навколо точки (20, 20)
    employees.push_back(new Manager(20, 20, R, V));

    std::cout << "--- Start Simulation ---\n";
    std::cout << "Time step (dt): " << dt << "s\n\n";

    // Цикл симуляції (наприклад, 10 кроків)
    for (int i = 0; i < 10; ++i) {
        double currentTime = i * dt;
        std::cout << "Time: " << currentTime << "s\n";

        for (auto* emp : employees) {
            emp->move(dt); // Рухаємо

            std::cout << "  " << emp->getType() << ": ";
            emp->printPosition();
            std::cout << std::endl;
        }
        std::cout << "-----------------------\n";
    }

    // Очищення пам'яті
    for (auto* emp : employees) {
        delete emp;
    }

    return 0;
}