#ifndef JUDGE_H
#define JUDGE_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "student.h"
#include "string_utils.cpp"

namespace fs = std::filesystem;

class Judge : public Student {
public:
    Judge();
    void antlr_generate();
    void antlr_parse_tree_judge();

private:
    void __env_check();

private:
    enum class AntlrLanguage {
        Java,
        Cpp,
    };

    // Basic information
    std::string language = "Cactus";
    std::string start_rule = "token";

    // ANTLR executable environment
    std::string grun = "org.antlr.v4.gui.TestRig";
    std::string antlr = "./javalib/antlr-4.13.1-complete.jar";
    Judge::AntlrLanguage antlr_generate_language = Judge::AntlrLanguage::Java;
    std::string antlr_generate_path = "./generated-files";
    std::string antlr_result_path = "./results";

    // Environment check
    std::string __javalib_antlr_version();

    // Basic functions
    std::string __language_to_string();
    std::string __exec_command(const char* cmd);
    std::string __generate(std::string path, std::string g4);
    std::string __compiler(std::string path);
    std::string __parse_tree(std::string path, std::string testcase);

    void __java_parser_tree_judge();
};

#endif  // JUDGE_H
