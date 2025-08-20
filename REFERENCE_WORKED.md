# Reference: Steps That Worked for Unit Testing and Coverage in C (GitHub Codespace, Ubuntu 24.04.2 LTS)

This file documents the **exact steps that worked** for setting up unit testing with Unity and generating code coverage for only the source file (`calculator.c`) in this Codespace.

---

## 1. Project Structure

```
/workspaces/AI_unit_tests/
├── calculator.c
├── calculator.h
├── tests/
│   ├── test_calculator.c
│   └── unity/
│       ├── unity.c
│       └── unity.h
```

---

## 2. Source and Header Files

**calculator.c**
```c
#include "calculator.h"
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
```

**calculator.h**
```c
#ifndef CALCULATOR_H
#define CALCULATOR_H

int add(int a, int b);
int subtract(int a, int b);

#endif
```

---

## 3. Unit Test File

**tests/test_calculator.c**
```c
#include "unity.h"
#include "calculator.h"

void setUp(void) {}
void tearDown(void) {}

void test_addition(void) {
    TEST_ASSERT_EQUAL(5, add(2, 3));
}

void test_subtraction(void) {
    TEST_ASSERT_EQUAL(1, subtract(3, 2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    return UNITY_END();
}
```

---

## 4. Minimal Unity Test Framework

**tests/unity/unity.h** and **tests/unity/unity.c**  
(Use the minimal versions or download from [Unity GitHub](https://github.com/ThrowTheSwitch/Unity))

---

## 5. Compile and Run Tests

```sh
gcc -Itests/unity -I. tests/test_calculator.c calculator.c tests/unity/unity.c -o test_calculator
./test_calculator
```

---

## 6. Compile with Coverage Flags

```sh
gcc -Itests/unity -I. -fprofile-arcs -ftest-coverage tests/test_calculator.c calculator.c tests/unity/unity.c -o test_calculator
```

---

## 7. Run Tests to Generate Coverage Data

```sh
./test_calculator
```

---

## 8. Generate Coverage Report (Text)

```sh
gcov -b -o . calculator.c
```
- This creates `calculator.c.gcov` with line-by-line coverage.

---

## 9. Generate HTML Coverage Report for Only Source File

```sh
# Clean up previous coverage data
rm -f *.gcda *.gcno *.info

# Compile with coverage flags
gcc -Itests/unity -I. -fprofile-arcs -ftest-coverage tests/test_calculator.c calculator.c tests/unity/unity.c -o test_calculator

# Run tests
./test_calculator

# Capture all coverage data
lcov --capture --directory . --output-file coverage.info

# List coverage info to verify calculator.c is included
lcov --list coverage.info

# Remove test and Unity files from coverage
lcov --remove coverage.info 'tests/*' '*/unity/*' '/usr/*' --output-file coverage_filtered.info

# Extract only calculator.c coverage
lcov --extract coverage_filtered.info '*/calculator.c' --output-file coverage_calculator.info

# Generate HTML report
genhtml coverage_calculator.info --output-directory coverage_html
```

---

## 10. View HTML Coverage Report

```sh
"$BROWSER" coverage_html/index.html
```
- If this doesn't open in your browser, you can serve the folder:
    ```sh
    cd coverage_html
    python3 -m http.server 8080
    ```
  Then forward port 8080 in VS Code and open the provided URL.

---

## Notes

- **Always run build and coverage commands from the project root** (`/workspaces/AI_unit_tests`).
- Adjust file paths if your structure differs.
- For more advanced Unity usage, see [Unity documentation](https://github.com/ThrowTheSwitch/Unity).
- If you get "no valid records found", check `lcov --list