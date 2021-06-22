#include <DxLib.h>

#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../common/ImageManager.h"
#include "../common/TmxAnimation.h"
#include "../common/AnimationManager.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, Size&& size, ControllType type) :Object(pos, speed, size)
{
	animation_ = std::make_unique<TmxAnimation>("Resource/AnimationData/AnimationPlayer.tmx");

	lpAnimManager.AddAnimation("Player", animation_->GetAnimData(), animation_->GetImageData());

	lpAnimManager.SetState("Player", Animation_State::Run);

	Init(type);
}

Player::~Player()
{
}

void Player::Init(ControllType type)
{
	//lpImageManager.GetImageHandle("Character/player01.png", { 24,1 }, { 32,32 });

	if (type == ControllType::GamePad)
	{
		controller_ = std::make_unique<Gamepad>();
		return;
	}
	controller_ = std::make_unique<Keyboard>();
}

bool Player::Update(const double& delta)
{
	controller_->Update();

	auto move = [&](Vector2f vel, InputID id)
	{
		if (controller_->GetPushingTrigger(id))
		{
			pos_ += vel * static_cast<float>(delta);
		}
	};
	move({ 0,speed_.y_ }, InputID::Down);
	move({ -speed_.x_,0 }, InputID::Left);
	move({ speed_.x_,0 }, InputID::Right);
	move({ 0,-speed_.y_ }, InputID::Up);


	elapsedTime_ += delta;

	return false;
}

void Player::Draw(const double& delta)
{
	auto pos = static_cast<Potision2>(pos_);
	DrawGraph(pos.x_, pos.y_, lpAnimManager.GetAnimation("Player", elapsedTime_), true);
}
