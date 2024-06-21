#ifndef JUDGE_H
#define JUDGE_H

#include <cstdlib>

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <string>

#include <thread>
#include <future>


#include "string_utils.cpp"
#include "student.h"

namespace fs = std::filesystem;

class Judge {
public:
    /*
     * antlr_generate(): Generate ANTLR files for each assignment.
     * antlr_judge(): Judge the antlr assignment.
     * set_parser_language(): Set the parser language to Java or Cpp.
     * set_start_rule(): Set the start rule for the parser.
     */
    Judge();
    void antlr_generate();
    void antlr_judge();
    void set_parser_language(std::string language);
    void set_parser_tree(bool type);
    void set_replace_ws(bool type);

    // Customize parser target language
    void set_language(std::string language);
    void set_start_rule(std::string start_rule);

private:
    enum class AntlrLanguage {
        Java,
        Cpp,
    };
    Judge::AntlrLanguage antlr_generate_language = Judge::AntlrLanguage::Java;

    // Basic information
    Student students;
    std::string language = "Cactus";
    std::string start_rule = "token";
    bool parser_tree = false;
    bool replace_ws = false;

    // ANTLR executable environment
    std::string grun = "org.antlr.v4.gui.TestRig";
    std::string antlr = "./javalib/antlr-4.13.1-complete.jar";
    std::string antlr_generate_path = "./generated-files";

    // Environment check
    void __env_check();
    std::string __javalib_antlr_version();

    // Basic functions
    std::string __language_to_string();
    std::string __exec_command(const char* cmd);
    std::string __exec_command_timeout(const char* cmd, int timeout_seconds);
    std::string __generate(std::string path, std::string g4);
    std::string __javac_compiler(std::string path);

    // Judge functions
    std::pair<std::string, std::string> __run_antlr(std::string path, std::string testcase);

    void __java_judge();
    void __cpp_judge();
};

#endif  // JUDGE_H
