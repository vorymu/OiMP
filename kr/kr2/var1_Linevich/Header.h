#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>

void setupRussianConsole();

bool isDelimiter(char, const std::string&);
bool isNumber(const std::string&);
bool isPrime(std::int32_t);
std::int32_t sumOfDigits(std::int32_t);
std::int32_t stringToInt(const std::string&);

bool openFiles(std::ifstream&, std::ofstream&);
bool checkFileNotEmpty(std::ifstream&);
std::string readDelimiters(std::ifstream&);

std::string processWord(const std::string&, bool&);
std::string processLine(const std::string&, const std::string&);
void processAndWriteLines(std::ifstream&, std::ofstream&,
    const std::string&);

void printStatistics(std::uint32_t, std::uint32_t);

#endif