#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

void setupRussianConsole() {
    std::setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

bool isDelimiter(char ch, const std::string& delimiters) {
    for (char d : delimiters) {
        if (ch == d) {
            return true;
        }
    }
    return false;
}

bool isNumber(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

bool isPrime(std::int32_t number) {
    if (number < 2) {
        return false;
    }
    if (number == 2) {
        return true;
    }
    if (number % 2 == 0) {
        return false;
    }
    for (std::int32_t i = 3; i * i <= number; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

std::int32_t sumOfDigits(std::int32_t number) {
    std::int32_t sum{};
    if (number < 0) {
        number = -number;
    }
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

std::int32_t stringToInt(const std::string& str) {
    std::int32_t result{};
    for (char c : str) {
        result = result * 10 + (c - '0');
    }
    return result;
}

std::string processLine(const std::string& line, const std::string& delimiters) {
    std::string result = "";
    std::string word = "";
    bool hasPrimeInLine = false;

    for (size_t i = 0; i <= line.length(); i++) {
        char currentChar;
        if (i == line.length()) {
            currentChar = '\0';
        }
        else {
            currentChar = line[i];
        }

        if (isDelimiter(currentChar, delimiters) || currentChar == '\0') {
            if (!word.empty()) {
                result += processWord(word, hasPrimeInLine);
                word = "";
            }

            if (i < line.length() && currentChar != '\0') {
                result += currentChar;
            }
        }
        else {
            word += currentChar;
        }
    }

    if (!hasPrimeInLine) {
        return "нет простых чисел в строке: " + line;
    }

    return result;
}

std::string processWord(const std::string& word, bool& hasPrime) {
    std::cout << "  Слово: \"" << word << "\"";

    if (!isNumber(word)) {
        std::cout << " - не число" << std::endl;
        return word;
    }

    std::int32_t num = stringToInt(word);
    std::cout << " - ЧИСЛО: " << num;

    if (!isPrime(num)) {
        std::cout << " (не простое)" << std::endl;
        return word;
    }
    std::cout << " (ПРОСТОЕ)";
    std::cout << " -> сумма цифр: " << sumOfDigits(num) << std::endl;

    hasPrime = true;
    return std::to_string(sumOfDigits(num));
}

void processAndWriteLines(std::ifstream& inputFile, std::ofstream& outputFile,
    const std::string& delimiters) {
    std::string line;
    std::uint32_t lineNumber = 0;
    std::uint32_t linesWithPrimes = 0;

    while (std::getline(inputFile, line)) {
        lineNumber++;
        std::cout << "\nСтрока " << lineNumber << ": \"" << line << "\"" << std::endl;

        std::string result = processLine(line, delimiters);

        if (result.find("нет простых чисел в строке") == std::string::npos) {
            linesWithPrimes++;
        }

        outputFile << result << std::endl;
        std::cout << "Результат: \"" << result << "\"" << std::endl;
    }

    printStatistics(lineNumber, linesWithPrimes);
}

void printStatistics(std::uint32_t totalLines, std::uint32_t linesWithPrimes) {
    if (totalLines == 0) {
        std::cout << "\nФайл не содержит строк для обработки." << std::endl;
        return;
    }

    std::cout << "\nСТАТИСТИКА:" << std::endl;
    std::cout << "Всего строк обработано: " << totalLines << std::endl;
    std::cout << "Строк с простыми числами: " << linesWithPrimes << std::endl;
    std::cout << "Строк без простых чисел: " << (totalLines - linesWithPrimes) << std::endl;
}