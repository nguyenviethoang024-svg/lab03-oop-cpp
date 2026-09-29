/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#ifndef SOFTWARE_ENGINEER_H
#define SOFTWARE_ENGINEER_H

#include "Employee.h"

/**
 * @class SoftwareEngineer
 * @brief Ky su phan mem = Employee + ngon ngu lap trinh chinh + phu cap ky thuat.
 *
 * Bat bien bo sung: primaryLanguage khong rong; technicalAllowance >= 0.
 */
class SoftwareEngineer : public Employee {
private:
    std::string primaryLanguage_;
    double technicalAllowance_;

    void validate() const;

public:
    SoftwareEngineer(const std::string& id, const std::string& fullName,
                     const std::string& primaryLanguage);
    SoftwareEngineer(const std::string& id, const std::string& fullName,
                     double baseSalary, const std::string& primaryLanguage,
                     double technicalAllowance);

    ~SoftwareEngineer() override;

    const std::string& getPrimaryLanguage() const;
    double getTechnicalAllowance() const;

    /// Tong luong co ban + phu cap ky thuat
    double calculateMonthlyCost() const override;
    void displayInfo() const override;
};

#endif
