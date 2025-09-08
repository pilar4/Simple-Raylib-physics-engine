//list of constants and libraries
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include "raylib.h"
#include "raymath.h"
#include "simulationSettings.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


constexpr Vector2 GRAVITY = {0.f, -980.f};
//constexpr Vector2 GRAVITY = {0.f, 0.f};
constexpr Vector2 BARRIERS = {1900, 1000};
constexpr float screenWidth = BARRIERS.x;
constexpr float screenHeight = BARRIERS.y;
//constexpr float RESTITUTION = 0.75f;
constexpr float RESTITUTION = 0.70f;
constexpr float airDragValue = 1.0 - 1/10;
Vector2 AIRDRAGVECTOR = {airDragValue, airDragValue};

timeController t;
float frictionCoefficient = 200.f;    



#endif