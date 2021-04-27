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
    /// 通常描画
    /// </summary>
    void Draw();
    /// <summary>
    /// 拡大表示
    /// </summary>
    /// <param name="rate">拡大率</param>
    void Draw(float rate);
    /// <summary>
    /// 拡大表示
    /// </summary>
    /// <param name="rate">拡大率</param>
    /// <param name="offset">オフセット</param>
    void Draw(Vector2 offset, float rate = 1);
private:
};

