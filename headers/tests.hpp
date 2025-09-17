#ifndef TESTS_H
#define TESTS_H
#include <iostream>
using namespace std;

enum TestID {
    TEST_APPLYFORCE_CIRCLE,
    TEST_ISONGROUND,
    TEST_ISONWALL,
    TEST_APPLYFRICTION,
    TEST_UPDATEPOSITION,
    TEST_DETECTBARRIERS,
    TEST_PULLOBJ,
    TEST_CIRCLE_COLLISION,
    TEST_BRUSH_CIRCLE,
    TEST_BRUSH_DRAW,
    TEST_SAND_UPDATE,
    TEST_SAND_UMAIN,
    TEST_SAND_DRAW,
    TEST_APPLYFORCE_SAND,
    TEST_DRAW_SAND,
    TEST_ADD_SAND,
    TEST_SAND_COLLISION,
    TEST_SAND_BRUSH_COLLISION,
    TEST_TIME_UPDATE,
    TEST_TIME_RECALCULATE,
    TEST_CAMERA_UPDATE,
    TEST_RESTITUTION_UPDATE,
    TEST_GRAVITY_UPDATE,
    TEST_PRINT_TEXT,
    TEST_ERASER,
    TEST_COUNT
};


struct TestFlag {
    const char* name;
    bool value;
};

static TestFlag tests[TEST_COUNT] = {
    {"CIRCLES_APPLYFORCE", false},
    {"CIRCLES_ISONGROUND", false},
    {"CIRCLES_ISONWALL", false},
    {"CIRCLES_APPLYFRICTION", false},
    {"CIRCLES_UPDATEPOSITION", false},
    {"CIRCLES_DETECTBARRIERS", false},
    {"CIRCLES_PULLOBJ", false},
    {"CIRCLE_COLLISION", false},
    {"BRUSH_CIRCLE_COLLISION", false},
    {"BRUSH_DRAW", false},
    {"SAND_UPDATE", false},
    {"SAND_UMAIN", false},
    {"SAND_DRAW", false},
    {"APPLYFORCE_SAND", false},
    {"SAND_DRAW", false},
    {"SAND_ADD", false},
    {"SAND_COLLISION", false},
    {"SAND_BRUSH", false},
    {"TIME_UPDATE", false},
    {"RESTITUTION_UPDATE", false},
    {"GRAVITY_UPDATE", false},
    {"CAMERA_UPDATE", false},
    {"TIME_RECALCULATEDELTATIME", false},
    {"PRINT_TEXT", false},
    {"ERASER", false}
};

inline void setTest(TestID id) {
    tests[id].value = true;
}

inline void TESTSRESULTS() {
    cout << "\n\n----------------------------- TESTS -----------------------------\n";
    for (auto& t : tests) {
        cout << t.name << " = " << (t.value ? "PASSED [OK]" : "NOT RUN [---------------X---------------]") << "\n";
    }
    cout << "------------------------- TESTS ENDED --------------------------\n\n";
}



#endif


