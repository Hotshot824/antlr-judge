### ANTLR-JUDEG

This is an simple tool to judge the correctness of the ANTLR grammar file. In order to assist teacher assistants in the CCU compiler design course.

-   [x] ANTLR to generate the parser and lexer.
-   [x] ANTLR TestRig to print the parse tree.
-   [ ] Using the Java code to generate the parse tree.
-   [ ] Using the C++ code to generate the parse tree.
-   [ ] Travesal the parse tree using the visitor pattern Java/C++ code.

Currently, the tool using `diff` to compare the parse tree string, spilit the string by the newline character, and compare the string line by line.

#### Requirements

-   Linux
-   ANTLR jar file > 4.9.2
-   Java JDK > 17
-   clang++ > 12.0.0
-   make > 4.3

---

### Usage

Create the missing directories and put in required files.

File Structure:
```bash
.
├── assignments ── ${student_id} ── ${grammar_files}
├── correct ── result ── ${testcase_expected_result}
├── generated-files (ANTLR generated files)
├── javalib (Java library)
├── makefile
├── results ── ${student_id} ── ${result_files}
├── lib (Cpp library)
├── main.cpp (Cpp main)
└── testcases ── ${testcase}
```

1.  Put the student's grammar file in the `assignments/${student_id}` directory.
2.  Put the test case in the `testcases` directory.
3.  Run the `make run` command.
4.  Results will be generated in the `results/${student_id}` directory.