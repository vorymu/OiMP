#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint> 

int main()
{
	double sum{};
	int32_t n = 1;
	double x{};
	double k{};
	int32_t check_k{};
	try {
		std::cout << "ln(1+x) = \nInput x (x should be in (-1;+1]) = ";
		if (!(std::cin >> x)) {
			throw "Error: Invalid input!";
		}
		if (x <= -1.0 || x > 1.0) {
			throw "Error: x should be in(-1; 1]!";
		}
		std::cout << "Input integer k = ";
		if (!(std::cin >> k)) {
			throw "Error: Invalid input!";
		}
		check_k = k;
		if (k <= 1 || k > check_k)
		{
			throw "Error: k should be integer > 1!";
		}
		double epsilon = 1.0;
		for (int32_t i = 0; i < k; ++i)
		{
			epsilon /= 10.0;
		}
		double term = x;
		std::cout << "\nComputing process:";
		std::cout << "epsilon = " << epsilon << '\n';
		while (fabs(term) >= epsilon)
		{
			sum += term;
			std::cout << "n=" << n << ", term =" << term << ", sum=" << sum << '\n';
			term = -term * x * n / (n + 1);
			++n;
			if (n > 10000) {
				throw "Error: Too many iterations!";
			}
		}
		std::cout << std::setprecision(k+1.0);
		std::cout << "Taylor's series = " << sum << '\n';
		double real_value{ std::log(1 + x) };
		std::cout << "\n ln(1+x) = " << real_value << std::endl;
		std::cout << "Difference = " << std::fixed << std::fabs(sum - real_value) << std::endl;
	}
	catch (const char* error_msg) {
		std::cerr << error_msg << std::endl;
		return 1;
	}

	return 0;
}