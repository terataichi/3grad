#include "RotateFireBulled.h"
#include "Pawn.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"

RotateFireBulled::RotateFireBulled(Potision2f&& pos, Vector2f&& vel, int&& damage, TeamTag tag):Bulled(pos,vel,tag)
{
	damage_ = damage;
	Init();
}

void RotateFireBulled::Init()
{
	// ステータスの設定
	animState_ = Anim_State::Normal;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationRotateFire.tmx", "RotateFire");
	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());
	size_ = lpAnimManager.GetChipSize(animKey_);
}

bool RotateFireBulled::Update()
{
	pos_ += vel_ * lpTimeManager.GetDeltaTimeF();
	return false;
}

void RotateFireBulled::Hit(std::shared_ptr<Object> target)
{
	if (target->GetObjectType() == ObjectType::Pawn)
	{
		std::dynamic_pointer_cast<Pawn>(target)->Damage(damage_);
	}
	active_ = false;
}
