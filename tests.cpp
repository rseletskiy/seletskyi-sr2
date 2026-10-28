#include "student.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

void expect(bool condition) {
    if (!condition) throw std::runtime_error("Test failed");
}

std::string describe(const Student& student) {
    std::ostringstream output;
    student.output(output);
    return output.str();
}

int main() {
    try {
        const Student empty;
        expect(describe(empty) == "Name: Unknown\nGroup: Not assigned\nCourse: 1\n");
        Student student("Roman Seletskyi", "KN-11", 1);
        expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-11\nCourse: 1\n");
        student.setGroup("KN-21");
        student.setCourse(2);
        expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-21\nCourse: 2\n");
        for (int course : {0, -1}) {
            bool caught = false;
            try { student.setCourse(course); }
            catch (const std::invalid_argument&) { caught = true; }
            expect(caught);
            expect(describe(student) == "Name: Roman Seletskyi\nGroup: KN-21\nCourse: 2\n");
            caught = false;
            try { Student invalid("Anna", "KN-11", course); }
            catch (const std::invalid_argument&) { caught = true; }
            expect(caught);
        }
        std::cout << "All tests passed\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
