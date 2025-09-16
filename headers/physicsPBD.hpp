#ifndef PHYSICSPBD_H
#define PHYSICSPBD_H
#include "globalVariables.hpp"
#include "tests.hpp"
#include "raylib.h"
#include <vector>
#include <cmath>




class SandParticle {
public:
    Vector2 position;        
    Vector2 prevPosition;    
    Vector2 acceleration;    
    float radius;
    Color color;

    SandParticle(Vector2 pos, float r = 3.0f, Color c = GOLD)
        : position(pos), prevPosition(pos), acceleration({0, 0}), radius(r), color(c) {}

    void UPDATE(float dt) {
        // Verlet integration
        Vector2 temp = position;
        Vector2 velocity = position - prevPosition;   // v = x - x_prev
        position += velocity + acceleration * (dt * dt);  
        prevPosition = temp;

        // Reset acceleration
        acceleration = {0, 0};

        // Kolizja z podłożem (position correction zamiast velocity bounce)
        if (position.y + radius > screenHeight) position.y = screenHeight - radius;
        if (position.y - radius < 0) position.y = 0 + radius;
        // Kolizja z bokami
        if (position.x - radius < 0) position.x = radius;
        if (position.x + radius > screenWidth) position.x = screenWidth - radius;
        
        setTest(TEST_SAND_UPDATE);
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

// System PBD
class SandSystem {
public:
    vector<SandParticle> particles;

    void AddParticle(Vector2 pos) {
        particles.push_back(SandParticle(pos));
        
        setTest(TEST_ADD_SAND);
    }

    void UPDATE(float dt) {
        for (auto &p : particles) {
            p.APPLYFORCE(g.GRAVITY);
            p.UPDATE(dt);
            
            setTest(TEST_SAND_UMAIN);
        }
        
    }

    void Draw() {
        for (auto &p : particles) {
            p.Draw();
        }
        
        setTest(TEST_SAND_DRAW);
    }
};




#endif