#include <iostream>
#include <cstdint>
#include <array>
#include <cmath>
#include <vector>
#include <string>
#include <windows.h>

void task3();
void task9();
void task12();
void task16();
void setupRussianConsole();

double enterNumber();
std::uint64_t validateInput(double);
std::array <std::uint16_t, 10> findFrequencyOfDigits(std::uint64_t);
std::uint16_t findTheMostFrequentDigit(const std::array<uint16_t, 10>&);
std::uint16_t findTheMaxCount(const std::array<std::uint16_t, 10>&, std::uint16_t);
void validadeUniqueFrequency(const std::array<std::uint16_t, 10>&, std::uint16_t, std::uint16_t);
std::uint64_t calculateMultiplier(std::uint64_t);
std::uint64_t addDigitsToBothSides(std::uint16_t, std::uint64_t, std::uint64_t);
void printResults(std::uint16_t, std::uint16_t, std::uint64_t);
void demonstrateArmstrong(std::uint64_t);

double enterN();
std::uint64_t validateSecondInput(double);
std::uint64_t findSumOfDivisors(std::uint64_t);
std::vector <std::pair<std::uint64_t, std::uint64_t>> findAmicableNumbers(std::uint64_t);
void printDivisors(std::uint64_t);
void printAmicablePairs(const std::vector<std::pair<std::uint64_t, std::uint64_t>>&);

double enterA();
double enterB();
std::uint64_t validateAInput(double);
std::uint64_t validateBInput(double);
void swap(std::uint64_t&, std::uint64_t&);
bool isArmstrongNumber(std::uint64_t);
std::vector<std::uint64_t> findArmstrongNumbers(std::uint64_t, std::uint64_t);
void demonstrateArmstrong(std::uint64_t);
void printArmstrongNumbers(std::uint64_t, std::uint64_t, std::vector<std::uint64_t>);

double enterNumberA();
double enterNumberB();
std::uint64_t validateNumberAInput(double);
std::uint64_t validateNumberBInput(double);
bool canObtainByErasing(std::uint64_t, std::uint64_t);
void demonstrateErasing(std::uint64_t, std::uint64_t);
void printAnswer(std::uint64_t, std::uint64_t, bool);

