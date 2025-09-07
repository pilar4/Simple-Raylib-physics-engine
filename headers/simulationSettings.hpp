#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H
#include "const.hpp"


// Z: slow down, X: speed up


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
        if (denominator < 1) denominator = 1; // safety so there is no x/0 

        // stop time
        if (IsKeyPressed(KEY_SPACE)) {
            timeStopped = !timeStopped; // toggle
        }

        RecalculateDeltaTime();
    }

    void RecalculateDeltaTime() {
        deltaTime = timeStopped ? 0.0f : float(numerator) / float(denominator);
        //if true use 0.0f if false use the rest after :
    }
};


timeController t;



#endif