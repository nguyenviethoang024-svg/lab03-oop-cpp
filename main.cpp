/****************/
/* Ma sinh vien: 202418901
 * Ho ten      : Nguyễn Việt Hoàng
 */
/****************/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Employee.h"
#include "ProjectTeam.h"
#include "SoftwareEngineer.h"

static int passed = 0, failed = 0;

// In ket qua PASS/FAIL cho mot phep kiem tra
static void check(bool condition, const std::string& label) {
    std::cout << (condition ? "  [PASS] " : "  [FAIL] ") << label << "\n";
    (condition ? passed : failed)++;
}

static void step(int n, const std::string& title) {
    std::cout << "\n--- Buoc " << n << ": " << title << " ---\n";
}

// Chay f, mong doi nem invalid_argument
template <typename F>
static void expectThrow(const std::string& label, F f) {
    try {
        f();
        check(false, label + " (khong nem ngoai le)");
    } catch (const std::invalid_argument& ex) {
        check(true, label + " -> " + ex.what());
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // Nhan su khai bao TRUOC nhom de song lau hon nhom (lien ket khong so huu)
    std::cout << "--- Buoc 1: Tao 2 Employee bang 2 constructor ---\n";
    Employee e1("E01", "Nguyen Van An");                  // luong = 0
    Employee e2("E02", "Tran Thi Binh", 12000000.0);
    Employee defaultEmp;                                  // gia tri mac dinh
    e1.displayInfo();
    e2.displayInfo();
    defaultEmp.displayInfo();
    check(defaultEmp.getId() == "UNKNOWN" && defaultEmp.getFullName() == "Unnamed employee" &&
          defaultEmp.getBaseSalary() == 0.0, "constructor mac dinh dung gia tri quy dinh");

    step(2, "Tao 2 SoftwareEngineer bang 2 constructor");
    SoftwareEngineer s1("SE01", "Le Van Cuong", "C++");
    SoftwareEngineer s2("SE02", "Pham Thu Dung", 20000000.0, "Python", 3000000.0);
    s1.displayInfo();
    s2.displayInfo();

    step(3, "Tang luong e2 bang so tien co dinh (+1,000,000)");
    e2.increaseSalary(1000000.0);
    e2.displayInfo();
    check(e2.getBaseSalary() == 13000000.0, "e2 = 13,000,000");

    step(4, "Tang luong s2 theo phan tram (+10%)");
    s2.increaseSalary(10.0, true);
    s2.displayInfo();
    check(std::abs(s2.getBaseSalary() - 22000000.0) < 1e-6, "s2 base = 22,000,000");
    s1.increaseSalary(500000.0, false);  // phien ban 2 voi byPercentage = false
    check(s1.getBaseSalary() == 500000.0, "increaseSalary(500000, false) = so tien co dinh");

    step(5, "Tao nhom du an khong co truong nhom");
    ProjectTeam team1("PRJ01", "He thong quan ly");
    check(team1.getLeader() == nullptr, "nhom moi chua co truong nhom");
    check(team1.calculateTotalMonthlyCost() == 0.0, "nhom rong co tong chi phi = 0");

    step(6, "addMember(employee)");
    check(team1.addMember(e2), "them e2 thanh cong");

    step(7, "addMember(employee, true) - dat s2 lam truong nhom");
    check(team1.addMember(s2, true), "them s2 va dat lam truong nhom");
    check(team1.getLeader() == &s2, "truong nhom la s2");
    check(team1.contains("SE02") && team1.contains("E02"), "e2 va s2 deu la thanh vien");

    step(8, "Them lai thanh vien da ton tai");
    check(!team1.addMember(e2), "them lai e2 bi tu choi");
    check(!team1.addMember(e2, true), "them lai e2 (makeLeader) bi tu choi");
    Employee dup("E02", "Ban sao trung ma", 1.0);
    check(!team1.addMember(dup), "doi tuong khac nhung trung ma bi tu choi");
    check(team1.memberCount() == 2, "so thanh vien van la 2");

    step(9, "Hien thi danh sach bang loi goi da hinh");
    team1.displayTeam();
    Employee* poly = &s2;  // con tro co so tro toi doi tuong dan xuat
    std::cout << "Goi qua con tro Employee*: ";
    poly->displayInfo();

    step(10, "Tinh tong chi phi nhan su hang thang");
    double total = team1.calculateTotalMonthlyCost();
    std::cout << "Tong chi phi: " << total << "\n";
    check(std::abs(total - 38000000.0) < 1e-6, "13,000,000 + (22,000,000 + 3,000,000) = 38,000,000");

    step(11, "Thu xoa truong nhom hien tai");
    check(!team1.removeMember("SE02"), "xoa truong nhom bi tu choi");
    check(team1.contains("SE02"), "s2 van con trong nhom");

    step(12, "Doi truong nhom roi xoa nguoi tung la truong nhom");
    check(team1.changeLeader(e2), "doi truong nhom sang e2");
    check(team1.getLeader() == &e2, "truong nhom la e2");
    check(team1.removeMember("SE02"), "xoa s2 thanh cong");
    check(!team1.contains("SE02"), "s2 khong con trong nhom");
    check(!team1.removeMember("SE02"), "xoa lan hai (khong ton tai) tra ve false");
    team1.displayTeam();

    step(13, "Tao nhom thu hai (trong khoi lenh cuc bo) dung chung nhan su");
    {
        ProjectTeam team2("PRJ02", "Ung dung di dong", s1);  // s1 la truong nhom
        check(team2.addMember(e2), "e2 dong thoi thuoc nhom 1 va nhom 2");
        check(team1.contains("E02") && team2.contains("E02"), "e2 o ca hai nhom");
        team2.displayTeam();

        step(14, "Huy nhom thu hai khi ket thuc khoi lenh");
    }  // team2 bi huy o day

    step(15, "Nhan su cua nhom 2 van ton tai sau khi nhom bi huy");
    e2.displayInfo();
    s1.displayInfo();
    check(team1.contains("E02"), "e2 van la thanh vien nhom 1");

    std::cout << "\n=== CAC TRUONG HOP BIEN ===\n";
    expectThrow("Employee ma rong", [] { Employee x("", "A"); });
    expectThrow("Employee ma toan khoang trang", [] { Employee x("   ", "A"); });
    expectThrow("Employee ten rong", [] { Employee x("E9", ""); });
    expectThrow("Employee luong am", [] { Employee x("E9", "A", -1.0); });
    expectThrow("SoftwareEngineer ngon ngu rong",
                [] { SoftwareEngineer x("SE9", "A", ""); });
    expectThrow("SoftwareEngineer phu cap am",
                [] { SoftwareEngineer x("SE9", "A", 1.0, "Java", -5.0); });
    expectThrow("tang luong bang 0", [&] { e1.increaseSalary(0.0); });
    expectThrow("tang luong am", [&] { e1.increaseSalary(-10.0); });
    expectThrow("tang phan tram am", [&] { e1.increaseSalary(-10.0, true); });
    expectThrow("ProjectTeam ma du an rong", [] { ProjectTeam t("", "X"); });

    ProjectTeam team3("PRJ03", "Nhom co truong nhom san", e1);
    check(team3.memberCount() == 1 && team3.contains("E01"),
          "constructor 2 tu dong dua truong nhom vao danh sach");
    check(!team3.removeMember("E01"), "khong xoa duoc truong nhom duy nhat");
    check(!team3.removeMember("KHONG-TON-TAI"), "xoa ma khong ton tai tra ve false");
    check(team3.changeLeader(defaultEmp) && team3.contains("UNKNOWN"),
          "truong nhom moi tu dong duoc them vao nhom");
    check(team3.changeLeader(defaultEmp), "doi truong nhom sang chinh nguoi dang la truong nhom");
    check(team3.memberCount() == 2, "khong bi them trung khi doi truong nhom");
    check(!team1.changeLeader(dup) && team1.getLeader() == &e2,
          "changeLeader voi doi tuong trung ma bi tu choi, truong nhom giu nguyen");

    std::cout << "\nKet qua: " << passed << " PASS, " << failed << " FAIL\n";
    std::cout << "\n--- Ket thuc main: cac doi tuong con lai se bi huy ---\n";
    return failed == 0 ? 0 : 1;
}
