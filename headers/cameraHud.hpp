#ifndef CAMERA_HUD_HPP
#define CAMERA_HUD_HPP
#include "raylib.h"

class CameraHud {
  public:
  
    Camera2D camera; //from raylib, has target offset rotation and zoom as shown below
    Vector2 cameraStart;
    Vector2 dragStart;
    bool dragging;
    
    
    CameraHud() {
        camera.target = {0.0f, 0.0f};
        camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        cameraStart = camera.target;
        dragStart = {0.0f, 0.0f};
        dragging = false;
    }




    void Update() {
        float wheel = GetMouseWheelMove(); 
        if (wheel != 0.0f) {
                float zoomIncrement = 0.05f;
                camera.zoom += wheel * zoomIncrement;
                if (camera.zoom < 0.1f) camera.zoom = 0.1f;  //safety barriers
                if (camera.zoom > 10.0f) camera.zoom = 10.0f;
        }

        // Drag
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
            dragStart = GetMousePosition();
            cameraStart = camera.target;  
            dragging = true;
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
            dragging = false;
        }

        if (dragging) {
            Vector2 mouseDelta = { GetMouseX() - dragStart.x, GetMouseY() - dragStart.y };
            camera.target.x = cameraStart.x - mouseDelta.x / camera.zoom;
            camera.target.y = cameraStart.y - mouseDelta.y / camera.zoom;
        }
    
        setTest(TEST_CAMERA_UPDATE);
    }
    
    

    
    void printText(int fps, float runtime, float mousex, float mousey, timeController t, restitutionController r, gravityController g, float frictionCoefficient, Vector2 BARRIERS){
        
        float baseX   = camera.target.x + (20 * (1 / camera.zoom));
        float baseY   = camera.target.y + (20 * (1 / camera.zoom));
        float textFont = (1 / camera.zoom) * 20.0f;
        float lineStep = (1 / camera.zoom) * 20.0f;  // odstęp między liniami
        int line = 0;

        DrawText(TextFormat("FPS: %d", fps),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("Run time: %.2f s", runtime),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        int fakeNumerator = (t.deltaTime == 0.f) ? 0 : 1;
        DrawText(TextFormat("Delta time: %d/%d", fakeNumerator, t.denominator),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("Mouse position: %.f - %.f", mousex, mousey),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("Restitution: %.3f", r.RESTITUTION),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("GravityX: %.2f", g.GRAVITY.x / 100),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("GravityY: %.2f", g.GRAVITY.y / 100),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;

        DrawText(TextFormat("Friction: %.f", frictionCoefficient),
        baseX, baseY + line * lineStep, textFont, SKYBLUE);
        line++;
 
        //DrawText("Q: reset objects, C: reset parameters, D: spawn balls, "     Looks ugly
        //"Time: SPACE Z X Restitution: T G, Gravity: I J K L, O: 8ball mode",   maybe put it in
        //baseX, baseY + line * lineStep, textFont, SKYBLUE);                    left corner
    }


    Camera2D& GetCamera()
    {
        return camera;
    }
};


#endif
