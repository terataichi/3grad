#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(Potision2 pos ,int radius);

    void Draw(void)override;

    void Draw(float radius);
private:
    int radius_;
};

