#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
using std::getline;

class Student {
private:
    int id;
    string name;
    float grade;

public:
    void getInput() {
        cout << "Please input the student ID: ";
        cin >> id;
        cin.ignore(); // Clear the newline character from the buffer
        cout << "Please input the student name: ";
        getline(cin, name);
        cout << "Please input the student grade: ";
        cin >> grade;
    }

    void showDetails() const {
        cout << "\n--- Student Information ---\n";
        cout << "Student ID: " << id << "\n";
        cout << "Student Name: " << name << "\n";
        cout << "Student Grade: " << grade << "\n";
    }
};

int main() {
    Student stud;
    stud.getInput();
    stud.showDetails();

    return 0;
}
