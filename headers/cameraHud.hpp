#ifndef CAMERA_HUD_HPP
#define CAMERA_HUD_HPP
#include "raylib.h"

class CameraHud {
  public:
  
    Camera2D camera;
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
            float zoomIncrement = 0.1f;
            camera.zoom += wheel * zoomIncrement;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
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


    }


    Camera2D& GetCamera()
    {
        return camera;
    }
};


#endif
