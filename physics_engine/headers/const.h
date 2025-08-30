//list of constants and headers

#ifndef CONST_H
#define CONST_H
#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;



constexpr float GRAVITY = 1;
constexpr Vector2 BARRIERS = {2000, 1000};
constexpr float screenWidth = BARRIERS.x;
constexpr float screenHeight = BARRIERS.y;
constexpr int bx = int(BARRIERS.x)-1;
constexpr int by = int(BARRIERS.y)-1;



#endif