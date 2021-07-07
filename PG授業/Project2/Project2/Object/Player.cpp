#include <DxLib.h>

#include "Player.h"
#include "../common/ImageManager.h"
#include "../common/AnimationManager.h"
#include "../common/TileMap.h"
#include "../_debug/_DebugDispOut.h"
#include "../TimeManager.h"
#include "../Status/Animation_State.h"

Player::Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap, ControllType type) :Pawn(pos, speed,type)
{
	tileMap_ = tileMap;

	Init();
}

Player::~Player()
{
}

void Player::Init()
{
	// ステータスの設定
	state_ = Anim_State::Normal;
	elapsedTime_ = 0;
	// アニメーション登録初期化
	animKey_ = lpAnimManager.AddAnimation("Resource/AnimationData/AnimationPlayer.tmx", "Player");
	lpAnimManager.SetState(animKey_, state_,elapsedTime_);


	Sizef animSize = lpAnimManager.GetChipSize(animKey_) / 2.0f;
	offset_.try_emplace(InputID::Left, std::list<Sizef>{ Sizef{ -animSize.x_,0 }, Sizef{ -animSize }, Sizef{ -animSize.x_,animSize.y_ } });
	offset_.try_emplace(InputID::Down, std::list<Sizef>{ Sizef{ 0,animSize.y_ }, Sizef{  animSize }, Sizef{ -animSize.x_,animSize.y_ } });
	offset_.try_emplace(InputID::Right, std::list<Sizef>{ Sizef{ animSize }, Sizef{ animSize.x_,0 }, Sizef{ animSize.x_,-animSize.y_ } });
	offset_.try_emplace(InputID::Up, std::list<Sizef>{ Sizef{ -animSize }, Sizef{ 0,-animSize.y_ }, Sizef{ animSize.x_,-animSize.y_ } });


	jump_ = false;


	rapidxml::file<> moduleFileName = "Resource/State/PlayerState.tmx";
	stateVec_ = moduleFileName.vecData();

	stateDoc.parse<0>(stateVec_.data());

	stateNode_ = stateDoc.first_node("moduleList");

}

bool Player::Update()
{
	controller_->Update();

	// first_nodeに何も書かなければ最初に見つけたやつが入る
	state_ = Anim_State::Normal;
	for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
	{
		moduleNode(this, node);
	}

	//auto checkMove = [&](Vector2f&& moveVec) 
	//{
	//	Raycast::Ray ray{ pos_,pos_ + moveVec ,moveVec };
	//	_dbgDrawLine(ray.p1.x_, ray.p1.y_, ray.p1.x_ + ray.v.x_, ray.p1.y_ + ray.v.y_,0xff0000);

	//	for (auto& col: tileMap_->GetCollitionData())
	//	{
	//		_dbgDrawBox(col.first.x_, col.first.y_, col.first.x_ + col.second.x_, col.first.y_ + col.second.y_, 0xfff, false);
	//		if (raycast_.CheckCollision(ray, col))
	//		{
	//			return false;
	//		}
	//	}
	//	return true;
	//};

	//Vector2f velValue = Vector2f::ZERO;
	//Sizef offsetSize = Sizef::ZERO;

	//// 入力に対しての動き
	//auto move = [&](Vector2f&& vel, InputID id, std::list<Sizef> offset,bool lock = false)
	//{
	//	if (lock || controller_->GetPushingTrigger(id))
	//	{
	//		// 反転
	//		if (id == InputID::Left)
	//		{
	//			turn_ = true;
	//			state_ = Animation_State::Run;
	//		}
	//		else if (id == InputID::Right)
	//		{
	//			turn_ = false;
	//			state_ = Animation_State::Run;
	//		}

	//		bool check = true;
	//		for (auto& size : offset)
	//		{
	//			check &= checkMove(vel * static_cast<float>(delta) + size);
	//		}
	//		if (check)
	//		{
	//			velValue += vel * static_cast<float>(delta);
	//			return true;
	//		}
	//	}
	//	return false;
	//};

	//// 重力操作
	//float v = displacement_ + GRAVITY * static_cast<float>(g_elapsedTime_);
	//displacement_ = static_cast<float>(GRAVITY / 2.0 * (g_elapsedTime_ * g_elapsedTime_));
	//if (!move({ 0,v }, InputID::Down, offset_[InputID::Down], true))
	//{
	//	displacement_ = 1.0f;
	//	g_elapsedTime_ = 4.0;
	//	jump_ = false;
	//	if (!jump_ && controller_->GetPushingTrigger(InputID::Up))
	//	{
	//		jump_ = true;
	//	}
	//}

	//if (jump_)
	//{
	//	if (!move({ 0,-500 }, InputID::Up, offset_[InputID::Up], true))
	//	{
	//		displacement_ = 1.0f;
	//		g_elapsedTime_ = 4.0;
	//		jump_ = false;
	//	}
	//}
	//move({ -speed_.x_,0 }, InputID::Left, offset_[InputID::Left]);
	//move({ speed_.x_,0 }, InputID::Right, offset_[InputID::Right]);


	//if (velValue != Vector2f::ZERO)
	//{
	//	pos_ += velValue;
	//}

	elapsedTime_ += lpTimeManager.GetDeltaTime();
	return false;
}

void Player::Draw()
{
	auto pos = static_cast<Potision2>(pos_);

	lpAnimManager.SetState(animKey_, state_, lpTimeManager.GetElapsedTime());
	DrawRotaGraph(pos.x_, pos.y_, 1, 0.0, lpAnimManager.GetAnimation(animKey_, lpTimeManager.GetElapsedTime()), true, turn_);
}
