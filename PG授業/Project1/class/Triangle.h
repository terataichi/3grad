#pragma once
#include "Shape.h"
#include <vector>


class Triangle :
    public Shape
{
public:
    Triangle(Vector2f&& point1, Vector2f&& point2, Vector2f&& point3, Vector2f&& speed, int&& color);
    ~Triangle();

    void Draw() override;
    void Draw(float rate)override;
    bool Update(const float& delta, const ShapeVec& vec)override;
private:

    Vector2f CheckHitWall(const ShapeVec& vec)override;
    void HitShape(const SharedShape& shape) override;
};

