//list of constants and libraries
#ifndef CONST_H
#define CONST_H
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
using namespace std;


constexpr Vector2 GRAVITY = {0.f, 300.f};
constexpr Vector2 BARRIERS = {1900, 1000};
constexpr float screenWidth = BARRIERS.x;
constexpr float screenHeight = BARRIERS.y;
constexpr int bx = BARRIERS.x-1;
constexpr int by = BARRIERS.y-1;
constexpr float dt = 1.0/60.0;


#endif