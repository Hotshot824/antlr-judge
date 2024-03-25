#ifndef STUDENT_H
#define STUDENT_H

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Student {
public:
    Student();
    void print_ids();
    void print_testcases();
    std::vector<std::string> get_ids() { return ids; }
    std::vector<std::string> get_testcases() { return testcases; }

protected:
    std::string assignment_path = "./assignments";
    std::vector<std::string> ids;
    std::string testcases_path = "./testcases";
    std::vector<std::string> testcases;
    void __set_ids(std::string path = "./assignments");
    void __set_testcases(std::string path = "./testcases");
};

#endif  // STUDENT_H
