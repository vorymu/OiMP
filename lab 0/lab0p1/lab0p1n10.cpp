//In some country, there is a special calendar.It has 12 months, and each month has 30 days.Determine a person's age if their date of birth is known. The input data includes the date of birth, which consists of the day, month, year, and the date for determining the age in the same format.
#include <iostream>
int main() {
	int32_t birth_day{};
	int32_t birth_month{};
	int32_t birth_year{};
	int32_t current_day{};
	int32_t current_month{};
	int32_t current_year{};
	char separator;
	std::cout << "Input birth date DD/MM/YYYY: \n";
	if (!(std::cin >> birth_day >> separator >> birth_month >> separator >> birth_year)) {
	std::cout << "Error: Invalid input!";
	return 1;
	}
	std::cout << "Input current date DD/MM/YYYY: \n";
	if (!(std::cin >> current_day >> separator >> current_month >> separator >> current_year)) {
		std::cout << "Error: Invalid input!";
		return 1;
	}
	if (birth_day < 1 || birth_day > 30 || current_day < 1 || current_day > 30 ||
		birth_month < 1 || birth_month > 12 || current_month < 1 || current_month > 12 ||
		birth_year < 0 || current_year < 0) {
		std::cout << "Error: Such date doesn't exist";
		return 1;
	}
	int32_t birth_total_days = birth_year * 360 + (birth_month - 1) * 30 + (birth_day - 1);
	int32_t current_total_days = current_year * 360 + (current_month - 1) * 30 + (current_day - 1);
	int32_t diff_days = current_total_days - birth_total_days;
	int32_t age_years = diff_days / 360;
	int32_t age_months = (diff_days % 360) / 30;
	int32_t age_days = (diff_days % 360) % 30;
	std::cout << "Age: " << age_years << " years, " << age_months << " months, " << age_days << " days";
	return 0;
}