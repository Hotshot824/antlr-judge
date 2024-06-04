/*
* judge_basic.cpp is stored the basic unit functions for the judge class,
* Like the langeuage to string translation, ANTLR environment check, and the parser tree judge.
*/

#include "judge.h"

/*
 * Check the environment for Judge, including Java and ANTLR.
 */
void Judge::__env_check() {
    // Check Java environment
    if (std::system("java -version > /dev/null 2>&1") != 0) {
        std::cerr << "Java is not installed or not in PATH" << std::endl;
        exit(1);
    }

    // Check diff environment
    if (std::system("diff --version > /dev/null 2>&1") != 0) {
        std::cerr << "diff is not installed or not in PATH" << std::endl;
        exit(1);
    }

    // Check ANTLR environment, .jar path in /javalib/antlr-4.9.2-complete.jar
    std::string command = "java -jar " + Judge::antlr + " > /dev/null 2>&1";
    if (std::system(command.c_str()) != 0) {
        std::cerr << "ANTLR is not installed or not in PATH" << std::endl;
        exit(1);
    }
}

/*
 * Translate the ANTLR language enum to string.
 */
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

/*
 * Main function to cpp parser tree judge, Write the result to the result directory.
 * Not implemented yet.
 */
void Judge::__cpp_judge() {
    std::cout << "Cpp parser tree is not implemented yet" << std::endl;
}

/*
 * Main function to java parser tree judge, Write the result to the result directory.
 */
void Judge::__java_judge() {
    for (auto& id : Judge::students.get_ids()) {
        std::cout << "Judging parse tree for " << id << std::endl;

        // Get the path of the generated files
        std::string gen_path = Judge::antlr_generate_path + "/" + id;
        std::string result_path = Judge::students.get_result_path() + "/" + id;
        std::string result_file = result_path + "/diff.txt";
        fs::create_directories(result_path);
        Judge::__exec_command(("echo -n "" > " + result_file).c_str());

        // Compile the generated files
        Judge::__javac_compiler(gen_path);

        // Test each test case then write the output to the result directory
        for (auto& testcase : Judge::students.get_testcases()) {
            auto [stdout, stderr] = Judge::__run_antlr(gen_path, testcase);

            // Replace space with newline
            if (Judge::replace_ws) {
                stdout = StringUtils::replace(stdout, " ", "\n");
            }

            // Write the output to the result directory
            std::ofstream outputFile(result_path + "/" + testcase);
            if (outputFile.is_open()) {
                outputFile << stderr;
                outputFile << stdout;
                outputFile.close();
                Judge::__exec_command(("echo Testcase " + testcase + " start. >> " + result_file).c_str());
                Judge::__exec_command(("diff --suppress-common-lines " + Judge::students.get_correct_path() + "/result/" + testcase + " " + result_path + "/" + testcase + " >> " + result_file).c_str());
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
    std::string command = "java -jar " + Judge::antlr + " -Xexact-output-dir -Dlanguage=" + Judge::__language_to_string() + " -o " + output_path + " " + g4 + " > /dev/null 2>&1";
    return Judge::__exec_command(command.c_str());
}

/*
 * Command format:
 * javac $PATH/asterisk.java
 */
std::string Judge::__javac_compiler(std::string path) {
    std::string command = "javac " + path + "/*.java";
    return Judge::__exec_command(command.c_str());
}

/*
 * Execute the TestRig command to parse the tree, return the stdout and stderr.
 * Command format:
 * java -cp $CLASSPATH:$ANTLR_JAR org.antlr.v4.gui.TestRig $LANGUAGE $START_RULE -tree < $TESTCASE
 */
std::pair<std::string, std::string> Judge::__run_antlr(std::string path, std::string testcase) {
    std::string command = "echo -n "" > " + path + "/error.txt";
    Judge::__exec_command(command.c_str());

    if (Judge::parser_tree) {
        command = "java -cp " + path + ":" + Judge::antlr + " " + Judge::grun + " " + Judge::language + " " + Judge::start_rule + " -tree < testcases/" + testcase + " 2> " + path + "/error.txt";
    } else {
        command = "java -cp " + path + ":" + Judge::antlr + " " + Judge::grun + " " + Judge::language + " " + Judge::start_rule + " < testcases/" + testcase + " 2> " + path + "/error.txt";
    }

    std::string stdout = Judge::__exec_command(command.c_str());
    std::string stderr = Judge::__exec_command(("cat " + path + "/error.txt").c_str());

    return {stdout, stderr};
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