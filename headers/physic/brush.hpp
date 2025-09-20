#ifndef BRUSH_H
#define BRUSH_H

class Brush {
  public:
    Rectangle rect;
    Color color = GRAY;

    Brush(float x, float y, float w, float h) {
        rect = {x, y, w, h};
    }

    void Draw() {
        DrawRectangleRec(rect, color);
        setTest(TEST_BRUSH_DRAW);
    }
};


#endif