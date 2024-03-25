### ANTLR-JUDEG

This is an simple tool to judge the correctness of the ANTLR grammar file. In order to assist teacher assistants in the CCU compiler design course.

---

### Usage

File Structure:
```bash
.
├── assignments ── ${student_id} ── ${grammar_files}
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