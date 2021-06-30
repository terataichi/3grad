#include <DxLib.h>

#include "Player.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"
#include "../common/TileMap.h"
#include "../_debug/_DebugDispOut.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap, ControllType type) :Object(pos, speed)
{
	tileMap_ = tileMap;
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

	auto checkMove = [&](Vector2f&& moveVec) 
	{
		Raycast::Ray ray{ pos_,pos_ + moveVec ,moveVec };
		_dbgDrawLine(ray.p1.x_, ray.p1.y_, ray.p1.x_ + ray.v.x_, ray.p1.y_ + ray.v.y_,0xfff);

		for (auto& col: tileMap_->GetCollitionData())
		{
			_dbgDrawBox(col.first.x_, col.first.y_, col.first.x_ + col.second.x_, col.first.y_ + col.second.y_, 0xfff, false);
			if (raycast_.CheckCollision(ray, col))
			{
				return false;
			}
		}
		return true;
	};

	state_ = Animation_State::Normal;
	Vector2f velValue = Vector2f::ZERO;
	Sizef offsetSize = Sizef::ZERO;

	auto move = [&](Vector2f&& vel, InputID id, Sizef offset)
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
			if (checkMove(vel * static_cast<float>(delta) + offset))
			{
				// 当たり判定用のoffset取得
				velValue += vel * static_cast<float>(delta);
			}
		}
	};
	Sizef animSize = lpAnimManager.GetChipSize(animKey_);
	move({ 0,speed_.y_ }, InputID::Down, Sizef{ 0,animSize.y_ / 2.0f});
	move({ -speed_.x_,0 }, InputID::Left, Sizef{ -animSize.x_ / 2.0f,0 });
	move({ speed_.x_,0 }, InputID::Right, Sizef{ animSize.x_ / 2.0f,0 });
	move({ 0,-speed_.y_ }, InputID::Up, Sizef{ 0,-animSize.y_ / 2.0f });


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
	DrawRotaGraph(pos.x_, pos.y_, 1, 0.0, lpAnimManager.GetAnimation(animKey_, elapsedTime_), true, turn_);
}

Sizef Player::GetOffSet(Vector2f vel)
{
	Sizef size;
	Sizef animSize = lpAnimManager.GetChipSize(animKey_);
	if (vel.x_ > 0)
	{
		size.x_ += animSize.x_ / 2;
	}
	else
	{
		size.x_ -= animSize.x_ / 2;
	}

	return size;
}
