/*
 * Class Student is managed all the student information:
 * 1. Student IDs.
 * 2. Assignment, Result, and Testcases, Correct answer path.
 */
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
    std::string get_assignment_path() { return assignment_path; }
    std::string get_testcases_path() { return testcases_path; }
    std::string get_result_path() { return result_path; }
    std::string get_correct_path() { return correct_path; }

protected:
    std::vector<std::string> ids;
    std::vector<std::string> testcases;
    std::string assignment_path = "./assignments";
    std::string testcases_path = "./testcases";
    std::string result_path = "./results";
    std::string correct_path = "./correct";
    
    void __set_ids(std::string path = "./assignments");
    void __set_testcases(std::string path = "./testcases");
};

#endif  // STUDENT_H
