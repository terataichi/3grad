#pragma once
#include "Shape.h"
class Capsule :
    public Shape
{
public:
    Capsule(Potision2f&& pos, Vector2f&& speed, int&& color);

    void Draw() override;
    void Draw(float rate)override;
    bool Update(const float& delta, const ShapeVec& vec)override;
private:
    // void Reflection(Vector2f N)override;
    void HitShape(const SharedShape& shape) override;
    Vector2f CheckHitWall(const ShapeVec& vec)override;
    ShapeVec shapeVec_;
    Vector2f nowSpeed_;
    float refcnt_;
};

