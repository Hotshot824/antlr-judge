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
    for ( auto &id : Judge::ids) {
        std::cout << "Generating ANTLR files for " << id << std::endl;

        // Create directory for generated files
        std::string gen_path = Judge::antlr_generate_path + "/" + id;
        std::string g4 = Judge::assignment_path + "/" + id + "/*.g4";
        fs::create_directories(gen_path);

        // Generate ANTLR files
        std::string output = Judge::__generate(gen_path, g4);
    }
}

/*
 * Judge the parse tree of each assignment.
 */
void Judge::antlr_parse_tree_judge() {
    switch (Judge::antlr_generate_language) {
        case Judge::AntlrLanguage::Java:
            Judge::__java_parser_tree_judge();
            break;
        case Judge::AntlrLanguage::Cpp:
            break;
        default:
            break;
    }
}

/*
 * Check the environment for Judge, including Java and ANTLR.
 */
void Judge::__env_check() {
    // Check Java environment
    if (std::system("java -version > /dev/null 2>&1") != 0) {
        std::cerr << "Java is not installed or not in PATH" << std::endl;
        exit(1);
    }

    // Check ANTLR environment, .jar path in /javalib/antlr-4.9.2-complete.jar
    std::string command = "java -jar " + Judge::antlr + " > /dev/null 2>&1";
    if (std::system(command.c_str()) != 0) {
        std::cerr << "ANTLR is not installed or not in PATH" << std::endl;
        exit(1);
    }
}

std::string Judge::__language_to_string() {
    switch (Judge::antlr_generate_language) {
        case Judge::AntlrLanguage::Java:
            return "Java";
            break;
        case Judge::AntlrLanguage::Cpp:
            return "Cpp";
            break;
        default:
            return "Java";
            break;
    }
}

void Judge::__java_parser_tree_judge() {
    for ( auto &id : Judge::ids) {
        std::cout << "Judging parse tree for " << id << std::endl;

        // Get the path of the generated files
        std::string gen_path = Judge::antlr_generate_path + "/" + id;
        std::string result_path = Judge::antlr_result_path + "/" + id;
        fs::create_directories(result_path);

        // Compile the generated files
        Judge::__compiler(gen_path);

        // Test each test case then write the output to the result directory
        for (auto& testcase : Judge::testcases) {
            std::string output = Judge::__parse_tree(gen_path, testcase);

            // Replace space with newline
            output = StringUtils::replace(output, " ", "\n");

            // Write the output to the result directory
            std::ofstream outputFile(result_path + "/" + testcase);
            if (outputFile.is_open()) {
                outputFile << output;
                outputFile.close();
            } else {
                exit(1);
            }
        }
    }
}

/*
 * Find the ANTLR .jar file in the javalib directory, return the name of the file.
 */
std::string Judge::__javalib_antlr_version() {
    std::regex antlrJarPattern("antlr-.*-complete\\.jar");
    for (const auto& entry : fs::directory_iterator("javalib")) {
        if (std::regex_match(entry.path().filename().string(), antlrJarPattern)) {
            return entry.path().string();
        }
    }
    return "";
}

/*
 * Command format:
 * java -jar $ANTLR -Dlanguage=$LANGUAGE -Xexact-output-dir -o $OUTPUT_PATH $GAMMAR_FILE
 */
std::string Judge::__generate(std::string output_path, std::string g4) {
    std::string command = "java -jar " + Judge::antlr + " -Xexact-output-dir -Dlanguage=" + Judge::__language_to_string() + " -o " + output_path + " " + g4;
    return Judge::__exec_command(command.c_str());
}

/*
 * Command format:
 * javac $PATH/asterisk.java
 */
std::string Judge::__compiler(std::string path) {
    std::string command = "javac " + path + "/*.java";
    return Judge::__exec_command(command.c_str());
}

/*
 * Command format:
 * java -cp $CLASSPATH:$ANTLR_JAR org.antlr.v4.gui.TestRig $LANGUAGE $START_RULE -tree < $TESTCASE
 */
std::string Judge::__parse_tree(std::string path, std::string testcase) {
    std::string command = "java -cp " + path + ":" + Judge::antlr + " " + Judge::grun + " " + Judge::language + " " + Judge::start_rule + " -tree < testcases/" + testcase;
    return Judge::__exec_command(command.c_str());
}

/*
 * Execute a command and return the output.
 */
std::string Judge::__exec_command(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}