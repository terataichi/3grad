#include "Collision.h"
#include "../Object/Object.h"

#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::IsHitAABB(std::shared_ptr<Object> myself, std::shared_ptr<Object> target)
{
    auto& tSize = target->GetSize();
    const auto& tPos = target->GetPotision() - tSize / 2.0f;

    auto& mSize = myself->GetSize();
    const auto& mPos = myself->GetPotision() - mSize / 2.0f;

    _dbgDrawBox(mPos.x_, mPos.y_, mPos.x_ + mSize.x_, mPos.y_ + mSize.y_, 0xff, false);

    return mPos.x_ <= tPos.x_ + tSize.x_ &&
            tPos.x_ <= mPos.x_ + mSize.x_ &&
            mPos.y_ <= tPos.y_ + tSize.y_ &&
            tPos.y_ <= mPos.y_ + mSize.y_;
}

void Collision::CheckCollision(std::shared_ptr<Object> myself, std::list<std::shared_ptr<Object>> objList)
{
    for (auto& obj : objList)
    {
        if (myself != obj)
        {
            // “¯‚¶ƒ`[ƒ€‚Æ‚Í“–‚½‚ç‚È‚¢
            if (myself->GetTeamTag() != TeamTag::Non && myself->GetTeamTag() == obj->GetTeamTag())
            {
                continue;
            }
            // “–‚½‚è”»’è
            if (IsHitAABB(myself, obj))
            {
                TRACE("Hit\n");
                myself->Hit(obj);
            }
        }
    }
}
