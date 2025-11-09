//9. The train's arrival time and departure time are known in hours and minutes. Determine the train's parking time.
#include <iostream>

int main()
{
    int32_t arrival_hours{};
    int32_t arrival_minutes{};
    int32_t departure_hours{};
    int32_t departure_minutes{};
    char separator;
    std::cout << "Input arrival time HH:MM : \n";
    if (!(std::cin >> arrival_hours >> separator >> arrival_minutes)) {
        std::cout << "Error: Invalid input!";
        return 1;
    }
    std::cout << "Input departure time HH:MM : \n";
    if (!(std::cin >> departure_hours >> separator >> departure_minutes)) {
        std::cout << "Error: Invalid input!";
        return 1;
    }
    if (arrival_hours > 23 || departure_hours > 23 || arrival_minutes > 59 || departure_minutes > 59)
    {
        std::cout << "Error: Such time doesn't exist!";
        return 1;
    }
    if (arrival_hours * 60 + arrival_minutes > departure_hours * 60 + departure_minutes){
            std::cout << "Error: Departure time shouid be later than arrival!";
            return 1;
        }
    if (arrival_minutes > departure_minutes) {
        --departure_hours;
        departure_minutes = departure_minutes + 60;        
        }
    int32_t parking_hours = departure_hours - arrival_hours;
    int32_t parking_minutes = departure_minutes - arrival_minutes;
    if (departure_minutes - arrival_minutes < 10) {
        std::cout << "Parking time: " << parking_hours << separator << 0 << parking_minutes;
        }
        else {
                std::cout << "Parking time: " << parking_hours << separator << parking_minutes;
            }
    return 0;
    }