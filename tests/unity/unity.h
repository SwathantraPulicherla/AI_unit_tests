#ifndef UNITY_H
#define UNITY_H

#include <setjmp.h>
#include <stdio.h>

void UNITY_BEGIN(void);
int UNITY_END(void);
void RUN_TEST(void (*TestFunc)(void));
void TEST_ASSERT_EQUAL(int expected, int actual);

#endif //