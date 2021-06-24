#include "Object.h"
#include <DxLib.h>
#include "../common/ImageManager.h"

Object::Object(Potision2f& pos, Vector2f& speed) :pos_(pos), speed_(speed)
{
    size_ = Vector2::ZERO;
    radius_ = 0;
    elapsedTime_ = 0.0;
    turn_ = false;
    state_ = Animation_State::Normal;
}

Object::~Object()
{
}