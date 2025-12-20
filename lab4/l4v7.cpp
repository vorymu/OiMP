#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <limits>
#include <cstdint>

constexpr std::size_t MAX_MATRIX_SIZE = 20;

double** createMatrix(std::size_t size);
void fillMatrixManually(double** matrix, std::size_t size);
void fillMatrixRandom(double** matrix, std::size_t size);
void printMatrix(double** matrix, std::size_t size);
void freeMatrix(double** matrix, std::size_t size);
double findMinElement(double** matrix, std::size_t size, std::size_t& minRow, std::size_t& minCol);
double findMaxElement(double** matrix, std::size_t size, std::size_t& maxRow, std::size_t& maxCol);
double scalarProduct(double** matrix, std::size_t size, std::size_t row, std::size_t col);
std::int32_t findMinK(double** matrix, std::size_t size);
bool validateMatrix(double** matrix, std::size_t size);
void setupConsole();
std::size_t inputMatrixSize();
std::size_t chooseFillMethod();

int main() {
    try {
        setupConsole();

        std::cout << "=== ЛАБОРАТОРНАЯ РАБОТА 4: ОБРАБОТКА КВАДРАТНОЙ МАТРИЦЫ ===\n\n";

        std::size_t size = inputMatrixSize();
        std::size_t method = chooseFillMethod();

        double** matrix = createMatrix(size);
        if (!matrix) {
            std::cerr << "Критическая ошибка: не удалось выделить память для матрицы!\n";
            return 1;
        }

        if (method == 1) {
            fillMatrixManually(matrix, size);
        }
        else {
            fillMatrixRandom(matrix, size);
        }

        if (!validateMatrix(matrix, size)) {
            std::cerr << "Ошибка: матрица содержит некорректные данные!\n";
            freeMatrix(matrix, size);
            return 1;
        }

        std::cout << "\n=== ПОЛУЧЕННАЯ МАТРИЦА " << size << "x" << size << " ===\n";
        printMatrix(matrix, size);

        std::cout << "\n=== ЗАДАЧА 1: СКАЛЯРНОЕ ПРОИЗВЕДЕНИЕ ===\n";

        std::size_t minRow = 0;
        std::size_t minCol = 0;
        std::size_t maxRow = 0;
        std::size_t maxCol = 0;

        double minElem = findMinElement(matrix, size, minRow, minCol);
        double maxElem = findMaxElement(matrix, size, maxRow, maxCol);

        std::cout << "Минимальный элемент: " << minElem
            << " (строка " << minRow + 1 << ", столбец " << minCol + 1 << ")\n";
        std::cout << "Максимальный элемент: " << maxElem
            << " (строка " << maxRow + 1 << ", столбец " << maxCol + 1 << ")\n";

        if (minRow < size && maxCol < size) {
            double scalar = scalarProduct(matrix, size, minRow, maxCol);
            std::cout << "Скалярное произведение строки с минимальным элементом\n";
            std::cout << "и столбца с максимальным элементом: " << scalar << "\n";
        }
        else {
            std::cout << "Невозможно вычислить скалярное произведение (ошибка индексов).\n";
        }

        std::cout << "\n=== ЗАДАЧА 2: НАИМЕНЬШЕЕ ЦЕЛОЕ K ===\n";
        std::int32_t K = findMinK(matrix, size);

        if (K != std::numeric_limits<std::int32_t>::max()) {
            std::cout << "Наименьшее целое K, для которого хотя бы в одной строке матрицы все элементы ее будут меньше этого числа: " << K << "\n";
        }
        else {
            std::cout << "Невозможно найти такое K.\n";
        }

        freeMatrix(matrix, size);

        std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА УСПЕШНО ===\n";

    }
    catch (const char* error_msg) {
        std::cerr << "\nОШИБКА: " << error_msg << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "\nНеизвестная ошибка!\n";
        return 1;
    }

    return 0;
}

