#include <algorithm>
#include <array>
#include <iostream>

struct SimulationResult {
    int days = 0;
    int start_day = 0;
};

long long minWeek(long long a, long long b, long long c) {
    return std::min({a / 3, b / 2, c / 2});
}

SimulationResult simulationDays(long long a_ostatok, long long b_ostatok,
                                long long c_ostatok) {
    // 0 — рыбный корм, 1 — рагу, 2 — курица. Неделя начинается с понедельника.
    const std::array<int, 7> menu = {0, 1, 2, 0, 2, 1, 0};
    SimulationResult best;

    for (int start_day = 0; start_day < 7; ++start_day) {
        std::array<long long, 3> ostatki = {a_ostatok, b_ostatok, c_ostatok};
        int days = 0;

        while (true) {
            int food = menu[(start_day + days) % 7];
            if (ostatki[food] == 0) {
                break;
            }

            --ostatki[food];
            ++days;
        }

        // При равном результате оставляем первый день по порядку недели.
        if (days > best.days) {
            best.days = days;
            best.start_day = start_day;
        }
    }

    return best;
}

int main() {
    long long a;
    long long b;
    long long c;

    if (!(std::cin >> a >> b >> c) || a < 0 || b < 0 || c < 0) {
        std::cerr << "Введите три неотрицательных целых числа.\n";
        return 1;
    }

    // Сколько полных недель кот сможет питаться при любом стартовом дне.
    long long weeks = minWeek(a, b, c);

    long long a_ostatok = a - weeks * 3;
    long long b_ostatok = b - weeks * 2;
    long long c_ostatok = c - weeks * 2;

    SimulationResult best = simulationDays(a_ostatok, b_ostatok, c_ostatok);
    const std::array<const char*, 7> weekdays = {
        "понедельник", "вторник", "среда", "четверг",
        "пятница", "суббота", "воскресенье"
    };

    std::cout << weeks * 7 + best.days << '\n';
    std::cout << weekdays[best.start_day] << '\n';

    return 0;
}
