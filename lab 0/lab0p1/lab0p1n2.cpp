/*2.	Enter a three-digit integer. Cross out the leftmost digit and add it to the right. Output the resulting number.*/
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
		int32_t last_two_digits = integer % 100;
		int32_t new_integer = last_two_digits * 10 + first_digit;
		std::cout << "The first digit from the left was crossed out and added to the right.\n" << "The resulting number = " << new_integer;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}
