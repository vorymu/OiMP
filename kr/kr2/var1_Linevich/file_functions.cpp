#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>

bool openFiles(std::ifstream& inputFile, std::ofstream& outputFile) {
    inputFile.open("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Не могу открыть input.txt" << std::endl;
        return false;
    }
    outputFile.open("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не могу открыть output.txt" << std::endl;
        inputFile.close();
        return false;
    }
    return true;
}

bool checkFileNotEmpty(std::ifstream& inputFile) {
    char firstChar;
    inputFile.get(firstChar);

    if (inputFile.eof()) {
        return false;
    }

    inputFile.unget(); 
    inputFile.clear();

    return true;
}

std::string readDelimiters(std::ifstream& inputFile) {
    std::string delimiters;
    if (!std::getline(inputFile, delimiters)) {
        throw "Ошибка! Не удалось прочитать разделители.\n";
    }
    return delimiters;
}