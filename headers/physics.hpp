#ifndef PHYSICS_H
#define PHYSICS_H
#include "const.hpp"
//using Verlet integration


struct object{
    Vector2 currentPosition;
    Vector2 oldPosition;
    Vector2 acceleration; 
    
    void NEWPOSITION(float dTime){
        Vector2 displacement = Vector2Subtract(currentPosition, oldPosition);
        oldPosition = currentPosition;
        currentPosition = Vector2Add(Vector2Add(currentPosition, displacement), Vector2Scale(acceleration, dTime*dTime));
        
        //Xn+1 = 2Xn - Xn-1 + a * Δt^2
        
        acceleration = (Vector2){0.f, 0.f};
}


    void applyForce(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
    }
};







#endif