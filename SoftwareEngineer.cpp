/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#include "SoftwareEngineer.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

// Luong co ban mac dinh = 0, phu cap mac dinh = 0
SoftwareEngineer::SoftwareEngineer(const std::string& id, const std::string& fullName,
                                   const std::string& primaryLanguage)
    : Employee(id, fullName), primaryLanguage_(primaryLanguage), technicalAllowance_(0.0) {
    validate();
}

SoftwareEngineer::SoftwareEngineer(const std::string& id, const std::string& fullName,
                                   double baseSalary, const std::string& primaryLanguage,
                                   double technicalAllowance)
    : Employee(id, fullName, baseSalary),
      primaryLanguage_(primaryLanguage),
      technicalAllowance_(technicalAllowance) {
    validate();
}

void SoftwareEngineer::validate() const {
    requireNonBlank(primaryLanguage_, "primaryLanguage");
    if (std::isnan(technicalAllowance_) || technicalAllowance_ < 0) {
        throw std::invalid_argument("technicalAllowance must be >= 0");
    }
}

SoftwareEngineer::~SoftwareEngineer() {
    std::cout << "  [~SoftwareEngineer] destroyed: " << getId() << "\n";
}

const std::string& SoftwareEngineer::getPrimaryLanguage() const { return primaryLanguage_; }
double SoftwareEngineer::getTechnicalAllowance() const { return technicalAllowance_; }

double SoftwareEngineer::calculateMonthlyCost() const {
    return Employee::calculateMonthlyCost() + technicalAllowance_;
}

void SoftwareEngineer::displayInfo() const {
    std::cout << std::fixed << std::setprecision(2)
              << "SoftwareEngineer | ID: " << getId()
              << " | Name: " << getFullName()
              << " | Base: " << getBaseSalary()
              << " | Lang: " << primaryLanguage_
              << " | Allowance: " << technicalAllowance_
              << " | Monthly cost: " << calculateMonthlyCost() << "\n";
}
