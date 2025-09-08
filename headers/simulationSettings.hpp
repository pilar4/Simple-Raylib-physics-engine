#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H
#include "headers.h"
#include "tests.hpp"



// Z: tiome slow down, X: time speed up, C: reset
// I J K L gravity change
// D: balls, RMB: rigid, Q: balls clear


class timeController {
public:
    int numerator = 1;
    int denominator = 60;
    float deltaTime = float(numerator) / float(denominator);
    bool timeStopped = false;
    int multiplier = 1;

    void UPDATE() {
        // manipulate time
        if (IsKeyDown(KEY_Z)) denominator += multiplier;
        if (IsKeyDown(KEY_X)) denominator -= multiplier;
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

class gravityController { 
  public:
    Vector2 GRAVITY = {0.f, 980.f};
    float multiplier = 20.f;
    void UPDATE() {

        // manipulate GRAVITY left / right included
        if (IsKeyDown(KEY_I)) GRAVITY.y += multiplier;
        if (IsKeyDown(KEY_K)) GRAVITY.y -= multiplier;
        if (IsKeyDown(KEY_J)) GRAVITY.x -= multiplier;
        if (IsKeyDown(KEY_L)) GRAVITY.x += multiplier;


        if (IsKeyDown(KEY_C)){
            GRAVITY = {0.f, 980.f};
        }
        setTest(TEST_GRAVITY_UPDATE);
    }   
};

class restitutionController { 
  public:
    float RESTITUTION = 0.7;
    float multiplier = 0.001f;
    void UPDATE() {

        // manipulate GRAVITY left / right included
        if (IsKeyDown(KEY_T)) RESTITUTION += multiplier;
        if (IsKeyDown(KEY_G)) RESTITUTION -= multiplier;



        if (IsKeyDown(KEY_C)){
            RESTITUTION = 0.7;
        }
        setTest(TEST_RESTITUTION_UPDATE);
    }   
};





#endif