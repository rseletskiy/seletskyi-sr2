#include "student.hpp"
#include "examples.hpp"

#include <iomanip>
#include <memory>
#include <vector>

int main() {
    std::cout << "Task 1: Student\n";
    Student first;
    Student second("Roman Seletskyi", "KN-11", 1);
    first.output();
    second.output();
    second.setGroup("KN-21");
    second.setCourse(2);
    std::cout << "After update:\n";
    second.output();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nTask 2: Tovar\n";
    Tovar book("Book", 125.50, 3);
    const Tovar pen("Pen", 20.00, 10);
    book.output();
    pen.output();
    book.sell(2);
    std::cout << "After selling two books:\n";
    book.output();

    std::cout << "\nTask 4: Prylad\n";
    const Prylad lamp("Lamp", 60);
    lamp.output();
    std::cout << "Energy for 5 hours: " << lamp.energyKwh(5) << " kWh\n";

    std::cout << "\nTask 5: Payment\n";
    const Payment empty;
    const Payment paid(15499, "UAH");
    empty.output();
    paid.output();

    std::cout << "\nTask 6: Vehicle hierarchy\n";
    const Car car("Ford");
    const Bicycle bicycle("Trek");
    std::cout << car.description() << '\n';
    std::cout << bicycle.description() << '\n';

    std::cout << "\nTask 7: Multiple inheritance\n";
    const MultiFunctionDevice device;
#ifdef SHOW_AMBIGUITY
    std::cout << device.status() << '\n';
#endif
    std::cout << device.Scanner::status() << '\n';
    std::cout << device.Printer::status() << '\n';
    const OfficeDevice office;
    std::cout << office.status() << '\n';

    std::cout << "\nTask 8: Polymorphic calls\n";
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Car>("Toyota"));
    vehicles.push_back(std::make_unique<Bicycle>("Giant"));
    for (const auto& vehicle : vehicles) {
        std::cout << vehicle->description() << '\n';
    }
}
