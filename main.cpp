#include "headers/headers.h"



//rigid body, new struct, velocity vector?, only need to find firs occurance of rectangle char
//in matrix, simulate it as a whole

int main(void){
    
    
    cout<<"\n check no1 \n \n";
    
    
    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);

    

    bool running = true;
    while(running){
        int tick = 0;
        
        vector<objectCircle> circles;
        vector<rigidBody> rigid;
        
        


        
        while (!WindowShouldClose())
        {
            
            
            tick++;
            float mousex = float(GetMouseX());
            float mousey = float(GetMouseY());
            Vector2 mouseVec = {mousex, mousey};
            
            //initializing physics
            for (auto& obj : circles) {
                obj.APPLYFORCE(GRAVITY);
                obj.NEWPOSITION(DELTATIME);
                obj.DETECTBARRIERS(BARRIERS, RESTITUTION);
                obj.PULLOBJ(mouseVec);
            }

            for(int i=0;i<circles.size();i++){
                for(int j=0;j<circles.size();j++){
                    HANDLECOLLISION(circles[i], circles[j]);
                }
            }

            for (auto& obj : rigid) {
              obj.MAKERIGID(mouseVec);
            }
            
            
//Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();
                ClearBackground(BLACK);
                DrawFPS(20, 20); 
                DrawText(TextFormat("Tick: %d", tick), BARRIERS.x - 200, 20, 20, GREEN);
                
                
                for (auto& obj : circles) {
                    DrawCircleV(obj.currentPosition, obj.radius, WHITE);
                }
                
                for (auto& obj : rigid) {
                    DrawCircleV(obj.position, obj.radius, RED);
                }
                
            
            EndDrawing();
//End of drawing ----------------------------------------------------------------------------------------------------------



            //input handling
            if(IsKeyPressed(KEY_D)){
                circles.push_back({{mousex, mousey}, {mousex, mousey}, {0, 0}});
            }
            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
                rigid.push_back({mousex, mousey});
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
