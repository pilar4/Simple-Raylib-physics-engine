//list of constants and libraries
#ifndef CONST_H
#define CONST_H
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


constexpr Vector2 GRAVITY = {0.f, 980.f};
constexpr Vector2 BARRIERS = {1900, 1000};
constexpr float screenWidth = BARRIERS.x;
constexpr float screenHeight = BARRIERS.y;
//constexpr float DELTATIME = 1.0/60.0;
constexpr float RESTITUTION = 0.75f;



#endif