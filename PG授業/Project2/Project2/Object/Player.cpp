#include <DxLib.h>

#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, Size&& size, ControllType type) :Object(pos, speed, size)
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
	auto move = [&](Vector2f vel, InputID id)
	{
		if (controller_->GetPushingTrigger(id))
		{
			pos_ += vel * static_cast<float>(delta);
			state_ = Animation_State::Run;
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

	lpAnimManager.SetState(animKey_, state_, elapsedTime_);
	DrawGraph(pos.x_, pos.y_, lpAnimManager.GetAnimation(animKey_, elapsedTime_), true);
}
