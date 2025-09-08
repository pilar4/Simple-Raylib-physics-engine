#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H
#include "const.hpp"
#include "tests.hpp"


// Z: tiome slow down, X: time speed up, C: reset
// V: gravity slow down, B: gravity speed up, M: gravity left, N: gravity right
// D: balls, RMB: rigid, Q: balls clear


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

        RecalculateDeltaTime();
    }

    void RecalculateDeltaTime() {
        deltaTime = timeStopped ? 0.0f : float(numerator) / float(denominator);
        //if true use 0.0f if false use the rest after :
    }
};
 

class gravityController { 
  public:
    Vector2 GRAVITY = {0.f, 980.f};
    
    void UPDATE() {
        
        // manipulate GRAVITY left / right included
        if (IsKeyDown(KEY_V)) GRAVITY.y += 10.f;
        if (IsKeyDown(KEY_B)) GRAVITY.y -= 10.f;
        if (IsKeyDown(KEY_N)) GRAVITY.x -= 10.f;
        if (IsKeyDown(KEY_M)) GRAVITY.x += 10.f;

        
        if (IsKeyDown(KEY_C)){
            GRAVITY = {0.f, 980.f};
        }
    }   
};


timeController t;
gravityController g;


#endif
