#include <iostream>
#include <windows.h>
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdint>
#include <array>

constexpr std::uint32_t MAX_SIZE{ 100 };

void setupRussianConsole();
std::uint32_t inputArraySize();
size_t chooseFillMethod();
size_t chooseArrayType();
void fillArrayFromKeyboard(double[], std::uint32_t);
void fillArrayRandom(double[], std::uint32_t);
void printArray(const double[], std::uint32_t);
double findMaxAbsolute(const double[], std::uint32_t);
bool findSumBetweenPositive(const double[], std::uint32_t, double&, std::string&);
void sortByFrequency(double[], std::uint32_t);
void printResults(double, bool, double, const std::string&, const double[], std::uint32_t);

void workWithStaticArray(std::uint32_t size, size_t method);
void workWithDynamicArray(std::uint32_t size, size_t method);
void workWithStdArray(std::uint32_t size, size_t method);
void workWithStdVector(std::uint32_t size, size_t method);

int main() {
	try {
		setupRussianConsole();
		std::uint32_t size = inputArraySize();
		size_t method = chooseFillMethod();
		size_t arrayType = chooseArrayType();
		switch (arrayType) {
		case 1:
			workWithStaticArray(size, method);
			break;
		case 2:
			workWithDynamicArray(size, method);
			break;
		case 3:
			workWithStdArray(size, method);
			break;
		case 4:
			workWithStdVector(size, method);
			break;
		default:
			std::cout << "Ошибка! Неверный тип массива.\n";
			return 1;
		}
	}
	catch (const char* error_msg) {
		std::cerr << error_msg << '\n';
		return 1;
	}
	return 0;
}

void setupRussianConsole() {
	std::setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
}

size_t chooseArrayType() {
	size_t choice;
	std::cout << "\n=== ВЫБОР ТИПА МАССИВА ===\n";
	std::cout << "1 - Статический массив\n";
	std::cout << "2 - Динамический массив\n";
	std::cout << "3 - std::array\n";
	std::cout << "4 - std::vector\n";
	std::cout << "Ваш выбор: ";

	if (!(std::cin >> choice)) {
		throw "Недопустимый ввод типа массива!";
	}

	while (choice < 1 || choice > 4) {
		std::cout << "Ошибка! Выберите от 1 до 4: ";
		if (!(std::cin >> choice)) {
			throw "Недопустимый ввод типа массива!";
		}
	}

	const char* names[] = { "", "Статический", "Динамический", "std::array", "std::vector" };
	std::cout << "Вы выбрали: " << names[choice] << "\n";
	return choice;
}

void workWithStaticArray(std::uint32_t size, size_t method) {
	double array[MAX_SIZE];
	if (method == 1) {
		fillArrayFromKeyboard(array, size);
	}
	else {
		fillArrayRandom(array, size);
	}

	std::cout << "\n=== СТАТИЧЕСКИЙ МАССИВ ===\n";
	printArray(array, size);

	double max_absolute = findMaxAbsolute(array, size);
	double sum = 0;
	std::string errorMsg;
	bool sumOk = findSumBetweenPositive(array, size, sum, errorMsg);
	double arrayCopy[MAX_SIZE]{};
	for (std::uint32_t i = 0; i < size; ++i) {
		arrayCopy[i] = array[i];
	}
	sortByFrequency(arrayCopy, size);

	printResults(max_absolute, sumOk, sum, errorMsg, arrayCopy, size);

}

void workWithDynamicArray(std::uint32_t size, size_t method) {
	std::cout << "\n=== РАБОТА С ДИНАМИЧЕСКИМ МАССИВОМ ===\n";
	double* dynamicArray = new double[size] {};

	try {
		if (method == 1) {
			fillArrayFromKeyboard(dynamicArray, size);
		}
		else {
			fillArrayRandom(dynamicArray, size);
		}

		printArray(dynamicArray, size);

		double max_absolute = findMaxAbsolute(dynamicArray, size);
		double sum = 0;
		std::string errorMsg;
		bool sumOk = findSumBetweenPositive(dynamicArray, size, sum, errorMsg);

		double* arrayCopy = new double[size] {};
		for (std::uint32_t i = 0; i < size; ++i) {
			arrayCopy[i] = dynamicArray[i];
		}
		sortByFrequency(arrayCopy, size);

		printResults(max_absolute, sumOk, sum, errorMsg, arrayCopy, size);
		delete[] arrayCopy;
		delete[] dynamicArray;
	}
	catch (...) {
		delete[] dynamicArray;
		throw;
	}
}

