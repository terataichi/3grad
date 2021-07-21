#include "Object.h"
#include <DxLib.h>
#include "../common/ImageManager.h"

Object::Object(Potision2f& pos, Vector2f& speed, ObjectType&& objtype) :pos_(pos), vel_(speed), objType_(objtype)
{
    size_ = Vector2::ZERO;
    radius_ = 0;
    turn_ = false;
}

Object::~Object()
{
}

const ObjectType& Object::GetObjectType(void) const
{
    return objType_;
}
