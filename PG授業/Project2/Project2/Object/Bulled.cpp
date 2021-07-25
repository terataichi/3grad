#include "Bulled.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"
#include "Pawn.h"

#include<DxLib.h>

Bulled::Bulled(Potision2f&& pos, Vector2f&& vel, TeamTag tag) :Object(pos, vel,ObjectType::Actor,tag)
{
	Init();
}

Bulled::~Bulled()
{
}

void Bulled::Init()
{
	// ステータスの設定
	animState_ = Anim_State::Normal;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationFire.tmx", "Fire");
	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());

	size_ = lpAnimManager.GetChipSize(animKey_);

}

bool Bulled::Update()
{
	pos_.x_ += vel_.x_ * lpTimeManager.GetDeltaTimeF();

	if (animState_ == Anim_State::Normal)
	{
		if (lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()) == -1)
		{
			animState_ = Anim_State::Run;
		}
	}
	return true;
}

void Bulled::Draw()
{
	auto pos = static_cast<Potision2>(pos_);

	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());
	DrawRotaGraph(pos.x_, pos.y_, 1, 0.0, lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()), true, turn_);
}

void Bulled::Hit(std::shared_ptr<Object> target)
{
	if (target->GetObjectType() == ObjectType::Pawn)
	{
		std::dynamic_pointer_cast<Pawn>(target)->Damage(1);
	}
	active_ = false;
}
