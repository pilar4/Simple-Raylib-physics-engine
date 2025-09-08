#ifndef TESTS_H
#define TESTS_H
#include <iostream>
using namespace std;

enum TestID {
    TEST_APPLYFORCE,
    TEST_ISONGROUND,
    TEST_APPLYFRICTION,
    TEST_UPDATEPOSITION,
    TEST_DETECTBARRIERS,
    TEST_PULLOBJ,
    TEST_CIRCLE_COLLISION,
    TEST_TIME_UPDATE,
    TEST_TIME_RECALCULATE,
    TEST_COUNT
};


struct TestFlag {
    const char* name;
    bool value;
};

static TestFlag tests[TEST_COUNT] = {
    {"CIRCLES_APPLYFORCE", false},
    {"CIRCLES_ISONGROUND", false},
    {"CIRCLES_APPLYFRICTION", false},
    {"CIRCLES_UPDATEPOSITION", false},
    {"CIRCLES_DETECTBARRIERS", false},
    {"CIRCLES_PULLOBJ", false},
    {"CIRCLE_COLLISION", false},
    {"TIME_UPDATE", false},
    {"TIME_RECALCULATEDELTATIME", false}
};

inline void setTest(TestID id) {
    tests[id].value = true;
}

inline void TESTSRESULTS() {
    cout << "\n\n----------------------------- TESTS -----------------------------\n";
    for (auto& t : tests) {
        cout << t.name << " = " << (t.value ? "PASSED [OK]" : "NOT RUN [X]") << "\n";
    }
    cout << "------------------------- TESTS ENDED --------------------------\n\n";
}



#endif