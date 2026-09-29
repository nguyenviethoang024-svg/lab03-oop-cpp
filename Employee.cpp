/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#include "Employee.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

bool Employee::isBlank(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") == std::string::npos;
}

void Employee::requireNonBlank(const std::string& value, const std::string& fieldName) {
    if (isBlank(value)) {
        throw std::invalid_argument(fieldName + " must not be empty");
    }
}

// Constructor mac dinh: uy quyen cho constructor day du (constructor delegation)
Employee::Employee() : Employee("UNKNOWN", "Unnamed employee", 0.0) {}

Employee::Employee(const std::string& id, const std::string& fullName)
    : Employee(id, fullName, 0.0) {}

Employee::Employee(const std::string& id, const std::string& fullName, double baseSalary)
    : id_(id), fullName_(fullName), baseSalary_(baseSalary) {
    requireNonBlank(id_, "Employee id");
    requireNonBlank(fullName_, "Employee fullName");
    if (std::isnan(baseSalary_) || baseSalary_ < 0) {
        throw std::invalid_argument("baseSalary must be >= 0");
    }
}

Employee::~Employee() {
    std::cout << "  [~Employee] destroyed: " << id_ << " - " << fullName_ << "\n";
}

const std::string& Employee::getId() const { return id_; }
const std::string& Employee::getFullName() const { return fullName_; }
double Employee::getBaseSalary() const { return baseSalary_; }

// Phien ban 1: tang so tien co dinh -> tai su dung phien ban 2
void Employee::increaseSalary(double amount) {
    increaseSalary(amount, false);
}

// Phien ban 2: tang theo % hoac so tien co dinh
void Employee::increaseSalary(double value, bool byPercentage) {
    if (std::isnan(value) || value <= 0) {
        throw std::invalid_argument("increase value must be positive");
    }
    if (byPercentage) {
        baseSalary_ += baseSalary_ * value / 100.0;
    } else {
        baseSalary_ += value;
    }
}

double Employee::calculateMonthlyCost() const {
    return baseSalary_;
}

void Employee::displayInfo() const {
    std::cout << std::fixed << std::setprecision(2)
              << "Employee | ID: " << id_
              << " | Name: " << fullName_
              << " | Base: " << baseSalary_
              << " | Monthly cost: " << calculateMonthlyCost() << "\n";
}
