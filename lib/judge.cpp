/*
* judge.cpp storage the top level function for the judge class, 
* all public calls to the judge class are made through this file.
*/

#include "judge.h"

Judge::Judge() {
    Judge::antlr = Judge::__javalib_antlr_version();
    Judge::__env_check();
}

/*
 * Generate ANTLR files for each assignment.
 */
void Judge::antlr_generate() {
    // Generate ANTLR files for each assignment
    for (auto& id : Judge::students.get_ids()) {
        std::cout << "Generating ANTLR files for " << id << std::endl;

        // Create directory for generated files
        std::string gen_path = Judge::antlr_generate_path + "/" + id;
        std::string g4 = Judge::students.get_assignment_path() + "/" + id + "/*.g4";
        fs::create_directories(gen_path);

        // Generate ANTLR files
        std::string output = Judge::__generate(gen_path, g4);
    }
}

/*
 * Judge the parse tree of each assignment.
 */
void Judge::antlr_judge() {
    switch (Judge::antlr_generate_language) {
        case Judge::AntlrLanguage::Java:
            Judge::__java_judge();
            break;
        case Judge::AntlrLanguage::Cpp:
            Judge::__cpp_judge();
            break;
        default:
            break;
    }
}

void Judge::set_parser_language(std::string language) {
    if (language == "Cpp") {
        Judge::antlr_generate_language = Judge::AntlrLanguage::Cpp;
    } else {
        Judge::antlr_generate_language = Judge::AntlrLanguage::Java;
    }
}

void Judge::set_parser_tree(bool type) {
    Judge::parser_tree = type;
}

void Judge::set_language(std::string language) {
    Judge::language = language;
}

void Judge::set_start_rule(std::string start_rule) {
    Judge::start_rule = start_rule;
}