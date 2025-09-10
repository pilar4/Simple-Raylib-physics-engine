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


constexpr Vector2 BARRIERS = {2500, 2500};
constexpr float screenWidth = 1800;
constexpr float screenHeight = 1000;
constexpr float airDragValue = 1.0 - 1/10;
Vector2 AIRDRAGVECTOR = {airDragValue, airDragValue};
constexpr int bGirth = 15;



gravityController g;
timeController t;
restitutionController r;


float frictionCoefficient = 200.f;    



#endif