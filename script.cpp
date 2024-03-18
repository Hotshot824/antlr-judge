#include<iostream>
#include<filesystem>
#include<vector>
#include<string>

namespace fs = std::filesystem;

class Student
{
    std::string assignment_path = "./target";
    std::vector<std::string> assignments;
    std::string testcases_path = "./testcases";
    std::vector<std::string> testcases;

    public:
    Student() {
        __set_assignments();
    }

    void print_assignments() {
        for (auto& id : assignments) {
            std::cout << id << std::endl;
        }
    }

    private:

    void __set_assignments() {
        for (const auto& entry : fs::directory_iterator(assignment_path))
        {
            if (entry.is_directory())
            {
                assignments.push_back(entry.path().filename().string());
            }
        }
    }

    void __set_testcases() {
        for (const auto& entry : fs::directory_iterator(testcases_path))
        {
            if (entry.is_directory())
            {
                testcases.push_back(entry.path().filename().string());
            }
        }
    }
};

int main()
{
    Student s;
    s.PrintStudents();
    return 0;
}