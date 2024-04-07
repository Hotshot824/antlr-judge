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
void Judge::antlr_parser_tree_judge() {
    switch (Judge::antlr_generate_language) {
        case Judge::AntlrLanguage::Java:
            Judge::__java_parser_tree_judge();
            break;
        case Judge::AntlrLanguage::Cpp:
            Judge::__cpp_parser_tree_judge();
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