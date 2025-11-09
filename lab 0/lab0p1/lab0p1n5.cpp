//5. Enter a three - digit integer.Reverse it.
#include <iostream>
int main() {
	int32_t integer{};
	try {
		std::cout << "Enter a three-digit integer: ";
		if (!(std::cin >> integer)) {
			throw "Error: Should be an integer!";
		}
		if (integer < 100 || integer > 999) {
			throw "Error: Should be a three-digit integer!";
		}
		int32_t first_digit = integer / 100;
		int32_t second_digit = (integer / 10) % 10;
		int32_t third_digit = integer % 10;
		int32_t reversed_result = third_digit * 100 + second_digit * 10 + first_digit;
		std::cout << "Reversed result = " << reversed_result;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}