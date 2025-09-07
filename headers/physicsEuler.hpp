#ifndef PHYSICSEULER_H
#define PHYSICSEULER_H
#include "const.hpp"
#include "simulationSettings.hpp"
// using semi-implicit Euler


class objectCircle{
  public:
    
    Vector2 position;      
    Vector2 velocity;       
    Vector2 acceleration;
    double radius = 50.f;
    //double instead of float because it increases precision by a wide margin
    //also the smaller delta time the better for simulations
    
    
    bool isDragging = false;
    Vector2 lastMousePos = {0.0f, 0.0f};
    

    
    void UPDATEPOSITION(){
        //V(t+dt) ​= v(t) ​+ a * dt
        velocity = Vector2Add(velocity, Vector2Scale(acceleration, t.deltaTime));
        position = Vector2Add(position, Vector2Scale(velocity, t.deltaTime));
        
        acceleration = (Vector2){0.f, 0.f};
       
    }
    
    void DETECTBARRIERS(Vector2 BARRIERS, float restitution) {
        // downside
        if (position.y + radius >= BARRIERS.y) {
            position.y = BARRIERS.y - radius;
            velocity.y *= -restitution;
        }

        // upside
        if (position.y - radius <= 0) {
            position.y = radius;
            velocity.y *= -restitution;
        }

        // left side
        if (position.x - radius <= 0) {
            position.x = radius;
            velocity.x *= -restitution;
        }

        // right side
        if (position.x + radius >= BARRIERS.x) {
            position.x = BARRIERS.x - radius;
            velocity.x *= -restitution;
        }
    }

    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
    }

    void PULLOBJ(Vector2 mouseVec) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // check if mouse is on circle
            if (!isDragging && 
                mouseVec.x < position.x + radius && mouseVec.y < position.y + radius &&
                mouseVec.x > position.x - radius && mouseVec.y > position.y - radius) {
                isDragging = true;
            }

            if (isDragging) {
                // drag to mouse
                position = mouseVec;

                //update velocity
                velocity = Vector2Scale(Vector2Subtract(mouseVec, lastMousePos), 1.0f / t.deltaTime);

                lastMousePos = mouseVec;
            }
        } else {
        isDragging = false;
        }
    }
};


void CIRCLECOLLISION(objectCircle& A, objectCircle& B, float restitution = 1.0f) {
    Vector2 displacement = Vector2Subtract(B.position, A.position);
    float distance = Vector2Length(displacement);
    float minDist = A.radius + B.radius;

    if (distance < minDist && distance > 0.0f) {
        
        
        // normal = displacement / distance,     it is normalized vector so that length = 1 from A to B it defines the collision axis 
        // and can be used to perform calculations so that it only changes direction (because lengh = 1 so force doesn't change)
        Vector2 normal = Vector2Scale(displacement, 1.0f / distance);

        //makes bodies not overlap
        float penetration = minDist - distance;
        //penetration / 2 because it corrects both bodies 
        Vector2 correction = Vector2Scale(normal, penetration / 2.0f);
        A.position = Vector2Subtract(A.position, correction);
        B.position = Vector2Add(B.position, correction);

        // // Calculate relative velocity and v along the normal
        Vector2 relativeVel = Vector2Subtract(B.velocity, A.velocity);
        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

        if (velAlongNormal > 0) return; // They are moving apart

        // calculate impulse scalar
        // law of conservation of momentum
        // J = -(1 + e) * (v * n / 2)
        // where J is impulse, e is restitution, v is velocity, n is normal (v * n equals velAlongNormal in this case)
        float j = -(1.0f + restitution) * velAlongNormal / 2.0f;

        Vector2 impulse = Vector2Scale(normal, j);

        // add impulse
        A.velocity = Vector2Subtract(A.velocity, impulse);
        B.velocity = Vector2Add(B.velocity, impulse);
    }
}







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



#endif