void setupConsole() {
    std::setlocale(LC_ALL, "Russian");
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

std::size_t inputMatrixSize() {
    std::size_t size{};

    std::cout << "Введите размер квадратной матрицы (от 1 до " << MAX_MATRIX_SIZE << "): ";
    if (!(std::cin >> size)) {
        throw "Недопустимый ввод размера матрицы!";
    }

    while (size < 1 || size > MAX_MATRIX_SIZE) {
        std::cout << "Ошибка! Размер должен быть от 1 до " << MAX_MATRIX_SIZE << ". Повторите ввод: ";
        if (!(std::cin >> size)) {
            throw "Недопустимый ввод размера матрицы!";
        }
    }

    std::cout << "Успешный ввод! Размер: " << size << "\n";
    return size;
}
std::size_t chooseFillMethod() {
    std::size_t method = 0;

    std::cout << "\nВыберите способ заполнения матрицы:\n";
    std::cout << "1 - Ввод с клавиатуры\n";
    std::cout << "2 - Заполнение случайными числами\n";
    std::cout << "Ваш выбор: ";

    if (!(std::cin >> method)) {
        throw "Недопустимый ввод способа заполнения!";
    }

    while (method != 1 && method != 2) {
        std::cout << "Ошибка! Выберите 1 или 2: ";
        if (!(std::cin >> method)) {
            throw "Недопустимый ввод способа заполнения!";
        }
    }

    std::cout << "Успешный ввод! Вы выбрали ";
    if (method == 1) {
        std::cout << "ввод с клавиатуры.\n";
    }
    else {
        std::cout << "заполнение случайными числами.\n";
    }

    return method;
}

double** createMatrix(std::size_t size) {
    double** matrix = new double* [size];

    for (std::size_t i = 0; i < size; ++i) {
        matrix[i] = new double[size];
        for (std::size_t j = 0; j < size; ++j) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void fillMatrixManually(double** matrix, std::size_t size) {
    std::cout << "\nВведите элементы матрицы " << size << "x" << size << ":\n";

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            std::cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            if (!(std::cin >> matrix[i][j])) {
                throw "Недопустимый ввод элемента матрицы!";
            }
        }
    }
}

void fillMatrixRandom(double** matrix, std::size_t size) {
    double minVal = 0;
    double maxVal = 0;

    std::cout << "\nВведите границы интервала для случайных чисел.\n";

    std::cout << "Минимальное значение: ";
    if (!(std::cin >> minVal)) {
        throw "Недопустимый ввод минимального значения!";
    }

    std::cout << "Максимальное значение: ";
    if (!(std::cin >> maxVal)) {
        throw "Недопустимый ввод максимального значения!";
    }

    if (minVal > maxVal) {
        std::swap(minVal, maxVal);
        std::cout << "Заметка: границы были автоматически поменяны местами.\n";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(minVal, maxVal);

    std::cout << "\nЗаполнение матрицы случайными числами из ["
        << minVal << ", " << maxVal << "]...\n";

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
}

void printMatrix(double** matrix, std::size_t size) {
    const std::int32_t COLUMN_WIDTH = 12;

    std::cout << "      ";
    for (std::size_t j = 0; j < size; ++j) {
        std::cout << std::setw(COLUMN_WIDTH) << "Стлб " << j + 1;
    }
    std::cout << "\n";

    for (std::size_t i = 0; i < size; ++i) {
        std::cout << "Стр " << std::setw(2) << i + 1 << ": ";
        for (std::size_t j = 0; j < size; ++j) {
            std::cout << std::setw(COLUMN_WIDTH) << matrix[i][j];
        }
        std::cout << "\n";
    }
}

void freeMatrix(double** matrix, std::size_t size) {
    if (!matrix) return;

    for (std::size_t i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double findMinElement(double** matrix, std::size_t size, std::size_t& minRow, std::size_t& minCol) {
    if (size == 0) return 0;

    double minVal = matrix[0][0];
    minRow = 0;
    minCol = 0;

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }

    return minVal;
}

double findMaxElement(double** matrix, std::size_t size, std::size_t& maxRow, std::size_t& maxCol) {
    if (size == 0) return 0;

    double maxVal = matrix[0][0];
    maxRow = 0;
    maxCol = 0;

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    return maxVal;
}

double scalarProduct(double** matrix, std::size_t size, std::size_t row, std::size_t col) {
    double product = 0;

    std::cout << "\nВычисление скалярного произведения:\n";
    std::cout << "Строка " << row + 1 << " x Столбец " << col + 1 << ":\n";

    for (std::size_t k = 0; k < size; ++k) {
        double term = matrix[row][k] * matrix[k][col];
        product += term;
        std::cout << "  " << matrix[row][k] << " * " << matrix[k][col]
            << " = " << term << "\n";
    }
    return product;
}


std::int32_t findMinK(double** matrix, std::size_t size) {
    if (size == 0) {
        return std::numeric_limits<std::int32_t>::max();
    }

    std::int32_t minK = std::numeric_limits<std::int32_t>::max();

    for (std::size_t i = 0; i < size; ++i) {
        double rowMax = matrix[i][0];
        for (std::size_t j = 1; j < size; ++j) {
            if (matrix[i][j] > rowMax) {
                rowMax = matrix[i][j];
            }
        }

        if (rowMax < std::numeric_limits<std::int32_t>::max()) {

            int32_t candidate{};
            double ceilValue = std::ceil(rowMax);

            if (std::abs(ceilValue - rowMax) < 1e-10) {
                candidate = static_cast<std::int32_t>(rowMax) + 1;
            }
            else {
                candidate = static_cast<std::int32_t>(ceilValue);
            }

            if (candidate < std::numeric_limits<std::int32_t>::max()) {
                if (candidate < minK) {
                    minK = candidate;
                }
            }
        }
    }

    return minK;
}
bool validateMatrix(double** matrix, std::size_t size) {
    if (!matrix) return false;

    for (std::size_t i = 0; i < size; ++i) {
        if (!matrix[i]) return false;
    }

    return true;
}