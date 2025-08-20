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

void test_multiplication(void) { // <-- Add this test
    TEST_ASSERT_EQUAL(6, multiply(2, 3));
}

void test_division(void) { // <-- Add this test
    TEST_ASSERT_EQUAL(6, divide(9, 3));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication); // <-- Add this line
    return UNITY_END();
}