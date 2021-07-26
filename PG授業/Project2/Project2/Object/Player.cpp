#include <DxLib.h>

#include "Player.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"
#include "../common/TileMap.h"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "../TimeManager.h"
#include "../Status/Animation_State.h"
#include "FireBulled.h"
#include "RotateFireBulled.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap, ControllType type, TeamTag tag)
	:Pawn(pos, speed, type,tag)
{
	tileMap_ = tileMap;

	Init();
	InitFunction();
}

Player::~Player()
{
}

void Player::Init()
{
	hp_ = 1;

	// ステータスの設定
	animState_ = Anim_State::Normal;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationPlayer.tmx", "Player");
	lpAnimManager.SetState(animKey_, animState_,lpTimeManager.GetElapsedTime());

	size_ = lpAnimManager.GetChipSize(animKey_);
	Sizef animSize = lpAnimManager.GetChipSize(animKey_) / 2.0f;
	offset_.try_emplace(InputID::Left, std::list<Sizef>{ Sizef{ -animSize.x_,0 }, Sizef{ -animSize }, Sizef{ -animSize.x_,animSize.y_ } });
	offset_.try_emplace(InputID::Down, std::list<Sizef>{ Sizef{ 0,animSize.y_ }, Sizef{  animSize }, Sizef{ -animSize.x_,animSize.y_ } });
	offset_.try_emplace(InputID::Right, std::list<Sizef>{ Sizef{ animSize }, Sizef{ animSize.x_,0 }, Sizef{ animSize.x_,-animSize.y_ } });
	offset_.try_emplace(InputID::Up, std::list<Sizef>{ Sizef{ -animSize }, Sizef{ 0,-animSize.y_ }, Sizef{ animSize.x_,-animSize.y_ } });

	LoadStateModule("Resource/State/PlayerState.tmx");

	LoadCommandList("Resource/Command/PlayerCommand.tmx");
}

bool Player::Update()
{
	controller_->Update();
	CommandBufUpdate();

	if (animState_ == Anim_State::Dmage || animState_ == Anim_State::Death)
	{
		if (lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()) == -1)
		{
			animState_ = Anim_State::Normal;
		}
	}
	else
	{
		animState_ = Anim_State::Normal;
	}

	// first_nodeに何も書かなければ最初に見つけたやつが入る
	//animState_ = Anim_State::Normal;
	for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
	{
		moduleNode(this, node);
	}
	return false;
}

void Player::Draw()
{
	auto pos = static_cast<Potision2>(pos_);

	lpAnimManager.SetState(animKey_, animState_, lpTimeManager.GetElapsedTime());
	DrawRotaGraph(pos.x_, pos.y_, 1, 0.0, lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()), true, turn_);
}

void Player::InitFunction(void)
{
	auto at1 = [&](void)->std::shared_ptr<Object> {

		Vector2f vel{ 500,0 };
		if (turn_)
		{
			vel.x_ *= -1;
		}
		std::shared_ptr<Object> obj;
		obj.reset(new FireBulled(std::move(pos_), std::move(vel), 1, teamTag_));
		TRACE("bulled生成\n");
		return obj;
	};
	auto at2 = [&](void)->std::shared_ptr<Object> {

		Vector2f vel{ 500,200 };
		if (turn_)
		{
			vel.x_ *= -1;
		}
		std::shared_ptr<Object> obj;
		obj.reset(new FireBulled(std::move(pos_), std::move(vel), 2,teamTag_));
		TRACE("bulled生成\n");
		return obj;
	};
	auto at3 = [&](void)->std::shared_ptr<Object> {

		Vector2f vel{ 500,200 };
		if (turn_)
		{
			vel.x_ *= -1;
		}
		std::shared_ptr<Object> obj;
		obj.reset(new FireBulled(std::move(pos_), std::move(vel), 2, teamTag_));
		TRACE("bulled生成\n");
		return obj;
	};
	auto at4 = [&](void)->std::shared_ptr<Object> {

		Vector2f vel{ 600,0 };
		if (turn_)
		{
			vel.x_ *= -1;
		}
		std::shared_ptr<Object> obj;
		obj.reset(new RotateFireBulled(std::move(pos_), std::move(vel), 2, teamTag_));
		TRACE("bulled生成\n");
		return obj;
	};

	instanceMap_ = { 
		{ "at1", at1 },
		{ "at2", at2 },
		{ "at3", at3 },
		{ "at4", at4 }
	};
}

void Player::Hit(std::shared_ptr<Object> target)
{
	// 同じオブジェクトタイプ同士なら当たらない
	if (target->GetObjectType() == ObjectType::Pawn)
	{
		return;
	}
}
