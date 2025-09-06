#ifndef PHYSICS_H
#define PHYSICS_H
#include "const.hpp"



class objectCircle{
  public:
    Vector2 currentPosition;
    Vector2 oldPosition;
    Vector2 acceleration;
    double radius = 50.f;
    //double instead of float because it increases precision by a wide margin
    //also the smaller delta time the better for simulations
    
    //using Verlet integration
    
    void NEWPOSITION(float dTime){
        Vector2 displacement = Vector2Subtract(currentPosition, oldPosition);
        oldPosition = currentPosition;
        currentPosition = Vector2Add(Vector2Add(currentPosition, displacement), Vector2Scale(acceleration, dTime*dTime));
        
        //Xn+1 = 2Xn - Xn-1 + a * Δt^2
        //where X is position, n is step (in time), a is acceleration and Δt is delta time
      
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
 

    void PULLOBJ(Vector2 mouseVec){
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (mouseVec.x < currentPosition.x + radius && mouseVec.y < currentPosition.y + radius &&
                mouseVec.x > currentPosition.x - radius && mouseVec.y > currentPosition.y - radius) {
                    currentPosition = mouseVec;
            }
        }
    }
    

    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
    }
    



   


};



class rigidBody{
  public: 
    Vector2 position;
    double radius = 10.f;

    void MAKERIGID(Vector2 mouseVec){
        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            position = mouseVec;

        }
    }

};


void HANDLECOLLISION(objectCircle& A, objectCircle& B) {
    Vector2 displacement = Vector2Subtract(B.currentPosition, A.currentPosition);
    float distance = Vector2Length(displacement);
    float minDist = A.radius + B.radius; 
        
        
    if (distance < minDist && distance > 0.0f) {
            
            
        // normal = displacement / distance,     it is normalized vector so that length = 1 from A to B it defines the collision axis 
        // and can be used to perform calculations so that it only changes direction (because lengh = 1 so force doesn't change)
        Vector2 normal = Vector2Scale(displacement, 1.0f / distance);



        //makes bodies not overlap
        float penetration = minDist - distance;
        Vector2 correction = Vector2Scale(normal, penetration / 2.0f);
        //penetration / 2 because it corrects both bodies 
        A.currentPosition = Vector2Subtract(A.currentPosition, correction);
        B.currentPosition = Vector2Add(B.currentPosition, correction);



        // Calculate velocities
        Vector2 vA = Vector2Subtract(A.currentPosition, A.oldPosition);
        Vector2 vB = Vector2Subtract(B.currentPosition, B.oldPosition);
        Vector2 relativeVel = Vector2Subtract(vB, vA);
        // Velocity along the normal
        float velAlongNormal = Vector2DotProduct(relativeVel, normal);


        if (velAlongNormal > 0) return; // They are moving apart


        // calculate impulse scalar
        // law of conservation of momentum
        // J = -(1 + e) * (v * n / 2)
        // where J is impulse, e is restitution, v is velocity, n is normal (v * n equals velAlongNormal in this case)
        
        float impulse = -(1.0f + RESTITUTION) * velAlongNormal / 2.0f;

        Vector2 impulseVec = Vector2Scale(normal, impulse);

        // apply impulse to old positions to simulate bounce
        A.oldPosition = Vector2Subtract(A.oldPosition, impulseVec);
        B.oldPosition = Vector2Add(B.oldPosition, impulseVec);
        
    }
}








#endif
