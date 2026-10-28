#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Student {
private:
    std::string name = "Unknown";
    std::string group = "Not assigned";
    int course = 1;

public:
    Student() = default;

    Student(std::string name, std::string group, int course)
        : name(std::move(name)), group(std::move(group)) {
        setCourse(course);
    }

    void setGroup(std::string group) {
        this->group = std::move(group);
    }

    void setCourse(int course) {
        if (course < 1) throw std::invalid_argument("Course must be positive");
        this->course = course;
    }

    void output(std::ostream& output = std::cout) const {
        output << "Name: " << name << '\n'
               << "Group: " << group << '\n'
               << "Course: " << course << '\n';
    }
};
