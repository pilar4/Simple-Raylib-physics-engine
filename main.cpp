#include "headers/headers.h"
#include <chrono>



int main(void){
    
    
    cout<<"\n Startup test \n \n";
    auto startTime = chrono::high_resolution_clock::now();
    
    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);


    bool running = true;
    while(running){

        
        vector<objectCircle> circles;
        vector<rigidBody> rigid;
        t.numerator = 1;
        t.denominator = 60;
        t.timeStopped = false;
        
        



        
        while (!WindowShouldClose())
        {
            
            
            auto currentTime = chrono::high_resolution_clock::now();
            chrono::duration<float> elapsed = currentTime - startTime;
            float runtime = elapsed.count();
            
            
            int fps = GetFPS();
            float mousex = float(GetMouseX());
            float mousey = float(GetMouseY());
            Vector2 mouseVec = {mousex, mousey};
            
            
            //initializing physics
            for (auto& obj : circles) {
                obj.APPLYFORCE(g.GRAVITY);                  
                obj.ISONGROUND(BARRIERS);
                obj.ISONWALL(BARRIERS);
                obj.APPLYFRICTION();           
                obj.UPDATEPOSITION();           
                obj.DETECTBARRIERS(BARRIERS, r.RESTITUTION); 
                obj.PULLOBJ(mouseVec);

                for (auto& sobj : circles) {
                    CIRCLECOLLISION(obj, sobj, r.RESTITUTION);
                }
            }
            
            
            t.UPDATE();
            g.UPDATE();
            r.UPDATE();


            for (auto& obj : rigid) {
              obj.MAKERIGID(mouseVec);
            }
            
            
//Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(TextFormat("FPS: %d", fps), 20, 20, 20, DARKBLUE); 
                DrawText(TextFormat("Run time: %.2f s", runtime), 20, 40, 20, DARKBLUE);
                int fakeNumerator;
                if(t.deltaTime == 0.f) fakeNumerator = 0;
                else fakeNumerator = 1;
                DrawText(TextFormat("Delta time: %d/%d", fakeNumerator, t.denominator), 20, 60, 20, DARKBLUE);
                DrawText(TextFormat("Mouse position: %.f - %.f", mousex, mousey), 20, 80, 20, DARKBLUE);
                DrawText(TextFormat("Restitution: %.3f", r.RESTITUTION), 20, 100, 20, DARKBLUE);
                DrawText(TextFormat("GravityX: %.2f", g.GRAVITY.x/100), 20, 120, 20, DARKBLUE);
                DrawText(TextFormat("GravityX: %.2f", g.GRAVITY.y/100), 20, 140, 20, DARKBLUE);

                
                
                for (auto& obj : circles) {
                    DrawCircleV(obj.position, obj.radius, WHITE);
                    
                    float speedx = obj.velocity.x;  
                    float speedy = obj.velocity.y;   if (obj.onGround) speedy = 0.f;
                    float speed = sqrt(speedx * speedx + speedy * speedy);
                    
                    
                    
                    DrawText(TextFormat("V:%.f", speed), obj.position.x - 25, obj.position.y - 25, 20, BLACK);
                    DrawText(TextFormat("X:%.f", speedx), obj.position.x - 25, obj.position.y - 5, 20, BLACK);
                    DrawText(TextFormat("Y:%.f", speedy), obj.position.x - 25, obj.position.y + 15, 20, BLACK);
                }
                
                for (auto& obj : rigid) {
                    DrawCircleV(obj.position, obj.radius, RED);
                }
                
            
            EndDrawing();
//End of drawing ----------------------------------------------------------------------------------------------------------



            //input handling
            if(IsKeyPressed(KEY_D)){
                circles.push_back({{mousex, mousey}, {0, 0}, {0, 0}});
            }
            if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
                rigid.push_back({mousex, mousey});
            }
            if(IsKeyPressed(KEY_ESCAPE)){
                running = false;
            }
            if(IsKeyPressed(KEY_Q)){
                circles.clear();
                break;
            }

        
            
        }
    }
    
    CloseWindow();
    TESTSRESULTS();
    return 0;
    
    
}