#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "Header.h"
int main() {
    setupRussianConsole();

    try {
        std::ifstream inputFile;
        std::ofstream outputFile;

        if (!openFiles(inputFile, outputFile)) {
            throw "Ошибка! Не получилось открыть файл\n";
        }
        if (!checkFileNotEmpty(inputFile)) {
            throw "Ошибка! Файл input.txt пустой.\n";
        }

        std::string delimiters = readDelimiters(inputFile);
        std::cout << "Разделители: \"" << delimiters << "\"" << std::endl;

        processAndWriteLines(inputFile, outputFile, delimiters);

        inputFile.close();
        outputFile.close();

        std::cout << "\nОбработка завершена! Результат в output.txt\n";
        return 0;
    }
    catch (const char* error_msg) {
        std::cerr << error_msg << '\n';
        return 1;
    }
}