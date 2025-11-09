// 1.	Ввести сторону квадрата a. Найти периметр  и площадь квадрата.
#include <iostream>
int main() {
	try {
		std::cout << "Input the side of the square, side = ";
		double side{};
		if (!(std::cin >> side)) {
			throw "Should be number!";
		}
		if (side < 0) {
			throw "Should be positive!";
		}
		double P{ side * 4 };
		double S{ side * side };
		std::cout << "P = " << P << '\n' << "S = " << S << '\n';
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}