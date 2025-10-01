#ifndef OBJECTSSYSTEM_H
#define OBJECTSSYSTEM_H
#include "physicsEuler.hpp"
#include "physicsPBD.hpp"
#include "brush.hpp"



void HANDLECOLLISION(objectPBD& A, objectPBD& B) {
    Vector2 displacement = Vector2Subtract(B.position, A.position);
    float distance = Vector2Length(displacement);
    float minDist = A.radius + B.radius;

    if(distance < minDist && distance > 0.0f) {
        Vector2 normal = Vector2Scale(displacement, 1.0f / distance);
        float penetration = minDist - distance;


        


        float correctionFactor = 0.5f;
        Vector2 correction = Vector2Scale(normal, penetration * correctionFactor);

        A.position = Vector2Subtract(A.position, correction);
        B.position = Vector2Add(B.position, correction);
    }

    setTest(TEST_PBD_COLLISION);
}

void CircleBrushCollision(objectEuler& circle, const Brush& brush, float restitution) {
    // find nearest point from square to circle
    //fminf means pick smaller number from two and vice versa with fmaxf
    
    
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
            normal = {dx / distance, dy / distance};        //so if vel is in the same direction it will have a positive num, 
                                                            //this is   why there is if there
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
    setTest(TEST_BRUSH_CIRCLE);
}





void BallBrushCollision(objectPBD& ball, const Brush& brush, float restitution) {
    float nearestX = fmaxf(brush.rect.x, fminf(ball.position.x, brush.rect.x + brush.rect.width));
    float nearestY = fmaxf(brush.rect.y, fminf(ball.position.y, brush.rect.y + brush.rect.height));

    float dx = ball.position.x - nearestX;
    float dy = ball.position.y - nearestY;
    float distance = sqrtf(dx*dx + dy*dy);

    if (distance < ball.radius) {
        Vector2 normal;
        if (distance > 0.0001f) {
            normal = {dx / distance, dy / distance};
        } else {
            normal = {0, -1};
        }

        float penetration = ball.radius - distance;
        ball.position.x += normal.x * penetration;
        ball.position.y += normal.y * penetration;

        // Verlet: v = pos - prevPos
        Vector2 v = {ball.position.x - ball.prevPosition.x, ball.position.y - ball.prevPosition.y};

        float velAlongNormal = Vector2DotProduct(v, normal);

        if (velAlongNormal < 0.0f) {
            float j = -(1.0f + restitution) * velAlongNormal;
            Vector2 impulse = { normal.x * j, normal.y * j};

            ball.prevPosition.x -= impulse.x;
            ball.prevPosition.y -= impulse.y;
        }
    }
    
    setTest(TEST_PBD_BRUSH_COLLISION);
}


void PBD_EULER_COLLISION(objectPBD& pbdBall, objectEuler& eulerBall, float restitution) {
    Vector2 disp = Vector2Subtract(eulerBall.position, pbdBall.position);
    float dist = Vector2Length(disp);
    float minDist = pbdBall.radius + eulerBall.radius;

    if(dist < minDist && dist > 0.0001f) {
        Vector2 normal = Vector2Scale(disp, 1.0f / dist);
        float penetration = minDist - dist;

        
        Vector2 correction = Vector2Scale(normal, penetration * 0.5f);

        
        pbdBall.position = Vector2Subtract(pbdBall.position, correction);

        
        eulerBall.position = Vector2Add(eulerBall.position, correction);

        
        Vector2 relativeVel = eulerBall.velocity;
        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

        if(velAlongNormal < 0) {
            float j = -(1 + restitution) * velAlongNormal;
            Vector2 impulse = Vector2Scale(normal, j);
            eulerBall.velocity = Vector2Add(eulerBall.velocity, impulse);
        }
    }
}

class ObjectsSystemPBD {
  public:
    vector<objectPBD> particles;
    
    void AddParticlePBD(Vector2 mousePos) {
        particles.push_back({mousePos, mousePos, {0,0}, 25.f});
        setTest(TEST_ADD_PBD);
    }

    void UPDATEPBD(float dt, Vector2 mousePos) {
        if (dt == 0.0f) return;  //time stop

        for (auto &p : particles) {
            p.APPLYFORCE(g.GRAVITY);
            p.UPDATE(dt);
            p.PULLBALL(mousePos);
            for (auto &sp : particles) {
                if (&p != &sp) HANDLECOLLISION(p, sp);
            }

        
        }
        setTest(TEST_PBD_UMAIN);
    }


    void Draw() {
        for (auto &p : particles) {
            p.Draw();
        }
        setTest(TEST_PBD_DRAW);
    }
    
    void RESETBALLS(void){
        particles.clear();
    }
};






#endif