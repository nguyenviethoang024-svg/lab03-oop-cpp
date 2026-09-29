/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#include "ProjectTeam.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

// Tim vi tri thanh vien theo ma; -1 neu khong co
int ProjectTeam::indexOf(const std::string& employeeId) const {
    for (std::size_t i = 0; i < members_.size(); ++i) {
        if (members_[i]->getId() == employeeId) return static_cast<int>(i);
    }
    return -1;
}

ProjectTeam::ProjectTeam(const std::string& projectCode, const std::string& projectName)
    : projectCode_(projectCode), projectName_(projectName), leader_(nullptr) {
    if (projectCode_.find_first_not_of(" \t\r\n") == std::string::npos ||
        projectName_.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("projectCode/projectName must not be empty");
    }
}

// Dat truong nhom va tu dong dua truong nhom vao danh sach thanh vien
ProjectTeam::ProjectTeam(const std::string& projectCode, const std::string& projectName,
                         Employee& leader)
    : ProjectTeam(projectCode, projectName) {
    members_.push_back(&leader);
    leader_ = &leader;
}

ProjectTeam::~ProjectTeam() {
    std::cout << "  [~ProjectTeam] destroyed team " << projectCode_
              << " (" << members_.size() << " links released, employees untouched)\n";
    members_.clear();  // chi xoa con tro, khong delete Employee
    leader_ = nullptr;
}

const std::string& ProjectTeam::getProjectCode() const { return projectCode_; }
const std::string& ProjectTeam::getProjectName() const { return projectName_; }
const Employee* ProjectTeam::getLeader() const { return leader_; }
std::size_t ProjectTeam::memberCount() const { return members_.size(); }

// Them thanh vien; tu choi neu ma da ton tai (ke ca doi tuong khac cung ma)
bool ProjectTeam::addMember(Employee& employee) {
    if (indexOf(employee.getId()) != -1) return false;
    members_.push_back(&employee);
    return true;
}

// Them va (neu makeLeader) dat lam truong nhom; truong nhom cu van la thanh vien
bool ProjectTeam::addMember(Employee& employee, bool makeLeader) {
    if (!addMember(employee)) return false;
    if (makeLeader) leader_ = &employee;
    return true;
}

// Khong cho xoa truong nhom hien tai
bool ProjectTeam::removeMember(const std::string& employeeId) {
    int idx = indexOf(employeeId);
    if (idx == -1) return false;
    if (members_[idx] == leader_) return false;
    members_.erase(members_.begin() + idx);
    return true;
}

// Truong nhom moi duoc them vao nhom neu chua la thanh vien
bool ProjectTeam::changeLeader(Employee& employee) {
    int idx = indexOf(employee.getId());
    if (idx != -1 && members_[idx] != &employee) return false;  // trung ma, khac doi tuong
    if (idx == -1) members_.push_back(&employee);
    leader_ = &employee;
    return true;
}

bool ProjectTeam::contains(const std::string& employeeId) const {
    return indexOf(employeeId) != -1;
}

// Truong nhom nam trong members_ nen khong bi tinh hai lan
double ProjectTeam::calculateTotalMonthlyCost() const {
    double total = 0.0;
    for (const Employee* e : members_) total += e->calculateMonthlyCost();
    return total;
}

void ProjectTeam::displayTeam() const {
    std::cout << "=== Team " << projectCode_ << " - " << projectName_ << " ===\n";
    std::cout << "Leader: " << (leader_ ? leader_->getFullName() : std::string("(none)")) << "\n";
    if (members_.empty()) std::cout << "(no members)\n";
    for (const Employee* e : members_) {
        std::cout << (e == leader_ ? "  * " : "    ");
        e->displayInfo();  // goi da hinh
    }
    std::cout << std::fixed << std::setprecision(2)
              << "Total monthly cost: " << calculateTotalMonthlyCost() << "\n";
}
