#include "student.hpp"
#include "examples.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <type_traits>

void expect(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

template <typename Exception, typename Action>
void expectThrows(Action action, const char* message) {
    bool caught = false;
    try {
        action();
    } catch (const Exception&) {
        caught = true;
    }
    expect(caught, message);
}

std::string describe(const Student& student) {
    std::ostringstream output;
    student.output(output);
    return output.str();
}

void testStudent() {
    const Student empty;
    expect(describe(empty) == "Name: Unknown\nGroup: Not assigned\nCourse: 1\n", "Student default constructor");
    Student student("Roman Seletskyi", "KN-11", 1);
    expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-11\nCourse: 1\n", "Student parameterized constructor");
    student.setGroup("KN-21");
    student.setCourse(2);
    expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-21\nCourse: 2\n", "Student update");
    for (int course : {0, -1}) {
        expectThrows<std::invalid_argument>([&] { student.setCourse(course); }, "Student invalid course");
        expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-21\nCourse: 2\n", "Student unchanged after rejection");
        expectThrows<std::invalid_argument>([&] { Student invalid("Anna", "KN-11", course); }, "Student invalid construction");
    }
}

void testTovar() {
    Tovar item("Book", 125.50, 3);
    expect(item.getName() == "Book" && item.getQuantity() == 3, "Tovar initial state");
    expect(std::abs(item.totalValue() - 376.50) < 1e-9, "Tovar total value");
    item.sell(2);
    expect(item.getQuantity() == 1, "Tovar sale reduces quantity");
    expectThrows<std::invalid_argument>([&] { item.sell(2); }, "Tovar overselling rejected");
    expectThrows<std::invalid_argument>([&] { item.sell(0); }, "Tovar zero sale rejected");
    expectThrows<std::invalid_argument>([&] { item.sell(-1); }, "Tovar negative sale rejected");
    expect(item.getQuantity() == 1, "Tovar unchanged after rejected sale");
    expectThrows<std::invalid_argument>([&] { item.setPrice(-1); }, "Tovar negative price rejected");
    expectThrows<std::invalid_argument>([&] { item.setPrice(std::numeric_limits<double>::quiet_NaN()); }, "Tovar NaN price rejected");
    expect(std::abs(item.getPrice() - 125.50) < 1e-9, "Tovar price unchanged after rejection");
    item.sell(1);
    expect(item.getQuantity() == 0, "Tovar last unit sold");
    expectThrows<std::invalid_argument>([] { Tovar invalid("Book", 10, -1); }, "Tovar negative stock rejected");
}

void testPrylad() {
    const Prylad lamp("Lamp", 60);
    expect(std::abs(lamp.energyKwh(5) - 0.3) < 1e-9, "Prylad watts converted to kWh");
    expect(lamp.energyKwh(0) == 0, "Prylad zero duration");
    expectThrows<std::invalid_argument>([&] { lamp.energyKwh(-1); }, "Prylad negative duration rejected");
    expectThrows<std::invalid_argument>([&] { lamp.energyKwh(std::numeric_limits<double>::infinity()); }, "Prylad infinite duration rejected");
    expectThrows<std::invalid_argument>([] { Prylad invalid("Lamp", -1); }, "Prylad negative power rejected");
}

void testPayment() {
    const Payment empty;
    expect(empty.getAmountKopiyky() == 0 && empty.getCurrency() == "UAH", "Payment default state");
    const Payment paid(15499, "UAH");
    expect(paid.getAmountKopiyky() == 15499 && paid.getCurrency() == "UAH", "Payment preserves smallest units");
    expectThrows<std::invalid_argument>([] { Payment invalid(-1, "UAH"); }, "Payment negative amount rejected");
    expectThrows<std::invalid_argument>([] { Payment invalid(100, ""); }, "Payment empty currency rejected");
}

void testInheritance() {
    static_assert(std::has_virtual_destructor_v<Vehicle>);
    const std::unique_ptr<Vehicle> car = std::make_unique<Car>("Ford");
    const std::unique_ptr<Vehicle> bicycle = std::make_unique<Bicycle>("Trek");
    expect(car->description() == "Car: Ford", "Virtual dispatch selects Car");
    expect(bicycle->description() == "Bicycle: Trek", "Virtual dispatch selects Bicycle");
    const MultiFunctionDevice device;
    expect(device.Scanner::status() == "Scanner ready", "Qualified scanner method");
    expect(device.Printer::status() == "Printer ready", "Qualified printer method");
    const OfficeDevice office;
    expect(office.status() == "Scanner ready; Printer ready", "Derived method resolves ambiguity");
}

int main() {
    try {
        testStudent();
        testTovar();
        testPrylad();
        testPayment();
        testInheritance();
        std::cout << "All tests passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
