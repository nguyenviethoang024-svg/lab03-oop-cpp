/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#ifndef PROJECT_TEAM_H
#define PROJECT_TEAM_H

#include <string>
#include <vector>

#include "Employee.h"

/**
 * @class ProjectTeam
 * @brief Nhom du an. Lien ket KHONG so huu (aggregation) toi Employee.
 *
 * Bat bien:
 *  - Khong co hai thanh vien cung ma trong mot nhom.
 *  - Neu co truong nhom thi truong nhom nam trong danh sach thanh vien.
 * Nguoi goi phai dam bao Employee song lau hon ProjectTeam.
 */
class ProjectTeam {
private:
    std::string projectCode_;
    std::string projectName_;
    Employee* leader_;                ///< khong so huu, co the nullptr
    std::vector<Employee*> members_;  ///< khong so huu

    int indexOf(const std::string& employeeId) const;

public:
    ProjectTeam(const std::string& projectCode, const std::string& projectName);
    ProjectTeam(const std::string& projectCode, const std::string& projectName,
                Employee& leader);

    /// Chi huy cau truc danh sach noi bo, KHONG huy cac Employee
    ~ProjectTeam();

    const std::string& getProjectCode() const;
    const std::string& getProjectName() const;
    const Employee* getLeader() const;
    std::size_t memberCount() const;

    bool addMember(Employee& employee);
    bool addMember(Employee& employee, bool makeLeader);
    bool removeMember(const std::string& employeeId);
    bool changeLeader(Employee& employee);
    bool contains(const std::string& employeeId) const;

    double calculateTotalMonthlyCost() const;
    void displayTeam() const;
};

#endif
