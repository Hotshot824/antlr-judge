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

    std::sort(testcases.begin(), testcases.end(), Student::__numericSort);
}

bool Student::__numericSort(std::string &a, std::string &b) {
    // Regular expression to extract the number from the filename
    std::regex re("test(\\d+)\\.txt");
    std::smatch matchA, matchB;

    // Extract number from a
    if (std::regex_search(a, matchA, re)) {
        int numA = std::stoi(matchA[1]);
        // Extract number from b
        if (std::regex_search(b, matchB, re)) {
            int numB = std::stoi(matchB[1]);
            return numA < numB;
        }
    }
    return false;
}