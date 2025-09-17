#ifndef PHYSICSPBD_H
#define PHYSICSPBD_H
#include "globalVariables.hpp"
#include "tests.hpp"
#include "raylib.h"
#include <vector>
#include <cmath>

//Verlet integration
//Xn+1 = 2Xn - Xn-1 + a * Δt^2 
//where X is position, n is step (in time), a is acceleration and Δt is delta time


class SandParticle {
public:
    Vector2 position;        
    Vector2 prevPosition;    
    Vector2 acceleration;
    float radius;
    Color color;

    SandParticle(Vector2 pos, float r = 1.0f, Color c = GOLD)
        : position(pos), prevPosition(pos), acceleration({0, 0}), radius(r), color(c) {}
    

    void UPDATE(float dt) {
    Vector2 temp = position;
    Vector2 velocity = Vector2Subtract(position, prevPosition);   // v = x - x_prev

    // Zastosowanie tarcia od razu
    float frictionCoefficient = 0.98f; // ustaw swój współczynnik
    velocity = Vector2Scale(velocity, frictionCoefficient);

    // Verlet integration
    position = Vector2Add(position, Vector2Add(velocity, Vector2Scale(acceleration, dt * dt)));
    prevPosition = temp;

    // Reset acceleration
    acceleration = {0, 0};

    // Ograniczenia ekranu
    if (position.y + radius > screenHeight) position.y = screenHeight - radius;
    if (position.y - radius < 0) position.y = radius;
    if (position.x - radius < 0) position.x = radius;
    if (position.x + radius > screenWidth) position.x = screenWidth - radius;

    setTest(TEST_SAND_UPDATE);
}

    
    

    

    void APPLYFORCE(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
        
        setTest(TEST_APPLYFORCE_SAND);
    }

    void Draw() {
        DrawRectangleV({position.x - radius, position.y - radius}, {radius * 2, radius * 2}, color);
        setTest(TEST_DRAW_SAND);
    }
};

void HANDLECOLLISION(SandParticle& A, SandParticle& B) {
    Vector2 displacement = Vector2Subtract(B.position, A.position);
    float distance = Vector2Length(displacement);
    float minDist = A.radius + B.radius;

    if (distance < minDist && distance > 0.0f) {
        //normalize vector
        Vector2 normal = Vector2Scale(displacement, 1.0f / distance);

        // Penetration correction
        float penetration = minDist - distance;
        Vector2 correction = Vector2Scale(normal, penetration * 0.5f);
        A.position = Vector2Subtract(A.position, correction);
        B.position = Vector2Add(B.position, correction);

        // velocity from verlet (old and new position)
        Vector2 vA = Vector2Subtract(A.position, A.prevPosition);
        Vector2 vB = Vector2Subtract(B.position, B.prevPosition);
        Vector2 relativeVel = Vector2Subtract(vB, vA);

        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

        // if theye are moving in opposite dir
        if (velAlongNormal > 0.0f) return;

        // let them have the same weight
        float e = r.RESTITUTION;

        float j = -(1.0f + e) * velAlongNormal / 2.0f;

        Vector2 impulse = Vector2Scale(normal, j * 0.008);

        A.prevPosition = Vector2Subtract(A.prevPosition, impulse);
        B.prevPosition = Vector2Add(B.prevPosition, impulse);
    }
    setTest(TEST_SAND_COLLISION);
    
}


void SandBrushCollision(SandParticle& sand, const Brush& brush, float restitution) {
    float nearestX = fmaxf(brush.rect.x, fminf(sand.position.x, brush.rect.x + brush.rect.width));
    float nearestY = fmaxf(brush.rect.y, fminf(sand.position.y, brush.rect.y + brush.rect.height));

    float dx = sand.position.x - nearestX;
    float dy = sand.position.y - nearestY;
    float distance = sqrtf(dx*dx + dy*dy);

    if (distance < sand.radius) {
        Vector2 normal;
        if (distance > 0.0001f) {
            normal = {dx / distance, dy / distance};
        } else {
            normal = {0, -1};
        }

        
        float penetration = sand.radius - distance;
        sand.position.x += normal.x * penetration;
        sand.position.y += normal.y * penetration;

        // Verlet: v = pos - prevPos
        Vector2 v = { sand.position.x - sand.prevPosition.x,
                      sand.position.y - sand.prevPosition.y };

        float velAlongNormal = Vector2DotProduct(v, normal);

        //if it flies to brush, same as in circle
        if (velAlongNormal < 0.0f) {
            
            float j = -(1.0f + restitution) * velAlongNormal;

            Vector2 impulse = { normal.x * j * 0.008f, normal.y * j * 0.008f};

            
            sand.prevPosition.x -= impulse.x;
            sand.prevPosition.y -= impulse.y;
        }
    }
    
    setTest(TEST_SAND_BRUSH_COLLISION);
}





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
            
            for (auto &sp : particles){
                HANDLECOLLISION(p, sp);
            }
            
            setTest(TEST_SAND_UMAIN);
        }
        
    }

    void Draw() {
        for (auto &p : particles) {
            p.Draw();
        }
        
        setTest(TEST_SAND_DRAW);
    }
    
    void RESETSAND(void){
        particles.clear();
    }
    
    
};




#endif
