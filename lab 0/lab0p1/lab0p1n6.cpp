//6. Enter the circumference L. Find the radius R and the area S of the circle, given that L = 2PiR, S = PiR^2.Use 3.1415927 as the value of Pi.
#include <iostream>
int main() {
    double L{};
    std::cout << "Input the circumference: \n" << "L = ";
    try {
        if (!(std::cin >> L)) {
            throw "Error: Invalid input!";
        }
        if (L <= 0) {
            throw "Error: Circumference must be positive!";
        }
        const double Pi(3.1415927);
        double R = L / (2 * Pi);
        double S = Pi * R * R;
        std::cout << "Radius R = " << R << "\nArea S = " << S;
    }
    catch (const char* msg) {
        std::cout << msg;
    }
    return 0;
}