#include "Head.h"

int main() {
    fstream file("file", ios::in);
    if (!file.is_open()) {
        cerr << "Ошибка: файл не открыт." << endl;
        return 1;
    }

    CSVParser<string, int, int, double> parser(file, 0, ',', '"');

    for (const auto& row : parser) {
        cout << get<0>(row) << ' ' << get<1>(row) << ' ' << get<2>(row) << ' ' << get<3>(row) << endl;
    }

    file.close();
    return 0;
}
