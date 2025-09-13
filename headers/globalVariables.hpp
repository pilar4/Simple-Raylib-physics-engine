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


constexpr Vector2 BARRIERS = {1920, 1080};
constexpr float screenWidth = 1920;
constexpr float screenHeight = 1080;
constexpr float airDragValue = 1.0 - 1/10;
Vector2 AIRDRAGVECTOR = {airDragValue, airDragValue};
constexpr int bGirth = 15;



gravityController g;
timeController t;
restitutionController r;
float frictionCoefficient = 200.f;    



#endif