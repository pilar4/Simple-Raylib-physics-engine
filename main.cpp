#include "headers/headers.h"


//rigid body, new struct, velocity vector?, only need to find firs occurance of rectangle char
//in matrix, simulate it as a whole

int main(void){
    
    
    cout<<"\n check no1 \n \n";
    
    
    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);

    

    bool running = true;
    while(running){

        
        
        vector<object> circles;
        
        


        
        while (!WindowShouldClose())
        {
            
            
            
            float mousex = float(GetMouseX());
            float mousey = float(GetMouseY());
            
            //initializing physics
            for (auto& obj : circles) {
                obj.applyForce(GRAVITY);
                obj.NEWPOSITION(dt);
            }
            
            
//Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();
                ClearBackground(BLACK);
                DrawFPS(20, 20); 
                
                
                
                for (auto& obj : circles) {
                    DrawCircleV(obj.currentPosition, 10.f, RED);
                }
                
                
            
            EndDrawing();
//End of drawing ----------------------------------------------------------------------------------------------------------

            //input handling
            if(IsKeyDown(KEY_D)){
                circles.push_back({{mousex, mousey}, {mousex, mousey}, {0, 0}});
            }
            if(IsKeyPressed(KEY_ESCAPE)){
                running = false;
            }
            if(IsKeyPressed(KEY_C)){
                circles.clear();
                break;
            }

        
            
        }
    }
    
    CloseWindow();
    return 0;
    
}