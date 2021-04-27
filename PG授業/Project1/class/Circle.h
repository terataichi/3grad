#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(Potision2 pos ,float radius);

    void Draw(void)override;
    void Draw(float radius)override;
    void Draw(Vector2 offset, float rate = 1)override;
private:
    int radius_;
};

