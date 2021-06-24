#include <DxLib.h>

#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, ControllType type) :Object(pos, speed)
{
	Init(type);
}

Player::~Player()
{
}

void Player::Init(ControllType type)
{
	// ステータスの設定
	state_ = Animation_State::Normal;
	elapsedTime_ = 0;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationPlayer.tmx", "Player");
	lpAnimManager.SetState(animKey_, state_,elapsedTime_);

	// コントローラーの設定
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
	state_ = Animation_State::Normal;
	Vector2f velValue = { 0.0f,0.0f };
	auto move = [&](Vector2f&& vel, InputID id)
	{
		if (controller_->GetPushingTrigger(id))
		{
			if (id == InputID::Left)
			{
				turn_ = true;
			}
			else if (id == InputID::Right)
			{
				turn_ = false;
			}

			velValue += vel * static_cast<float>(delta);
		}
	};
	move({ 0,speed_.y_ }, InputID::Down);
	move({ -speed_.x_,0 }, InputID::Left);
	move({ speed_.x_,0 }, InputID::Right);
	move({ 0,-speed_.y_ }, InputID::Up);

	if (velValue != Vector2f::ZERO)
	{
		pos_ += velValue;
		state_ = Animation_State::Run;
	}


	elapsedTime_ += delta;

	return false;
}

void Player::Draw(const double& delta)
{
	auto pos = static_cast<Potision2>(pos_);

	lpAnimManager.SetState(animKey_, state_, elapsedTime_);
	DrawRotaGraph(pos.x_, pos.y_, 1.7, 0.0, lpAnimManager.GetAnimation(animKey_, elapsedTime_), true, turn_);
}
