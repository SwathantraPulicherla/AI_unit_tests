#include "unity.h"

static int tests_run = 0;
static int tests_failed = 0;

void UNITY_BEGIN(void) {
    tests_run = 0;
    tests_failed = 0;
    printf("Unity test runner\n");
}

int UNITY_END(void) {
    printf("-----------------------\n");
    printf("%d Tests %d Failures 0 Ignored\n", tests_run, tests_failed);
    if (tests_failed == 0) {
        printf("OK\n");
        return 0;
    } else {
        printf("FAIL\n");
        return 1;
    }
}

void RUN_TEST(void (*TestFunc)(void)) {
    tests_run++;
    TestFunc();
}

void TEST_ASSERT_EQUAL(int expected, int actual) {
    if (expected != actual) {
        printf("Test failed: expected %d but got %d\n", expected, actual);
        tests_failed++;
    }
}