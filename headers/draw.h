//drawing

#ifndef DRAW_H
#define DRAW_H
#include "const.h"
#include "liquid.h"
#include "matrix.h"

void draw(void){
    InitWindow(screenWidth, screenHeight, "physics");
    SetTargetFPS(60);

    bool running = true;

    while(running){
        

        
        while (!WindowShouldClose())
        {


            BeginDrawing();
                ClearBackground(BLACK);
                DrawFPS(20, 20); 
                
                for(int x=1;x<bx;x++){
                    for(int y=1;y<by;y++){
                        if(matrix[x][y]=='b'){
                            DrawPixel(x, y, GREEN);
                        }
                    }
                   
                }
                
            
            EndDrawing();



            if(IsKeyPressed(KEY_ESCAPE)){
                running = false;
            }
            if(IsKeyPressed(KEY_C)){
                break;
            }
            
            
            
        }
    }
    CloseWindow();
    
}

#endif

