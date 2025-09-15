#ifndef PHYSICSPBD_H
#define PHYSICSPBD_H
#include "globalVariables.hpp"
#include "tests.hpp"
#include "raylib.h"
#include <vector>
#include <cmath>

using namespace std;



class SandParticle {
public:
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;

    SandParticle(Vector2 pos, float r = 3.0f, Color c = GOLD)
        : position(pos), radius(r), color(c) {
        velocity = {0.0f, 0.0f};
    }

    void Update() {
        // Apply g.GRAVITY
        velocity.y += g.GRAVITY.y * t.deltaTime;

        // Update position
        position.x += velocity.x * t.deltaTime;
        position.y += velocity.y * t.deltaTime;

        // Simple floor collision
        if (position.y + radius > screenHeight) {
            position.y = screenHeight - radius;
            velocity.y *= -0.3f;  // bounce with damping
        }

        // Left/right screen bounds
        if (position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -0.3f;
        }
        if (position.x + radius > screenWidth) {
            position.x = screenWidth - radius;
            velocity.x *= -0.3f;
        }
    }

    void Draw() {
        DrawCircleV(position, radius, color);
    }
};

// Optional: simple Sand system
class SandSystem {
public:
    vector<SandParticle> particles;

    void AddParticle(Vector2 pos) {
        particles.push_back(SandParticle(pos));
    }

    void Update() {
        for (auto &p : particles) {
            p.Update();
        }
    }

    void Draw() {
        for (auto &p : particles) {
            p.Draw();
        }
    }
};





#endif