void workWithStdArray(std::uint32_t size, size_t method) {
	std::cout << "\n=== РАБОТА С STD::ARRAY ===\n";
	std::array<double, MAX_SIZE> stdArray{};

	if (method == 1) {
		fillArrayFromKeyboard(stdArray.data(), size);
	}
	else {
		fillArrayRandom(stdArray.data(), size);
	}

	printArray(stdArray.data(), size);
	double max_absolute = findMaxAbsolute(stdArray.data(), size);
	double sum = 0;
	std::string errorMsg;
	bool sumOk = findSumBetweenPositive(stdArray.data(), size, sum, errorMsg);
	std::array<double, MAX_SIZE> arrayCopy = stdArray;
	sortByFrequency(arrayCopy.data(), size);

	printResults(max_absolute, sumOk, sum, errorMsg, arrayCopy.data(), size);
}

void workWithStdVector(std::uint32_t size, size_t method) {
	std::cout << "\n=== РАБОТА С STD::VECTOR ===\n";

	std::vector<double> vec(size); 

	if (method == 1) {
		fillArrayFromKeyboard(vec.data(), size);
	}
	else {
		fillArrayRandom(vec.data(), size);
	}
	printArray(vec.data(), size);
	double maxAbs = findMaxAbsolute(vec.data(), size);
	double sum = 0;
	std::string errorMsg;
	bool sumOk = findSumBetweenPositive(vec.data(), size, sum, errorMsg);

	std::vector<double> vecCopy = vec;
	sortByFrequency(vecCopy.data(), size);

	printResults(maxAbs, sumOk, sum, errorMsg, vecCopy.data(), size);
}
std::uint32_t inputArraySize() {
	double size{};
	std::cout << "Введите количество элементов массива (от 1 до " << MAX_SIZE << "): ";
	if (!(std::cin >> size)) {
		throw "Ошибка! Недопустимый ввод!";
	}
	while (size < 1 || size > MAX_SIZE || size != static_cast<std::uint32_t>(size)) {
		std::cout << "Ошибка! Размер должен быть натуральным числом от 1 до " << MAX_SIZE << ". Повторите ввод: ";
		if (!(std::cin >> size)) {
			throw "Ошибка! Недопустимый ввод!";
		}
	}
	std::cout << "Успешный ввод! Размер: " << static_cast<std::uint32_t>(size) << std::endl;
	return static_cast<std::uint32_t>(size);
}
size_t chooseFillMethod() {
	size_t method;
	std::cout << "\nВыберите способ заполнения массива:\n";
	std::cout << "1 - Ввод с клавиатуры\n";
	std::cout << "2 - Заполнение случайными числами\n";
	std::cout << "Ваш выбор: ";
	if (!(std::cin >> method)) {
		throw "Ошибка! Недопустимый ввод!";
	}

	while (method != 1 && method != 2) {
		std::cout << "Ошибка! Выберите 1 или 2: ";
		if (!(std::cin >> method)) {
			throw "Ошибка! Недопустимый ввод!";
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
void fillArrayFromKeyboard(double array[], std::uint32_t size) {
	std::cout << "Введите " << size << " вещественных чисел:\n";
	for (uint32_t i = 0; i < size; ++i) {
		std::cout << "Элемент [" << i << "]: ";
		if (!(std::cin >> array[i])) {
			throw "Ошибка! Недопустимый ввод!";
		}
	}
}
void fillArrayRandom(double array[], std::uint32_t size) {
	double min, max;
	std::cout << "\nВведите границы интервала для случайных чисел:\n";
	std::cout << "Минимальное значение: ";
	if(!(std::cin >> min)) {
		throw "Недопустимый ввод минимального значения!";
	}
	std::cout << "Максимальное значение: ";
	if (!(std::cin >> max)) {
		throw "Недопустимый ввод максимального значения!";
	}
	if (min > max) {
		std::swap(min, max);
		std::cout << "Заметка: границы были автоматически поменяны местами.\n";
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(min, max);
	for (uint32_t i = 0; i < size; ++i) {
		array[i] = dist(gen);
	}
}
void printArray(const double array[], std::uint32_t size) {
	std::cout << "\nИсходный массив: [";
	for (std::uint32_t i = 0; i < size; ++i) {
		std::cout << array[i];
		if (i < size - 1) std::cout << ", ";
	}
	std::cout << "]\n";
}
double findMaxAbsolute(double array[], std::uint32_t size) {
	double max_value = array[0];
	double max_absolute = std::fabs(array[0]);
	for (uint32_t i = 1; i < size; ++i) {
		if (fabs(array[i]) > max_absolute) {
			max_absolute = std::fabs(array[i]);
			max_value = array[i];
		}
	}
	return max_value;
}
bool findSumBetweenPositive(const double array[], std::uint32_t size, double& sum, std::string& errorMsg) {
	sum = 0.0;
	errorMsg.clear();

	if (size < 3) {
		errorMsg = "Для вычисления суммы нужно как минимум 3 элемента.";
		return false;
	}

	std::int32_t firstPositiveIdx = -1;
	std::int32_t secondPositiveIdx = -1;

	for (std::uint32_t i = 0; i < size; ++i) {
		if (array[i] > 0.0) {
			firstPositiveIdx = static_cast<std::int32_t>(i);
			break;
		}
	}

	if (firstPositiveIdx == -1) {
		errorMsg = "В массиве нет положительных элементов.";
		return false;
	}

	for (std::uint32_t i = firstPositiveIdx + 1; i < size; ++i) {
		if (array[i] > 0.0) {
			secondPositiveIdx = static_cast<std::int32_t>(i);
			break;
		}
	}

	if (secondPositiveIdx == -1) {
		errorMsg = "В массиве только одно положительное число.";
		return false;
	}

	if (secondPositiveIdx == firstPositiveIdx + 1) {
		errorMsg = "Положительные числа стоят рядом. Между ними нет элементов для суммирования.";
		return false;
	}

	sum = 0.0;
	for (std::uint32_t i = firstPositiveIdx + 1; i < secondPositiveIdx; ++i) {
		sum += array[i];
	}

	return true;
}


void sortByFrequency(double array[], std::uint32_t size) {
	std::sort(array, array + size);
	struct ElementsFrequency {
		double value;
		std::uint32_t count;
	};
	std::vector <ElementsFrequency> frequency;
	for (std::uint32_t i = 0; i < size; ++i) {
		if (frequency.empty() || frequency.back().value != array[i]) {
			frequency.push_back({ array[i], 1 });
		}
		else {
			++frequency.back().count;
		}
	}
		std::sort(frequency.begin(), frequency.end(),
			[](const ElementsFrequency& a, const ElementsFrequency& b) {
				return a.count > b.count;
			});
		std::uint32_t index{};
		for (const auto& element : frequency) {
			for (size_t k = 0; k < element.count; ++k) {
				array[index] = element.value;
				++index;
			}
		}
}

void printResults(double max_absolute, bool sum_between, double sum, const std::string& sumError, const double array[], std::uint32_t size) {
	std::cout << "\n=== РЕЗУЛЬТАТЫ ВЫЧИСЛЕНИЙ ===\n";
	std::cout << "1. Максимальный по модулю элемент: " << max_absolute << std::endl;
	std::cout << "2. Сумма между первым и вторым положительными элементами: ";
		if (sum_between) {
		std::cout << sum << std::endl;
		} else {
				std::cout << "не может быть вычислена" << std::endl;
				std::cout << "   Причина: " << sumError << std::endl;
		}
	std::cout << "3. Массив после сортировки по частоте (в порядке убывания частоты и значения):\n";
	printArray(array, size);
}