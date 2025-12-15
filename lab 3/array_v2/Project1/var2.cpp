#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <array>

void InputSizeOfArray(int&);
double SumOfOdd(int32_t*, int32_t);
void CheckSize(int32_t);
void DynamicArray(int32_t);
void StaticArray(int32_t);
//void Vector();
//void Array(int32_t);
void HandleInput(int32_t*, int32_t);
void RandomInput(int32_t*, int32_t);
void PrintArray(int32_t*, int32_t);
double FindProductBetweenNegatives(int32_t*, int32_t);
void CompressArray(int32_t*, int32_t);
void CheckSizeOfStatic(int32_t);

constexpr int MAX_SIZE = 100;

int main() {
    try {
        int32_t size{};
        char choice1;
        std::cout << "Choose the type of array: 'd' for dynamic, 's' for static: ";
        std::cin >> choice1;

        if (choice1 == 'd') {
            DynamicArray(size);
        }
        else if (choice1 == 's') {
            StaticArray(size);
        }
       /* else if (choice1 == 'v') {
            Vector();
        }
        else if (choice1 == 'a') {
            Array(size);
        }*/
        else {
            throw "Invalid array type!";
        }
    }
    catch (const char* msg) {
        std::cout << msg;
    }

    return 0;
}

void InputSizeOfArray(int& size) {
    std::cout << "Input size: ";
    std::cin >> size;
}

void CheckSizeOfStatic(int32_t size) {
    if (size < 1 || size > MAX_SIZE)
        throw "Wrong size for static array!\n";
}

void CheckSize(int32_t size) {
    if (size < 1)
        throw "Wrong size! Size must be positive.\n";
}

double SumOfOdd(int32_t* arr, int32_t size) {
    int32_t sum{};
    for (int i = 1; i < size; i += 2) {
        sum += arr[i];
    }
    return sum;
}

void HandleInput(int32_t* arr, int32_t size) {
    std::cout << "Input elements of array: ";
    for (int32_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

void RandomInput(int32_t* arr, int32_t size) {
    srand(time(NULL));
    for (int32_t i = 0; i < size; ++i) {
        arr[i] = rand() % 10 - 5;
    }
}

void PrintArray(int32_t* arr, int32_t size) {
    std::cout << "Your array: ";
    for (int32_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

double FindProductBetweenNegatives(int32_t* arr, int32_t size) {
    int first_negative = -1, last_negative = -1;

    for (int i = 0; i < size; ++i) {
        if (arr[i] < 0) {
            if (first_negative == -1) first_negative = i;
            last_negative = i;
        }
    }

    if (first_negative == -1 || last_negative == -1 || first_negative == last_negative) {
        throw "There are no negative elements or only one negative element.\n";
    }

    double product = 1.0;
    for (int i = first_negative + 1; i < last_negative; ++i) {
        product *= arr[i];
    }

    return product;
}

void CompressArray(int32_t* arr, int32_t size) {
    int i = 0;
    for (int j = 0; j < size; ++j) {
        if (std::abs(arr[j]) > 1) {
            arr[i++] = arr[j];
        }
    }
    while (i < size) {
        arr[i++] = 0;
    }
}

// Функция для работы со статическим массивом
void StaticArray(int32_t size) {
    InputSizeOfArray(size);
    CheckSizeOfStatic(size);

    int32_t arr[MAX_SIZE]; 

    char choice2;
    std::cout << "Choose input method: 'k' for keyboard, 'r' for random: ";
    std::cin >> choice2;

    if (choice2 == 'k') {
        HandleInput(arr, size);
    }
    else if (choice2 == 'r') {
        RandomInput(arr, size);
    }
    else {
        throw "Invalid input method!";
    }

    PrintArray(arr, size);
    double sum = SumOfOdd(arr, size);
    std::cout << "Sum of elements with odd indices: " << sum << std::endl;

    try {
        double prod = FindProductBetweenNegatives(arr, size);
        std::cout << "Product of elements between first and last negative elements: " << prod << std::endl;
    }
    catch (const char* msg) {
        std::cout << msg;
    }

    CompressArray(arr, size);
    std::cout << "Array after compression: ";
    PrintArray(arr, size);
}

// Функция для работы с динамическим массивом
void DynamicArray(int32_t size) {
    InputSizeOfArray(size);
    CheckSize(size);

    int32_t* arr = new int32_t[size];

    char choice2;
    std::cout << "Choose input method: 'k' for keyboard, 'r' for random: ";
    std::cin >> choice2;

    if (choice2 == 'k') {
        HandleInput(arr, size);
    }
    else if (choice2 == 'r') {
        RandomInput(arr, size);
    }
    else {
        delete[] arr; 
        throw "Invalid input method!";
    }

    PrintArray(arr, size);
    double sum = SumOfOdd(arr, size);
    std::cout << "Sum of elements with odd indices: " << sum << std::endl;

    try {
        double prod = FindProductBetweenNegatives(arr, size);
        std::cout << "Product of elements between first and last negative elements: " << prod << std::endl;
    }
    catch (const char* msg) {
        std::cout << msg;
    }

    CompressArray(arr, size);
    std::cout << "Array after compression: ";
    PrintArray(arr, size);

    delete[] arr;
    arr = nullptr;
    std::cout << "Dynamic array memory freed.\n";
}
//// Функция для работы с vector
//void Vector() {
//    int32_t size;
//    InputSizeOfArray(size);
//    CheckSize(size);
//    std::vector<int32_t> arr(size); 
//    char choice2;
//    std::cout << "Choose input method: 'k' for keyboard, 'r' for random: ";
//    std::cin >> choice2;
//
//    if (choice2 == 'k') {
//        HandleInput(arr);
//    }
//    else if (choice2 == 'r') {
//        RandomInput(arr);
//    }
//    else {
//        throw "Invalid input method!";
//    }
//
//    PrintArray(arr, size);
//    double sum = AverageSum(arr, size);
//    std::cout << "Sum of elements with odd indices: " << sum << std::endl;
//
//    try {
//        double prod = FindProductBetweenNegatives(arr, size);
//        std::cout << "Product of elements between first and last negative elements: " << prod << std::endl;
//    }
//    catch (const char* msg) {
//        std::cout << msg;
//    }
//
//    CompressArray(arr, size);
//    std::cout << "Array after compression: ";
//    PrintArray(arr, size);
//
//    std::cout << "Vector size: " << arr.size() << std::endl;
//    std::cout << "Vector capacity: " << arr.capacity() << std::endl;
//}
