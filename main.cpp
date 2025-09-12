#include "headers/headers.h"
#include <chrono>

int main(void){

    cout<<"\n Startup test \n \n";
    auto startTime = std::chrono::high_resolution_clock::now();

    InitWindow(screenWidth, screenHeight, "Physics2D");
    SetTargetFPS(60);

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

                for (auto &brush : brushes) {
                    CircleBrushCollision(obj, brush, 0.8f);
                }
            }

            t.UPDATE();
            g.UPDATE();
            r.UPDATE();

            //Drawing -----------------------------------------------------------------------------------------------------------------
            BeginDrawing();

                BeginMode2D(cam.GetCamera());


                        ClearBackground(BLACK);
                        
                        cam.printText(fps, runtime,mousex, mousey, t, r, g,  frictionCoefficient, BARRIERS);
                        
                        


                    for(int i=0;i<=BARRIERS.x;i++){
                        for(int j=0;j>-bGirth;j--){
                            DrawPixel(i, j, RED);
                        }
                        for(int j=0;j<bGirth;j++){
                            DrawPixel(i, BARRIERS.y + j, RED);
                        }
                    }

                    for(int i=0;i<=BARRIERS.y;i++){
                        for(int j=0;j>-bGirth;j--){
                            DrawPixel(j, i, RED);
                        }
                        for(int j=0;j<bGirth;j++){
                            DrawPixel(BARRIERS.x + j, i, RED);
                        }
                    }

                    for (auto& obj : circles) {

                        DrawCircleV(obj.position, obj.radius, obj.circleColor);

                    }

                    for (auto &brush : brushes) {
                        brush.Draw();
                    }

                EndMode2D();

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

        } // koniec while (!WindowShouldClose())
    } // koniec while(running)

    CloseWindow();
    TESTSRESULTS();
    return 0;
}
