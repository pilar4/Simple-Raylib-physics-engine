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


class BallParticle {
  public:
    Vector2 position;        
    Vector2 prevPosition;    
    Vector2 acceleration;
    double radius;
    Color color;
    
    bool isDragging = false;

    BallParticle(Vector2 pos, float r = 25.0f, Color c = GOLD)
        : position(pos), prevPosition(pos), acceleration({0, 0}), radius(r), color(c) {
            
            static constexpr Color coldColors[5] = { BLUE, DARKBLUE, SKYBLUE, PURPLE, DARKPURPLE };
            color = coldColors[GetRandomValue(0, 4)];
        }
    

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

        // === Screen boundaries with bounce ===
        // Bottom
        if (position.y + radius > screenHeight) {
            position.y = screenHeight - radius;

            // Oblicz prędkość (Verlet)
            Vector2 velocity = Vector2Subtract(position, prevPosition);

            // Zastosuj restitution tylko na osi Y
            velocity.y *= -r.RESTITUTION;

            // Zachowaj X bez strat, bo to podłoga (nie ściana)
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
            // sprawdź, czy myszka jest w obrębie kulki
            if (!isDragging &&
                mousePos.x < position.x + radius && mousePos.y < position.y + radius &&
                mousePos.x > position.x - radius && mousePos.y > position.y - radius) {
                isDragging = true;
            }

            if (isDragging) {
                // przesuń kulkę do myszki
                Vector2 delta = Vector2Subtract(mousePos, position);
                position = mousePos;

                // ustaw prevPosition, aby Verlet zachował prędkość
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
        DrawCircleV(position, radius, color);
        setTest(TEST_DRAW_SAND);
    }
};







#endif
