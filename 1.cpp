#include "raylib.h"
#include <iostream>
#include <vector>

using namespace std;

const float GRAVITY = 1;
const Vector2 BARRIERS = {2000, 1000};

struct liquid {
    Vector2 pos;
    float weight = GRAVITY * 1;
    Color color = BLUE;
};

float liquidPhysics(float weight, float posY, float posX, vector<liquid> vec){
    float newposY = posY;
    if(posY >= BARRIERS.y){
        newposY = BARRIERS.y - 1;
        return newposY;
    }
    
    for(auto element: vec){
        if(element.pos.y == posY - 1){
            
        }
    }
    newposY = BARRIERS.y-1;
    }
    else{
        newposY += weight;
    }
    
    
    
    
    return newposY;
}



int main(void)
{
    const float screenWidth = BARRIERS.x;
    const float screenHeight = BARRIERS.y;

    InitWindow(screenWidth, screenHeight, "physics");
    SetTargetFPS(60);

    bool running = true;

    while(running){
        
        int counter = 0;
        
        vector<Vector2> brush;
        vector<liquid> vecLiquid;
        
        
        while (!WindowShouldClose())
        {
            Vector2 mousePos = GetMousePosition();

            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                brush.push_back(mousePos);
            }
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            vecLiquid.push_back({mousePos});
            }
            

            BeginDrawing();
                ClearBackground(BLACK);
            
                for(auto &pos : brush){
                    DrawCircleV(pos, 10, RED);
                }
                for(auto &l : vecLiquid){
                    DrawPixelV(l.pos, l.color);
                    l.pos.y = gravity_force(l.weight, l.pos.y);
                }
            
            DrawText(("Counter: " + to_string(counter)).c_str(), 10, 10, 20, WHITE);

            
            
            
            EndDrawing();

            if(IsKeyPressed(KEY_ESCAPE)){
                running = false;
            }
            if(IsKeyPressed(KEY_C)){
                break;
            }
            
        }
    
        counter++;
    }
    CloseWindow();
    return 0;
}
