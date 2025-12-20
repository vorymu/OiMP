#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>

bool IsDelimiter(char symbol, const char* delimiters);
bool IsVowel(char symbol);
void CopyWordWithCapitalization(const char* source, char* destination, std::size_t length);
void ProcessString(const char* inputString, const char* delimiters, char* resultString);

int main()
{
    const std::size_t MAX_LENGTH = 301;

    char inputString[MAX_LENGTH];
    char delimiters[MAX_LENGTH];
    char resultString[MAX_LENGTH * 2];

    std::cout << "Enter delimiter characters: ";
    std::cin.getline(delimiters, MAX_LENGTH);

    if (*delimiters == '\0')
    {
        std::cerr << "Error: no delimiter characters specified." << std::endl;
        return 1;
    }

    std::cout << "Enter string (up to 300 characters): ";
    std::cin.getline(inputString, MAX_LENGTH);

    std::size_t inputLength = 0;
    while (inputString[inputLength] != '\0' && inputLength < MAX_LENGTH)
    {
        ++inputLength;
    }

    if (inputLength >= MAX_LENGTH - 1)
    {
        std::cerr << "Error: string is too long or does not contain null terminator.\n";
        return 1;
    }

    ProcessString(inputString, delimiters, resultString);

    if (*resultString == '\0')
    {
        std::cout << "No words starting with vowels found in the string." << std::endl;
    }
    else
    {
        std::cout << "Result: " << resultString << std::endl;
    }

    return 0;
}

bool IsDelimiter(char symbol, const char* delimiters)
{
    while (*delimiters != '\0')
    {
        if (symbol == *delimiters)
        {
            return true;
        }
        ++delimiters;
    }
    return false;
}

bool IsVowel(char symbol)
{
    char lowerSymbol = static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
    return (lowerSymbol == 'a' || lowerSymbol == 'e' || lowerSymbol == 'i' ||
        lowerSymbol == 'o' || lowerSymbol == 'u' || lowerSymbol == 'y');
}

void CopyWordWithCapitalization(const char* source, char* destination, std::size_t length)
{
    if (length == 0)
    {
        return;
    }

    *destination = static_cast<char>(std::toupper(static_cast<unsigned char>(*source)));
    ++destination;

    for (std::size_t i = 1; i < length; ++i)
    {
        *destination = source[i];
        ++destination;
    }

    *destination = '\0';
}

void ProcessString(const char* inputString, const char* delimiters, char* resultString)
{
    if (inputString == nullptr || delimiters == nullptr || resultString == nullptr)
    {
        std::cerr << "Error: null pointer in function parameters." << std::endl;
        *resultString = '\0';
        return;
    }

    if (*inputString == '\0')
    {
        *resultString = '\0';
        std::cout << "Input string is empty." << std::endl;
        return;
    }

    const char* currentPosition = inputString;
    bool isFirstWord = true;

    while (*currentPosition != '\0')
    {
        while (*currentPosition != '\0' && IsDelimiter(*currentPosition, delimiters))
        {
            ++currentPosition;
        }

        const char* wordStart = currentPosition;

        while (*currentPosition != '\0' && !IsDelimiter(*currentPosition, delimiters))
        {
            ++currentPosition;
        }

        std::size_t wordLength = static_cast<std::size_t>(currentPosition - wordStart);

        if (wordLength > 0 && IsVowel(*wordStart))
        {
            if (!isFirstWord)
            {
                *resultString = ' ';
                ++resultString;
            }

            CopyWordWithCapitalization(wordStart, resultString, wordLength);

            resultString += wordLength;

            isFirstWord = false;
        }
    }

    *resultString = '\0';
}