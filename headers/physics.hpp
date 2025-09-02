#ifndef PHYSICS_H
#define PHYSICS_H
#include "const.hpp"
//using Verlet integration


class objectCircle{
  public:
    Vector2 currentPosition;
    Vector2 oldPosition;
    Vector2 acceleration;
    double radius = 50.f;
    //double instead of float because it increases precision by a wide margin
    //also the smaller delta time the better for simulations
    
    void NEWPOSITION(float dTime){
        Vector2 displacement = Vector2Subtract(currentPosition, oldPosition);
        oldPosition = currentPosition;
        currentPosition = Vector2Add(Vector2Add(currentPosition, displacement), Vector2Scale(acceleration, dTime*dTime));
        
        //Xn+1 = 2Xn - Xn-1 + a * Δt^2
        
        acceleration = (Vector2){0.f, 0.f};
}
    void DETECTBARRIERS(Vector2 BARRIERS, float restitution) {
    // down side
    if (currentPosition.y + radius >= BARRIERS.y) {
        currentPosition.y = BARRIERS.y - radius;

        Vector2 velocity = Vector2Subtract(currentPosition, oldPosition);        
        velocity.y *= -restitution;
        oldPosition = Vector2Subtract(currentPosition, velocity);
    }

    //top side
    if (currentPosition.y - radius <= 0) {
        currentPosition.y = radius;

        Vector2 velocity = Vector2Subtract(currentPosition, oldPosition);        
        velocity.y *= -restitution;
        oldPosition = Vector2Subtract(currentPosition, velocity);
    }
    
    // left side
    if (currentPosition.x - radius <= 0) {
        currentPosition.x = radius;

        Vector2 velocity = Vector2Subtract(currentPosition, oldPosition);
        velocity.x *= -restitution;

        oldPosition = Vector2Subtract(currentPosition, velocity);
    }

    // right side
    if (currentPosition.x + radius >= BARRIERS.x) {
        currentPosition.x = BARRIERS.x - radius;

        Vector2 velocity = Vector2Subtract(currentPosition, oldPosition);
        velocity.x *= -restitution;

        oldPosition = Vector2Subtract(currentPosition, velocity);
    }
}
 

    void DRAGOBJ(Vector2 mouseVec){
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (mouseVec.x < currentPosition.x + radius && mouseVec.y < currentPosition.y + radius &&
                mouseVec.x > currentPosition.x - radius && mouseVec.y - currentPosition.y - radius) {
                    currentPosition = mouseVec;
            }
        }
    }
    
    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
    }
};








#endif
