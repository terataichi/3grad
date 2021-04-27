#pragma once
#include "Shape.h"
#include "../common/Vector2.h"

class Square :
    public Shape
{
public:
    Square(Potision2 pos, Size size);
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
private:
};

