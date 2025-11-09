//8. Enter the coordinates of the triangle's vertices: (x1, y1), (x2, y2), (x3, y3). Find its perimeter and area. To find the sides of the triangle a, b, and c, use the formula for finding the distance between points on a plane. To calculate the area of the triangle, use the Heron's formula : S = p(p a)(p b)(p c), where p = (a + b + c) / 2 is the semi - perimeter.
#include <iostream>
int main() {
    double x1{};
    double y1{};
    double x2{};
    double y2{};
    double x3{};
    double y3{};
        std::cout << "Input x1: \n" << "x1 = ";
        if (!(std::cin >> x1)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Input y1: \n" << "y1 = ";
        if (!(std::cin >> y1)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Input x2: \n" << "x2 = ";
        if (!(std::cin >> x2)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Input y2: \n" << "y2 = ";
        if (!(std::cin >> y2)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Input x3: \n" << "x3 = ";
        if (!(std::cin >> x3)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Input y3: \n" << "y3 = ";
        if (!(std::cin >> y3)) {
            std::cout << "Error: Invalid input!";
            return 1;
        }
        std::cout << "Your coordinates: \n" << '(' << x1 << ',' << y1 << "); " << '(' << x2 << ',' << y2 << "); " << '(' << x3 << ',' << y3 << ") \n";
        double the_first_side = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        double the_second_side = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        double the_third_side = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
        if (the_first_side + the_second_side <= the_third_side || the_first_side + the_third_side <= the_second_side || the_second_side + the_third_side <= the_first_side) {
            std::cout << "Error: These points do not form a triangle!";
            return 1;
        }
        double P = the_first_side + the_second_side + the_third_side;
        double p = P / 2;
        double S = sqrt(abs(p * (p - the_first_side) * (p - the_second_side) * (p - the_third_side)));
        std::cout << "Perimeter P = " << P << ", Area S = " << S;
    return 0;

}