#ifndef LIQUID_H
#define LIQUID_H
#include "const.h"

struct liquid {
    Vector2 pos;
    float weight = GRAVITY * 1;
    Color color = BLUE;
};

#endif