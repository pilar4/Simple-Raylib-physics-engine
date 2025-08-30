#ifndef DRAW_H
#define DRAW_H
#include "const.h"
#include "liquid.h"

void draw(void){
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
                //    l.pos.y = gravity_force(l.weight, l.pos.y);
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
    
}

#endif

