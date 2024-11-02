#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <chrono>  // для замера времени

using namespace std;
using namespace chrono;

// вычисляем среднее по строке
double calculateRowAverage(const vector<int>& row) {
    double sum = accumulate(row.begin(), row.end(), 0.0);
    return sum / row.size();
}

int main() {
    int N;
    cout << "Введите размер матрицы (N): ";
    cin >> N;

    if (N <= 0) {
        cerr << "Ошибка: размер матрицы должен быть положительным числом." << endl;
        return 1;
    }

    vector<vector<int>> matrix(N, vector<int>(N));
    cout << "Введите элементы матрицы (" << N << "x" << N << "):" << endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(cin >> matrix[i][j])) {
                cerr << "Ошибка ввода: пожалуйста, введите целые числа." << endl;
                return 1;
            }
        }
    }

    // Замер времени выполнения
    auto start = high_resolution_clock::now();

    // Вычисление среднего для каждой строки
    vector<double> rowAverages(N);
    for (int i = 0; i < N; ++i) {
        rowAverages[i] = calculateRowAverage(matrix[i]);
    }

    // Завершение замера времени выполнения
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    // Сохранение результатов в файл
    ofstream outFile("/Users/nurgiss/Documents/averages.txt");
    if (outFile.is_open()) {
        for (double avg : rowAverages) {
            outFile << avg << endl;
        }
        // Добавляем информацию о времени выполнения и размере матрицы
        outFile << "\n--- Информация о вычислениях ---" << endl;
        outFile << "Размер матрицы: " << N << "x" << N << endl;
        outFile << "Время выполнения: " << elapsed.count() << " секунд" << endl;

        outFile.close();
        cout << "Средние значения по строкам и информация о вычислениях сохранены в файл averages.txt" << endl;
    } else {
        cerr << "Ошибка открытия файла для записи." << endl;
    }

    return 0;
}
