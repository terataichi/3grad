#pragma once
#include "Shape.h"
#include "../common/Vector2.h"

class Square :
    public Shape
{
public:
    Square(Potision2f&& pos, Size&& size, Vector2f&& speed, int&& color);
    ~Square();

    /// <summary>
    /// ’Êí•`‰æ
    /// </summary>
    void Draw();
    /// <summary>
    /// Šg‘å•\¦
    /// </summary>
    /// <param name="rate">Šg‘å—¦</param>
    void Draw(float rate);
    /// <summary>
    /// Šg‘å•\¦
    /// </summary>
    /// <param name="rate">Šg‘å—¦</param>
    /// <param name="offset">ƒIƒtƒZƒbƒg</param>
    void Draw(Vector2 offset, float rate = 1);

    bool Update(const float& delta, const ShapeVec& vec)override;
private:

    Vector2f CheckHitWall(const ShapeVec& vec)override;
    void HitShape(const SharedShape& shape) override;
};

