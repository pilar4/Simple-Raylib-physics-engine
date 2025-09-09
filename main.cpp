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
        vector<Brush> brushes;


        bool fullscreen = false;
        
        /*
        t.numerator = 1;
        t.denominator = 60;
        t.timeStopped = false;
        */
        



        
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
                
                for (auto &brush : brushes) {
                    CircleBrushCollision(obj, brush, 0.8f);
                }
            }
            
            

            
            
            
            t.UPDATE();
            g.UPDATE();
            r.UPDATE();



            
            
//Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText(TextFormat("FPS: %d", fps), 20, 20, 20, SKYBLUE); 
                DrawText(TextFormat("Run time: %.2f s", runtime), 20, 40, 20, SKYBLUE);
                int fakeNumerator;
                if(t.deltaTime == 0.f) fakeNumerator = 0;
                else fakeNumerator = 1;
                DrawText(TextFormat("Delta time: %d/%d", fakeNumerator, t.denominator), 20, 60, 20, DARKBLUE);
                DrawText(TextFormat("Mouse position: %.f - %.f", mousex, mousey), 20, 80, 20, DARKBLUE);
                DrawText(TextFormat("Restitution: %.3f", r.RESTITUTION), 20, 100, 20, DARKBLUE);
                DrawText(TextFormat("GravityX: %.2f", g.GRAVITY.x/100), 20, 120, 20, DARKBLUE);
                DrawText(TextFormat("GravityX: %.2f", g.GRAVITY.y/100), 20, 140, 20, DARKBLUE);
                DrawText(TextFormat("Friction: %.f", frictionCoefficient), 20, 160, 20, DARKBLUE);
                DrawText(TextFormat("Q: reset objects, C; reset parameters, D: spawn balls,\nTime: SPACE Z X Restitution: T G, Gravity: I J K L\nO: 8ball mode"),
                BARRIERS.x - 600, 20, 20, SKYBLUE);

                
                
                for (auto& obj : circles) {
                    DrawCircleV(obj.position, obj.radius, WHITE);
                    
                    float speedx = obj.velocity.x;  
                    float speedy = obj.velocity.y;   if (obj.onGround) speedy = 0.f;
                    float speed = sqrt(speedx * speedx + speedy * speedy);
                    
                    
                    
                    DrawText(TextFormat("V:%.f", speed), obj.position.x - 25, obj.position.y - 25, 20, BLACK);
                    DrawText(TextFormat("X:%.f", speedx), obj.position.x - 25, obj.position.y - 5, 20, BLACK);
                    DrawText(TextFormat("Y:%.f", speedy), obj.position.x - 25, obj.position.y + 15, 20, BLACK);
                }
                
                for (auto &brush : brushes) {
                    brush.Draw();
                }
                
                
                
            EndDrawing();
//End of drawing ----------------------------------------------------------------------------------------------------------



            //input handling
            if(IsKeyPressed(KEY_D)){
                circles.push_back({{mousex, mousey}, {0, 0}, {0, 0}});
            }
            
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                brushes.push_back(Brush(mousex, mousey, 10, 10));
            }
            
            if (IsKeyPressed(KEY_F)){
                fullscreen = !fullscreen;
                if(fullscreen == true) ToggleFullscreen();
                else RestoreWindow();
            }  
            
            if (IsKeyDown(KEY_M)){
                circles.push_back({{mousex, mousey}, {0, 0}, {0, 0}});
            }
            
            if (IsKeyDown(KEY_O)){

                g.GRAVITY = {0, 0};

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