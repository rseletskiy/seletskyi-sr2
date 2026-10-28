#include "student.hpp"

int main() {
    Student first;
    Student second("Roman Seletskyi", "KN-11", 1);

    std::cout << "Default constructor:\n";
    first.output();

    std::cout << "\nParameterized constructor:\n";
    second.output();

    second.setGroup("KN-21");
    second.setCourse(2);
    std::cout << "\nAfter update:\n";
    second.output();
}
