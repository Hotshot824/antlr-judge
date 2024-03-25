#include "student.h"

Student::Student() {
    Student::__set_ids();
    Student::__set_testcases();
}

void Student::print_ids() {
    for (auto &id : ids) {
        std::cout << id << std::endl;
    }
}

void Student::print_testcases() {
    for (auto &id : testcases) {
        std::cout << id << std::endl;
    }
}

/*
 * Using the assignment path to set the ids.
 */
void Student::__set_ids(std::string path) {
    Student::assignment_path = path;
    ids.clear();
    for (const auto &entry : fs::directory_iterator(assignment_path)) {
        if (entry.is_directory()) {
            ids.push_back(entry.path().filename().string());
        }
    }
}

/*
 * Set the testcases path, default is "./testcases".
 */
void Student::__set_testcases(std::string path) {
    Student::testcases_path = path;
    testcases.clear();
    for (const auto &entry : fs::directory_iterator(testcases_path)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        std::string filename = entry.path().filename().string();
        if (filename.find("test") == 0) {
            testcases.push_back(filename);
        }
    }
}