#include "Raycast.h"

bool Raycast::CheckCollision(Ray ray, std::pair<Potision2f, Sizef> col, float& height)
{

    Line lineList[4] = {
        { {col.first.x_,col.first.y_ + col.second.y_},col.first },
        { col.first,{col.first.x_ + col.second.x_,col.first.y_} },
        { col.first + col.second,{col.first.x_,col.first.y_ + col.second.y_} },
        { {col.first.x_ + col.second.x_,col.first.y_},col.first + col.second }
    };

    for (auto line : lineList)
    {
        if (CheckRay(ray, line))
        {
            if (line.p1.y_ == line.p2.y_)
            {
                height = line.p1.y_;
            }
            return true;
        }
    }

    return false;
}

bool Raycast::CheckRay(Ray ray, Line line)
{
    auto v = line.p1 - ray.p1;

    // ïΩçsÇ©Ç«Ç§Ç©
    float cross1 = Cross(ray.v, line.vec());
    if (cross1 == 0.0f)
    {
        return false;
    }

    float cross2 = Cross(v, ray.v);
    float cross3 = Cross(v, line.vec());

    float t1 = cross3 / cross1;
    float t2 = cross2 / cross1;

    const float eps = 0.00001f;

    if (t1 + eps < 0.0f || t1 - eps > 1.0f || t2 + eps < 0.0f || t2 - eps > 1.0f)
    {
        return false;
    }


    return true;
}
