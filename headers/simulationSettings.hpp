#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H
#include "headers.h"
#include "tests.hpp"


// Z: slow down, X: speed up, C: reset

// MOZNA BY ZMIENIC TE WSZYSTKIE VECTOR2ADD ITD NA WLASNA MATEMATYKE I ZROBIC Z TEGO NOWY HEADER
// NAPRAWIC TIME STOP I OBJ DRAG, DODAC SUWAKI DLA GRAWITACJI I RESTITUTION ZROBIC OPORY TRAKCJI




class timeController {
public:
    int numerator = 1;
    int denominator = 60;
    float deltaTime = float(numerator) / float(denominator);
    bool timeStopped = false;

    void UPDATE() {
        // manipulate time
        if (IsKeyDown(KEY_Z)) denominator += 1;
        if (IsKeyDown(KEY_X)) denominator -= 1;
        if (IsKeyDown(KEY_C)) denominator = 60;
        if (denominator < 1) denominator = 1; // safety so there is no x/0 

        // stop time
        if (IsKeyPressed(KEY_SPACE)) {
            timeStopped = !timeStopped; // toggle
        }

        RECALCULATEDELTATIME();
        setTest(TEST_TIME_UPDATE);
    }

    void RECALCULATEDELTATIME() {
        deltaTime = timeStopped ? 0.0f : float(numerator) / float(denominator);
        //if true use 0.0f if false use the rest after :
        setTest(TEST_TIME_RECALCULATE);
    }
};






#endif