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
    /// �ʏ�`��
    /// </summary>
    void Draw();
    /// <summary>
    /// �g��\��
    /// </summary>
    /// <param name="rate">�g�嗦</param>
    void Draw(float rate);
    /// <summary>
    /// �g��\��
    /// </summary>
    /// <param name="rate">�g�嗦</param>
    /// <param name="offset">�I�t�Z�b�g</param>
    void Draw(Vector2 offset, float rate = 1);

    bool Update(const float& delta, const ShapeVec& vec)override;
private:

    Vector2f CheckHitWall(const ShapeVec& vec)override;
    void HitShape(const SharedShape& shape) override;
};

