//3. Enter a three - digit integer.Duplicate each digit of the number.Output the resulting number.
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
		int32_t new_integer = integer * 1000 + integer;
		std::cout << "Each digit of the number was duplicated.\n" << "The resulting number = " << new_integer;
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}