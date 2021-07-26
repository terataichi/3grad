#include "FireBulled.h"
#include "Pawn.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"

FireBulled::FireBulled(Potision2f&& pos, Vector2f&& vel,int&& damage, TeamTag tag):Bulled(pos,vel,tag)
{
	damage_ = damage;
	Init();
}

void FireBulled::Init()
{
	// ステータスの設定
	animState_ = Anim_State::Normal;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationFire.tmx", "Fire");
	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());
	size_ = lpAnimManager.GetChipSize(animKey_);

	turn_ = vel_.x_ < 0;
}

bool FireBulled::Update()
{
	pos_ += vel_ * lpTimeManager.GetDeltaTimeF();

	if (animState_ == Anim_State::Normal)
	{
		if (lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()) == -1)
		{
			animState_ = Anim_State::Run;
		}
	}
	return true;
}

void FireBulled::Hit(std::shared_ptr<Object> target)
{
	if (target->GetObjectType() == ObjectType::Pawn)
	{
		std::dynamic_pointer_cast<Pawn>(target)->Damage(damage_);
	}
	active_ = false;
}
