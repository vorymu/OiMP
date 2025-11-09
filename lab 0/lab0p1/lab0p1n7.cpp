//Enter the area S of the circle. Find the diameter D and the circumference L of, given that L = 2PiR, S = PiR^2.Use 3.1415927 as the value of Pi.
#include <iostream>
int main()
{
    double S{};
    std::cout << "Input the area of the circle: \n" << "S = ";
    try {
        if (!(std::cin >> S)) {
            throw "Error: Invalid input!";
        }
        if (S <= 0) {
            throw "Error: The area must be positive!";
        }
        const double Pi(3.1415927);
        double R = std::sqrt(S / Pi);
        double D = 2 * R;
        double L = 2* Pi * R;
        std::cout << "Circumference L = " << L << "\nDiameter D = " << D;
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}