#include "Object.h"
#include <DxLib.h>
#include "../common/ImageManager.h"

int Object::instanceCount_ = 1;

Object::Object(Potision2f& pos, Vector2f& speed, ObjectType&& objtype, TeamTag tag)
    :pos_(pos), vel_(speed), objType_(objtype),teamTag_(tag)
{
    radius_ = 0;
    turn_ = false;
    active_ = true;
    objID_ = instanceCount_;
    instanceCount_++;
}

Object::~Object()
{
}

const Potision2f& Object::GetPotision(void) const
{
    return pos_;
}

const Sizef& Object::GetSize(void) const
{
    return size_;
}

const ObjectType& Object::GetObjectType(void) const
{
    return objType_;
}

const int& Object::GetObjID(void) const
{
    return objID_;
}

const TeamTag Object::GetTeamTag(void) const
{
    return teamTag_;
}

const Anim_State Object::GetAnimState(void) const
{
    return animState_;
}

const bool Object::IsActive(void)
{
    return active_;
}
