//4. Enter a three - digit integer.Find the sum and product of the digits in the number.
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
		int32_t sum = first_digit + second_digit + third_digit;
		int32_t product = first_digit * second_digit * third_digit;
		std::cout << "The sum of digits = " << sum << "\nThe product of digits = " << product;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}