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

float gravity_force(float weight, float pos){
    float newpos = pos;
    if(pos >= BARRIERS.y){
        return BARRIERS.y - 1;
    }
    else{
        newpos += weight;
    }
    return newpos;
}

int main(void)
{
    const float screenWidth = BARRIERS.x;
    const float screenHeight = BARRIERS.y;

    InitWindow(screenWidth, screenHeight, "physics");
    SetTargetFPS(144);

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
