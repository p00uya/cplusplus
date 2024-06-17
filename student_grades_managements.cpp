#include <iostream>
#include <vector>
#include <string>
#include <numeric> // For std::accumulate

class Student {
public:
    std::string name;
    int grade;

    Student(std::string n, int g) : name(n), grade(g) {}
};

void addStudent(std::vector<Student>& students, const std::string& name, int grade) {
    students.push_back(Student(name, grade));
}

void displayStudents(const std::vector<Student>& students) {
    for (const auto& student : students) {
        std::cout << "Name: " << student.name << ", Grade: " << student.grade << std::endl;
    }
}

double calculateAverageGrade(const std::vector<Student>& students) {
    if (students.empty()) return 0.0;

    int totalGrade = std::accumulate(students.begin(), students.end(), 0, 
                                     [](int sum, const Student& student) {
                                         return sum + student.grade;
                                     });
    return static_cast<double>(totalGrade) / students.size();
}

int main() {
    std::vector<Student> students;

    // Adding students
    addStudent(students, "Alice", 85);
    addStudent(students, "Bob", 90);
    addStudent(students, "Charlie", 78);

    // Displaying students
    std::cout << "Student List:" << std::endl;
    displayStudents(students);

    // Calculating and displaying the average grade
    double averageGrade = calculateAverageGrade(students);
    std::cout << "Average Grade: " << averageGrade << std::endl;

    return 0;
}
