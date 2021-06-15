#pragma once
#include "Shape.h"
#include "../common/Vector2.h"

class Circle :
    public Shape
{
public:
    Circle(Potision2f&& pos ,float&& radius, Vector2f&& speed, int&& color);

    void Draw(void)override;
    void Draw(float rate)override;
    bool Update(const float& delta, const ShapeVec& vec)override;
private:
    Vector2f CheckHitWall(const ShapeVec& vec)override;
    void HitShape(const SharedShape& shape) override;

};

