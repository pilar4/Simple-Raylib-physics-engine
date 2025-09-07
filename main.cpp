#include "headers/headers.h"
#include <chrono>
// MOZNA BY ZMIENIC TE WSZYSTKIE VECTOR2ADD ITD NA WLASNA MATEMATYKE I ZROBIC Z TEGO NOWY HEADER
// PISAC POLOZENIE I MOZE PREDKOSC NA KULKACH

//rigid body, new struct, velocity vector?, only need to find firs occurance of rectangle char
//in matrix, simulate it as a whole

int main(void){
    
    
    cout<<"\n check no1 \n \n";
    auto startTime = chrono::high_resolution_clock::now();
    
    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);


    bool running = true;
    while(running){
        int tick = 0;
        
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
            tick++;
            float mousex = float(GetMouseX());
            float mousey = float(GetMouseY());
            Vector2 mouseVec = {mousex, mousey};
            
            
            //initializing physics
            for (auto& obj : circles) {
                obj.APPLYFORCE(GRAVITY);
                obj.UPDATEPOSITION();
                obj.DETECTBARRIERS(BARRIERS, RESTITUTION);
                obj.PULLOBJ(mouseVec);
                for (auto& sobj : circles) {
                    CIRCLECOLLISION(obj, sobj);
                }
            }
            
            
            t.UPDATE();
            


            for (auto& obj : rigid) {
              obj.MAKERIGID(mouseVec);
            }
            
            
//Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(TextFormat("FPS: %d", fps), 100, 20, 20, WHITE); 
                DrawText(TextFormat("Run time: %.2f s", runtime), 20, 40, 20, WHITE);
                int fakeNumerator;
                if(t.deltaTime == 0.f) fakeNumerator = 0;
                else fakeNumerator = 1;
                DrawText(TextFormat("Delta time: %d/%d", fakeNumerator, t.denominator), 20, 60, 20, WHITE);
                DrawText(TextFormat("Mouse position: %.f - %.f", mousex, mousey), 20, 80, 20, WHITE);
                DrawText(TextFormat("Restitution: %.2f", RESTITUTION), 20, 100, 20, WHITE);
                DrawText(TextFormat("Gravity: %.2f", GRAVITY.y/100), 20, 120, 20, WHITE);

                
                
                for (auto& obj : circles) {
                    DrawCircleV(obj.position, obj.radius, WHITE);
                    
                    float speedx = obj.velocity.x;   if (speedx < 1.0f && speedx > -1.0f) speedx = 0;
                    float speedy = obj.velocity.y + 7;   if (speedy < 1.0f && speedy > -1.0f) speedy = 0;
                    
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
    return 0;
    

}
