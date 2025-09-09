#ifndef PHYSICSEULER_H
#define PHYSICSEULER_H
#include "globalVariables.hpp"
#include "simulationSettings.hpp"
#include "tests.hpp"
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
        //V(t+dt) = v(t) + a * dt
        velocity = Vector2Add(velocity, Vector2Scale(acceleration, t.deltaTime));
        position = Vector2Add(position, Vector2Scale(velocity, t.deltaTime));
        acceleration = (Vector2){0.f, 0.f};

        setTest(TEST_UPDATEPOSITION);
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

        setTest(TEST_DETECTBARRIERS);
    }

    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
        setTest(TEST_APPLYFRICTION);
    }

    void PULLOBJ(Vector2 mouseVec) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !t.timeStopped) {
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
        } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && t.timeStopped) {
            if (!isDragging && 
                mouseVec.x < position.x + radius && mouseVec.y < position.y + radius &&
                mouseVec.x > position.x - radius && mouseVec.y > position.y - radius) {
                isDragging = true;
            }

            if (isDragging) {
                // drag to mouse
                position = mouseVec;
                velocity = {0.0};
            }
        } else {
            isDragging = false;
        }

        setTest(TEST_PULLOBJ);
    }
    
    bool onGround = false;
    bool onWall = false;
    void ISONGROUND(Vector2 BARRIERS) {
        if (position.y + radius >= BARRIERS.y - 0.5f || position.y - radius <= 0.5f) { //little bit of float error "0.5f"
            onGround = true;
        } else {
            onGround = false;
        }
        setTest(TEST_ISONGROUND);
    }
    void ISONWALL(Vector2 BARRIERS) {
        if (position.x - radius <= 0.5f || position.x + radius >= BARRIERS.x - 0.5f) { //little bit of float error "0.5f"
            onWall = true;
        } else {
            onWall = false;
        }
        setTest(TEST_ISONWALL);
    }

    void APPLYFRICTION() {
        if (onGround && Vector2Length(velocity) > 0.001f) {
            Vector2 friction = Vector2Scale(Vector2Normalize(velocity), -frictionCoefficient);
            APPLYFORCE(friction);
        }

        setTest(TEST_APPLYFORCE);
    }

};

void CIRCLECOLLISION(objectCircle& A, objectCircle& B, float restitution) {
    Vector2 displacement = Vector2Subtract(B.position, A.position);
    float distance = Vector2Length(displacement);
    float minDist = A.radius + B.radius;

    if (distance < minDist && distance > 0.0f) {
        // normal = displacement / distance
        Vector2 normal = Vector2Scale(displacement, 1.0f / distance);

        // makes bodies not overlap
        float penetration = minDist - distance;
        Vector2 correction = Vector2Scale(normal, penetration / 2.0f);
        A.position = Vector2Subtract(A.position, correction);
        B.position = Vector2Add(B.position, correction);

        // relative velocity along normal
        Vector2 relativeVel = Vector2Subtract(B.velocity, A.velocity);
        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

        if (velAlongNormal > 0) return; // moving apart

        float j = -(1.0f + restitution) * velAlongNormal / 2.0f;
        Vector2 impulse = Vector2Scale(normal, j);

        A.velocity = Vector2Subtract(A.velocity, impulse);
        B.velocity = Vector2Add(B.velocity, impulse);
    }

    setTest(TEST_CIRCLE_COLLISION);
}

class Brush {
  public:
    Rectangle rect;
    Color color = GRAY;

    Brush(float x, float y, float w, float h) {
        rect = {x, y, w, h};
    }

    void Draw() {
        DrawRectangleRec(rect, color);
    }
};


void CircleBrushCollision(objectCircle& circle, const Brush& brush, float restitution) {
    // find nearest point from square to circle
    //fminf means pick smaller number from two and vice versa with fmaxf
    
    
    //                realy smart line lmao no way i would figuer it out
    //                if circle position is bigger than right side of rectangle position then nearest is set as right side of square
    //                and if circle position is more to the left than the left side of square, value is set as this side
    //                OTHERWISE, the nearest is set as circle position, same with y axis
    
    //                  left side of rectangle                            right side of rectangle
    float nearestX = fmaxf(brush.rect.x, fminf(circle.position.x, brush.rect.x + brush.rect.width));
    float nearestY = fmaxf(brush.rect.y, fminf(circle.position.y, brush.rect.y + brush.rect.height));

    //calc distance
    float dx = circle.position.x - nearestX;
    float dy = circle.position.y - nearestY;
    float distance = sqrt(dx*dx + dy*dy);

    if (distance < circle.radius) {
        Vector2 normal;
        
        // 0.0001 so there is no division by 0
        if (distance > 0.0001f) {                           //IMPORTANT, vec normal is from square to circle ONLY and not otherwise
            normal = {dx / distance, dy / distance};        //so if vel is in the same direction it will have a positive num, this is why there is if there
        } else {                                     
            normal = {0, -1};  // if somehow distance is even closer to 0 and all hell let loose
        }

        // to fix clipping
        float penetration = circle.radius - distance;
        circle.position.x += normal.x * penetration;
        circle.position.y += normal.y * penetration;
      
        // 
        float velAlongNormal = Vector2DotProduct(circle.velocity, normal);  //relative velocity
        if (velAlongNormal < 0) {                  //         <----------------------------------------------- here
            circle.velocity.x -= (1 + r.RESTITUTION) * velAlongNormal * normal.x;
            circle.velocity.y -= (1 + r.RESTITUTION) * velAlongNormal * normal.y;
        }
    }
}


#endif