int main() {
	try {
		setupRussianConsole();
		task3();
		task9();
		task12();
		task16();
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

void task3() {
	double input = enterNumber();
	std::uint64_t number = validateInput(input);
	std::array <uint16_t, 10> digits_count = findFrequencyOfDigits(number);
	std::uint16_t most_frequent_digit = findTheMostFrequentDigit(digits_count);
	std::uint16_t max_count = findTheMaxCount(digits_count, most_frequent_digit);
	validadeUniqueFrequency(digits_count, max_count, most_frequent_digit);
	std::uint64_t multiplier = calculateMultiplier(number);
	std::uint64_t result = addDigitsToBothSides(most_frequent_digit, multiplier, number);
	printResults(most_frequent_digit, max_count, result);
}
void task9() {
	double second_input = enterN();
	std::uint64_t N = validateSecondInput(second_input);
	std::vector <std::pair<std::uint64_t, std::uint64_t>> amicablePairs = findAmicableNumbers(N);
	printAmicablePairs(amicablePairs);
}
void task12() {
	double input_a = enterA();
	std::uint64_t a = validateAInput(input_a);
	double input_b = enterB();
	std::uint64_t b = validateBInput(input_b);
	swap(a, b);
	std::vector<std::uint64_t> armstrong_numbers = findArmstrongNumbers(a, b);
	printArmstrongNumbers(a, b, armstrong_numbers);
}
void task16() {
	double input_A = enterNumberA();
	double input_B = enterNumberB();
	std::uint64_t B = validateNumberBInput(input_B);
	std::uint64_t A = validateNumberAInput(input_A);
	bool second_result = canObtainByErasing(A, B);
	printAnswer(A, B, second_result);
}


double enterNumber() {
	double input{};
	std::cout << "3. Программа добавляет слева и справа в записи числа цифру, повторяющуюся максимальное число раз;\nВведите натуральное число n = ";
	if (!(std::cin >> input)) {
		throw "Error: Invalid input!";
	}
	return input;
}
std::uint64_t validateInput(double input) {
	std::uint64_t integer_part = static_cast<std::uint64_t>(input);
	if (integer_part <= 0 || input > integer_part) {
		throw "Error: n should be integer!";
	}
	return integer_part;
}
std::array<std::uint16_t, 10> findFrequencyOfDigits(std::uint64_t number) {
	std::uint64_t first_copy = number;
	std::array<uint16_t,10> digits_count{};
	while (first_copy > 0) {
		std::uint16_t digit = first_copy % 10;
		++digits_count[digit];
		first_copy /= 10;
	}
	return digits_count;
}
std::uint16_t findTheMostFrequentDigit(const std::array<std::uint16_t, 10>& digits_count) {
	std::uint16_t max_count{};
	std::uint16_t most_frequent_digit{};
	for (size_t i = 0; i < 10; ++i) {
		if (digits_count[i] > max_count) {
			max_count = digits_count[i];
			most_frequent_digit = i;
		}
	}
	return most_frequent_digit;
}
std::uint16_t findTheMaxCount(const std::array<std::uint16_t, 10>& digits_count, std::uint16_t most_frequent_digit) {
	std::uint16_t max_count = digits_count[most_frequent_digit];
	return max_count;
}
void validadeUniqueFrequency(const std::array<std::uint16_t, 10>& digits_count, std::uint16_t max_count, std::uint16_t most_frequent_digit) {
	for (size_t i = 0; i < 10; ++i) {
		if (digits_count[i] == max_count && i != most_frequent_digit) {
			throw "Error: Multiple digits have the same maximum frequency!";
		}
	}
}
std::uint64_t calculateMultiplier(std::uint64_t number) {
	std::uint64_t multiplier = 1;
	for (std::uint64_t second_copy = number; second_copy > 0; second_copy /= 10) {
		multiplier *= 10;
	}
	return multiplier;
}
std::uint64_t addDigitsToBothSides(uint16_t most_frequent_digit, std::uint64_t multiplier, std::uint64_t number) {
	std::uint64_t result = (most_frequent_digit * multiplier + number) * 10 + most_frequent_digit;
	return result;
}
void printResults(uint16_t most_frequent_digit, std::uint16_t max_count, std::uint64_t result) {
	std::cout << "\n=== РЕЗУЛЬТАТ: ===\n";
	std::cout << "Цифра, повторяющаяся максимальное число раз: " << most_frequent_digit << " (встретилось " << max_count << " раз)\n" << result << '\n';
}


double enterN() {
	double second_input{};
	std::cout << "\n\n9. Программа, которая для заданного натурального числа N находит, не превышающие это число, дружественные;\nВведите натуральное число N = ";
	if (!(std::cin >> second_input)) {
		throw "Error: Invalid input!";
	}
	return second_input;
}
std::uint64_t validateSecondInput(double second_input) {
	std::uint64_t integer_part = static_cast<std::uint64_t>(second_input);
	if (integer_part <= 0 || second_input > integer_part) {
		throw "Error: N should be integer!";
	}
	return integer_part;
}
std::uint64_t findSumOfDivisors(std::uint64_t N) {
	if (N <= 1) return 0;
	std::uint64_t sum = 1;
	std::uint64_t limit = static_cast<std::uint64_t>(std::sqrt(N));
	for (std::uint64_t i = 2; i < limit; ++i) {
		if (N % i == 0) {
			sum += i;
			if (i != N / i) {
				sum += N / i;
			}
		}
	}
	return sum;
}
std::vector <std::pair<std::uint64_t, std::uint64_t>> findAmicableNumbers(std::uint64_t N) {
	std::vector<std::pair<uint64_t, uint64_t>> amicablePairs;
	std::vector<bool> processed(N + 1, false);
	for (std::uint64_t a = 2; a < N; ++a) {
		if (!(processed[a])) {
			std::uint64_t b = findSumOfDivisors(a);
			if (b > a && b <= N && a == findSumOfDivisors(b)) {
				amicablePairs.push_back({ a,b });
				processed[a] = true;
				if (b <= N) processed[b] = true;
		}
		}
		
	}
	return amicablePairs;
}
void printDivisors(std::uint64_t N) {
	std::vector<std::uint64_t> divisors = { 1 };
	std::uint64_t limit = static_cast<std::uint64_t>(std::sqrt(N));
	for (size_t i = 2; i <= limit; ++i) {
		if (N % i == 0) {
			divisors.push_back(i);
			if (N / i != i) {
				divisors.push_back(N / i);
			}
		}
	}
	for (size_t i = 0; i < divisors.size(); ++i) {
		for (size_t j = 1 + i; j < divisors.size(); ++j) {
			if (divisors[i] > divisors[j]) {
				std::swap(divisors[i], divisors[j]);
			}
		}
	}
	for (size_t i = 0; i < divisors.size(); ++i) {
		std::cout << divisors[i];
		if (i < divisors.size() - 1) {
			std::cout << '+';
		}
	}
}
void printAmicablePairs(const std::vector<std::pair<std::uint64_t, std::uint64_t>>& amicablePairs) {
	std::cout << "\n=== ПАРЫ ДРУЖЕСТВЕННЫХ ЧИСЕЛ МЕНЬШЕ ЧИСЛА N: === \n";
	if (amicablePairs.empty()) {
		std::cout << "Нет пар дружественных чисел.\n";
	}
	else {
		std::cout << "Найдено " << amicablePairs.size() << " пар дружественных чисел: \n";
		}
		size_t i = 1;
		for (const auto& pair : amicablePairs) {
			std::cout << (i) << ". ";
			std::cout << pair.first << " и " << pair.second << std::endl;
			std::cout << "  " << pair.first << " = "; printDivisors(pair.second); std::cout << std::endl;
			std::cout << "  " << pair.second << " = "; printDivisors(pair.first); std::cout << std::endl << std::endl;
			++i;
		}
}


double enterA() {
	double input_a{};
	std::cout << "\n12. Программа, которая на заданном отрезке [a,b] натурального ряда чисел находит все числа Армстронга;\nВведите натуральное число а = ";
	if (!(std::cin >> input_a)) {
		throw "Error: Invalid input!";
	}
	return input_a;
}
double enterB() {
	double input_b{};
	std::cout << "Введите натуральное число b = ";
	if (!(std::cin >> input_b)) {
		throw "Error: Invalid input!";
	}
	return input_b;
}
std::uint64_t validateAInput(double input_a) {
	std::uint64_t integer_a_part = static_cast<std::uint64_t>(input_a);
	if (integer_a_part <= 0 || input_a > integer_a_part) {
		throw "Error: a should be integer!";
	}
	return integer_a_part;
}
std::uint64_t validateBInput(double input_b) {
	std::uint64_t integer_b_part = static_cast<std::uint64_t>(input_b);
	if (integer_b_part <= 0 || input_b > integer_b_part) {
		throw "Error: b should be integer!";
	}
	return integer_b_part;
}
void swap(std::uint64_t& a, std::uint64_t& b) {
	if (a > b) {
		std::cout << "\nЗамечание: границы отрезка были автоматически упорядочены:\n";
		std::cout << "Исходный ввод: [" << a << ", " << b << "]\n";
		std::swap(a, b);
		std::cout << "Рабочий диапазон: [" << a << ", " << b << "]\n";
	}
}
bool isArmstrongNumber(std::uint64_t number) {
	std::uint64_t temp = number;
	size_t digits_counter{};
	while (temp > 0) {
		++digits_counter;
		temp /= 10;
	}
	temp = number;
	std::uint64_t sum{};
	while (temp > 0) {
		size_t digit = temp % 10;
		sum += static_cast<std::uint64_t>(std::pow(digit, digits_counter));
		temp /= 10;
	}
	return sum == number;
}
std::vector<std::uint64_t> findArmstrongNumbers(std::uint64_t a, std::uint64_t b) {
	std::vector<std::uint64_t> armstrong_numbers;
	for (std::uint64_t i = a; i <= b; ++i) {
		if (isArmstrongNumber(i)) {
			armstrong_numbers.push_back(i);
		}
	}
	return armstrong_numbers;
}
void demonstrateArmstrong(std::uint64_t number) {
	if (!isArmstrongNumber(number)) return;
	std::uint64_t temp = number;
	size_t digits_counter{};
	while (temp > 0) {
		++digits_counter;
		temp /= 10;
	}
	std::cout << number << " = ";
	temp = number;
	bool first = true;
	std::vector<size_t> digits;
	while (temp > 0) {
		digits.push_back(temp % 10);
		temp /= 10;
	}
	for (std::int64_t i = digits.size() - 1; i >= 0; --i) {
		if (!first) {
			std::cout << " + ";
		}
		std::cout << digits[i] << "^" << digits_counter;
		first = false;
	}
}
void printArmstrongNumbers(std::uint64_t a, std::uint64_t b, std::vector<std::uint64_t> armstrong_numbers) {
	std::cout << "\n=== ЧИСЛА АРМСТРОНГА НА ОТРЕЗКЕ [" << a << ", " << b << "] ===\n";
    
    if (armstrong_numbers.empty()) {
        std::cout << "Чисел Армстронга не найдено.\n";
    } else {
		std::cout << "Найдено " << armstrong_numbers.size() << " чисел Армстронга:\n";
        
        for (size_t i = 0; i < armstrong_numbers.size(); ++i) {
            std::cout << (i + 1) << ". ";
            demonstrateArmstrong(armstrong_numbers[i]);
            std::cout << std::endl;
        }
    }
}


double enterNumberA() {
	double input_A{};
	std::cout << "\n\n16. Программа, которая для заданных натуральных чисел А и В определяет возможность получения числа А вычеркиванием цифр из числа В;\nВведите натуральное число A = ";
	if (!(std::cin >> input_A)) {
		throw "Error: Invalid input!";
	}
	return input_A;
}
double enterNumberB() {
	double input_B{};
	std::cout << "Введите натуральное число B = ";
	if (!(std::cin >> input_B)) {
		throw "Error: Invalid input!";
	}
	return input_B;
}
std::uint64_t validateNumberAInput(double input_A) {
	std::uint64_t integer_A_part = static_cast<std::uint64_t>(input_A);
	if (integer_A_part <= 0 || input_A > integer_A_part) {
		throw "Error: A should be integer!";
	}
	return integer_A_part;
}
std::uint64_t validateNumberBInput(double input_B) {
	std::uint64_t integer_B_part = static_cast<std::uint64_t>(input_B);
	if (integer_B_part <= 0 || input_B > integer_B_part) {
		throw "Error: B should be integer!";
	}
	return integer_B_part;
}
bool canObtainByErasing(std::uint64_t A, std::uint64_t B) {
	std::string strA = std::to_string(A);
	std::string strB = std::to_string(B);
	if (strA.length() > strB.length()) {
		return false;
	}
	size_t i{};
	size_t j{};
	while (i < strA.length() && j < strB.length()) {
		if (strA[i] == strB[j]) {
			++i;
		}
		++j;
	}
	return i == strA.length();
}
void printAnswer(std::uint64_t A, std::uint64_t B, bool second_result) {
	std::cout << "\n=== РЕЗУЛЬТАТ ===\n";
	std::cout << "Число A: " << A << std::endl;
	std::cout << "Число B: " << B << std::endl;
	if (second_result) {
		std::cout << "МОЖНО получить число " << A << " вычеркиванием цифр из числа " << B << std::endl;
		demonstrateErasing(A, B);
	}
	else {
		std::cout << "НЕВОЗМОЖНО получить число " << A << " вычеркиванием цифр из числа " << B << std::endl;
	}
}
void demonstrateErasing(std::uint64_t A, std::uint64_t B) {
	std::string strA = std::to_string(A);
	std::string strB = std::to_string(B);

	std::cout << "Демонстрация:\n";
	std::cout << "B = " << strB << std::endl;

	std::string second_result;
	size_t i = 0;

	for (size_t j = 0; j < strB.length(); ++j) {
		if (i < strA.length() && strB[j] == strA[i]) {
			second_result += strB[j];
			i++;
			std::cout << "  Оставляем цифру: " << strB[j] << " (позиция " << j + 1 << ")" << std::endl;
		}
		else {
			std::cout << "  Вычеркиваем цифру: " << strB[j] << " (позиция " << j + 1 << ")" << std::endl;
		}
	}

	std::cout << "Полученное число: " << second_result << std::endl;
	std::cout << "Целевое число A: " << strA << std::endl;
}
