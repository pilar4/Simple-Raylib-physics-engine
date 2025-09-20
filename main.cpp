#include "headers/headers.h"
#include <chrono>

int main(void){
    CameraHud cam;
    cout<<"\n Startup test \n \n";
    auto startTime = std::chrono::high_resolution_clock::now();

    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);
    
    
    ObjectsSystem PBD;
    

    bool running = true;
    while(running){

        vector<objectCircle> circles;
        vector<Brush> brushes;


        bool fullscreen = false;
        

        while (!WindowShouldClose())
        {

            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = currentTime - startTime;
            float runtime = elapsed.count();

            int fps = GetFPS();
            cam.Update();
            Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), cam.GetCamera());
            float mousex = worldPos.x;
            float mousey = worldPos.y;
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
            
            for (int i = 0; i < 8; i++) { // 8 iterations of collision
                for (auto &a : circles) {
                    for (auto &b : circles) {
                        if (&a != &b) CIRCLECOLLISION(a, b, r.RESTITUTION);
                    }
                    for (auto &brush : brushes) {
                        CircleBrushCollision(a, brush, r.RESTITUTION);
                    }
                }
                for (auto &brush : brushes) {
                    
                        for (auto &PBDp : PBD.particles){
                            BallBrushCollision(PBDp, brush, r.RESTITUTION);
                        }
                    }
                
            }
            for(auto &circle : circles){
    for(auto &pbdBall : PBD.particles){
        PBD_EULER_COLLISION(pbdBall, circle, r.RESTITUTION);
    }
}

               
            
            if (IsKeyPressed(KEY_S)) {
            
                PBD.AddParticle(mouseVec);
            }
            PBD.UPDATE(t.deltaTime, mouseVec);
            //for whatever reason when you make delta time smaller PBD stops to clip somewhere around 1/200
            
            
            //eraser declaration
            bool erasing = false;
            float eraserRadius = 30.f;
            if(IsKeyDown(KEY_E)){
                erasing = true;
                
            } else {
                erasing = false;
            }
            
            

            t.UPDATE();
            g.UPDATE();
            r.UPDATE();

            //Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();

                BeginMode2D(cam.GetCamera());


                        ClearBackground(BLACK);
                        
                        cam.printText(fps, runtime,mousex, mousey, t, r, g,  frictionCoefficient, BARRIERS);
                        
                    PBD.Draw();


                    for(int i=0;i<=BARRIERS.x;i++){
                        for(int j=0;j>-bGirth;j--){
                            DrawPixel(i, j, RED);
                        }
                        for(int j=0;j<bGirth;j++){
                            DrawPixel(i, BARRIERS.y + j-1, RED);
                        }
                    }

                    for(int i=0;i<=BARRIERS.y;i++){
                        for(int j=0;j>-bGirth;j--){
                            DrawPixel(j, i, RED);
                        }
                        for(int j=0;j<bGirth;j++){
                            DrawPixel(BARRIERS.x + j-1, i, RED);
                        }
                    }

                    for (auto& obj : circles) {

                        DrawCircleV(obj.position, obj.radius, obj.circleColor);

                    }

                    for (auto &brush : brushes) {
                        brush.Draw();
                    }
                    
                    if(erasing){
                        DrawCircle(mousex, mousey, eraserRadius, GRAY);
                    }

                EndMode2D();

            EndDrawing();
            //End of drawing ----------------------------------------------------------------------------------------------------------
            //Eraser
            
            
            
            if(erasing){
                
                
                for (auto it = circles.begin(); it != circles.end(); ) {
                    if (it->position.x + it->radius > mousex - eraserRadius && it->position.x - it->radius < mousex + eraserRadius&&
                    it->position.y + it->radius > mousey - eraserRadius && it->position.y - it->radius < mousey + eraserRadius &&
                    erasing) {
        
                        it = circles.erase(it);
                } else {
                    ++it;
                }
            }
            
                for (auto it = brushes.begin(); it != brushes.end(); ) {
                    if (mousex + eraserRadius >= it->rect.x &&
                    mousex - eraserRadius <= it->rect.x + it->rect.width &&
                    mousey + eraserRadius >= it->rect.y &&
                    mousey - eraserRadius <= it->rect.y + it->rect.height &&
                    erasing) {
    
                        it = brushes.erase(it);
                    } else {
                        ++it;
                    }

                }
                
                setTest(TEST_ERASER);
            }





            



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
                PBD.RESETBALLS();
                break;
            }

        } // koniec while (!WindowShouldClose())
    } // koniec while(running)

    CloseWindow();
    TESTSRESULTS();
    return 0;
}
