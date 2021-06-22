#include "Object.h"
#include <DxLib.h>
#include "../common/ImageManager.h"

Object::Object()
{
}

Object::Object(Potision2f& pos, Vector2f& speed, Size& size) :pos_(pos), speed_(speed), size_(size)
{
    radius_ = 0;
    elapsedTime_ = 0.0;
}

Object::~Object()
{
}