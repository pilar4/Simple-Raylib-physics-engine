//drawing
#ifndef DRAW_H
#define DRAW_H
#include "const.hpp"
#include "matrix.hpp"
#include "sand.hpp"

void draw(void){
    InitWindow(screenWidth, screenHeight, "physics");
    SetTargetFPS(60);

    bool running = true;
    

    while(running){
        int tick = 0;
        initMatrix();


        
        while (!WindowShouldClose())
        {
            

            BeginDrawing();
                ClearBackground(BLACK);
                DrawFPS(20, 20); 
                DrawText(TextFormat("Tick: %d", tick), 1800, 20, 20, GREEN);
                
                int mousex = GetMouseX();
                int mousey = GetMouseY();
                
                
                if(IsKeyDown(KEY_S)){
                    makeSand(mousex, mousey);
                }
                
                for(int x=1;x<bx;x++){
                    for(int y=1;y<by;y++){
                        if(matrix[x][y]=='b'){
                            DrawPixel(x, y, GREEN);
                        }
                        if(matrix[x][y]=='s'){
                            DrawPixel(x, y, YELLOW);
                        }
                    }
                }
                
                //DrawSand(500, 300, 10, 10, GOLD);
                
                gravitySand(tick);
                
                tick++;
            
            EndDrawing();



            if(IsKeyPressed(KEY_ESCAPE)){
                running = false;
            }
            if(IsKeyPressed(KEY_C)){
                clearMatrix();
                break;
            }
            
            
            
        }
    }
    CloseWindow();
    
}

#endif

