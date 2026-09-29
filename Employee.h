/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

/**
 * @class Employee
 * @brief Nhan su thong thuong: ma, ho ten, luong co ban.
 *
 * Bat bien: id va fullName khong rong; baseSalary >= 0.
 */
class Employee {
private:
    std::string id_;       ///< Ma nhan su
    std::string fullName_; ///< Ho ten
    double baseSalary_;    ///< Luong co ban (>= 0)

protected:
    /// Kiem tra chuoi rong hoac chi gom khoang trang
    static bool isBlank(const std::string& s);
    /// Nem std::invalid_argument neu chuoi rong
    static void requireNonBlank(const std::string& value, const std::string& fieldName);

public:
    // ---- Constructor (nap chong) ----
    Employee();
    Employee(const std::string& id, const std::string& fullName);
    Employee(const std::string& id, const std::string& fullName, double baseSalary);

    /// Destructor ao, in thong bao de quan sat vong doi
    virtual ~Employee();

    // ---- Getter ----
    const std::string& getId() const;
    const std::string& getFullName() const;
    double getBaseSalary() const;

    // ---- Nap chong phuong thuc ----
    /// Tang luong theo so tien co dinh (amount > 0)
    void increaseSalary(double amount);
    /// Tang theo % neu byPercentage == true, nguoc lai tang so tien co dinh (value > 0)
    void increaseSalary(double value, bool byPercentage);

    // ---- Da hinh ----
    /// Chi phi hang thang; mac dinh = luong co ban
    virtual double calculateMonthlyCost() const;
    /// In thong tin nhan su
    virtual void displayInfo() const;
};

#endif
