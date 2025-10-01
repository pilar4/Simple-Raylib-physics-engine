#ifndef PHYSICSPBD_H
#define PHYSICSPBD_H
#include "../globalVariables.hpp"
#include "../tests.hpp"
#include "raylib.h"
#include <vector>
#include <cmath>

using namespace std;

// Verlet integration:
// Xn+1 = 2Xn - Xn-1 + a * Δt^2 
// where X is position, n is step (in time), a is acceleration and Δt is delta time


class objectPBD{
  public:
    Vector2 position;
    Vector2 prevPosition;
    Vector2 acceleration;
    double radius = 25.f;
    
    
    static constexpr Color coldColors[5] = { BLUE, DARKBLUE, SKYBLUE, PURPLE, DARKPURPLE };
    Color circleColor = coldColors[GetRandomValue(0, 4)];
    
    bool isDragging = false;

        
    

    void UPDATE(float dt) {
        Vector2 temp = position;
        Vector2 velocity = Vector2Subtract(position, prevPosition); // v = x - x_prev

        // Air resistance / friction
        if (Vector2Length(velocity) > 0.001f) {
            Vector2 friction = Vector2Scale(Vector2Normalize(velocity), -frictionCoefficient);
            acceleration = Vector2Add(acceleration, friction);
        }

        // Verlet integration
        position = Vector2Add(position, Vector2Add(velocity, Vector2Scale(acceleration, dt * dt)));
        prevPosition = temp;

        // Reset acceleration
        acceleration = {
            0,
            0
        };

        
        // Bottom
        if (position.y + radius > screenHeight) {
            position.y = screenHeight - radius;

            Vector2 velocity = Vector2Subtract(position, prevPosition);

            velocity.y *= -r.RESTITUTION;

            prevPosition = Vector2Subtract(position, velocity);
        }

        // Top
        if (position.y - radius < 0) {
            position.y = radius;
            
            velocity = Vector2Subtract(position, prevPosition);
            
            velocity.y *= -r.RESTITUTION;
            
            prevPosition.y = position.y - velocity.y;
        }
        
        // Left
        if (position.x - radius < 0) {
            position.x = radius;
            
            velocity = Vector2Subtract(position, prevPosition);
            
            velocity.x *= -r.RESTITUTION;
            
            prevPosition.x = position.x - velocity.x;
        }
        
        // Right
        if (position.x + radius > screenWidth) {
            position.x = screenWidth - radius;
            
            velocity = Vector2Subtract(position, prevPosition);
            
            velocity.x *= -r.RESTITUTION;
            
            prevPosition.x = position.x - velocity.x;
        }

        setTest(TEST_SAND_UPDATE);
    }
    
    void PULLBALL(Vector2 mousePos) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            //check if mouse is dragging
            if (!isDragging &&
                mousePos.x < position.x + radius && mousePos.y < position.y + radius &&
                mousePos.x > position.x - radius && mousePos.y > position.y - radius) {
                isDragging = true;
            }

            if (isDragging) {
                //move obj to new position that is mouse position, vector delta is there 
                //to make prev position
                Vector2 delta = Vector2Subtract(mousePos, position);
                position = mousePos;

                prevPosition = Vector2Subtract(position, Vector2Scale(delta, 0.5f));
            }
        } else {
            isDragging = false;
        }
    }



    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
        setTest(TEST_APPLYFORCE_SAND);
    }

    void Draw() {
        DrawCircleV(position, radius, circleColor);
        setTest(TEST_DRAW_SAND);
    }
};







#endif
