#pragma once
#include <string>
#include <functional>
#include <map>
#include <list>
#include <cassert>
#include "Player.h"
#include "../Input/InputID.h"
#include "../common/AnimationManager.h"
#include "../TimeManager.h"
#include "../common/Vector2.h"
#include "../common/TileMap.h"

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

namespace
{
	// s_to_Anim
	std::map<std::string, Anim_State> s_to_Anim =
	{
		{"Normal",Anim_State::Normal},
		{"Run",Anim_State::Run},
	};

	// stringに対応したID
	std::map<std::string, InputID>keyMap_ =
	{
		{"Left",InputID::Left},
		{"Right",InputID::Right},
		{"Down",InputID::Down },
		{"Up",InputID::Up}
	};

	// 当たり判定用で複数の場所で使用したかった。
	bool HitRay(Raycast::Ray ray, const CollisionPList& colList, Raycast& raycast,float& height)
	{
		for (auto& col : colList)
		{
			_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_),
				static_cast<int>(col.first.x_ + col.second.x_), static_cast<int>(col.first.y_ + col.second.y_), 0xfff, false);

			if (raycast.CheckCollision(ray, col, height))
			{
				return true;
			}
		}
		return false;
	}


}

// --- 関数オブジェクト

/// <summary>
/// 動かすだけ
/// </summary>
struct Move
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "x")
			{
				myself->pos_.x_ += static_cast<float>(atof(atr->value())) * lpTimeManager.GetDeltaTimeF();
			}
			if (name == "y")
			{
				myself->pos_.y_ += static_cast<float>(atof(atr->value())) * lpTimeManager.GetDeltaTimeF();
			}
		}
		return true;
	}
};
/// <summary>
/// キーチェックするだけ
/// </summary>
struct CheckKey
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();

			if (name == "key")
			{
				std::string value = atr->value();
				if (keyMap_.count(value))
				{
					return myself->controller_->GetPushingTrigger(keyMap_[value]);
				}
				assert(!"State.h 53行：キーが見つかりません");
			}
		}
		return false;
	}
};
/// <summary>
/// ステータスチェック
/// </summary>
struct CheckState
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "state")
			{
				std::string value = atr->value();
				if (s_to_Anim.count(value))
				{
					if (myself->state_ == s_to_Anim[value])
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};
/// <summary>
/// アニメーションの設定
/// </summary>
struct SetAnimation
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "state")
			{
				std::string value = atr->value();
				if (s_to_Anim.count(value))
				{
					myself->state_ = s_to_Anim[value];
					return true;
				}
			}
		}
		return false;
	}
};
/// <summary>
/// 画像を反転させるかどうか
/// </summary>
struct SetTurn
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "turn")
			{
				std::string trun = atr->value();
				myself->turn_ = trun == "true" ? true : false;
				return true;
			}
		}
		return false;
	}
};
/// <summary>
/// コリジョンデータとの当たり判定
/// </summary>
struct CheckCollision
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		// 必要な情報の取得
		InputID id{};
		Vector2f vec = Vector2f::ZERO;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string name = atr->name();
			if (name == "x")
			{
				vec.x_ = static_cast<float>(atof(atr->value()));
			}
			if (name == "y")
			{
				vec.y_ = static_cast<float>(atof(atr->value()));
			}
			if (name == "key")
			{
				if (!keyMap_.count(atr->value()))
				{
					return false;
				}
				id = keyMap_[atr->value()];
			}
		}
		// 当たり判定
		int count = 0;
		for (const auto& offset : myself->offset_[id])
		{
			Potision2f p1 = myself->pos_;
			if (id == InputID::Left || id == InputID::Right)
			{
				p1.y_ = p1.y_ - offset.y_ + offset.y_ * count;
			}
			else if (id == InputID::Up || id == InputID::Down)
			{
				p1.x_ = p1.x_ - offset.x_ + offset.x_ * count;
			}

			Raycast::Ray ray{ p1 ,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset};

			_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
				static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

			float height{};
			if (HitRay(ray,myself->tileMap_->GetCollitionData(),myself->raycast_, height))
			{
				return false;
			}
		}
		count++;
		return true;
	}
};
struct SetJump
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		if (myself->isGround_)
		{
			myself->isJump_ = true;
			myself->isGround_ = false;
			return true;
		}
		return false;
	}
};
/// <summary>
/// ジャンプ処理
/// </summary>
struct Jump
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		if (myself->isJump_)
		{
			Vector2f vec = Vector2f::ZERO;

			if (myself->isGround_)
			{
				myself->isJump_ = false;
				return false;
			}

			for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
			{
				std::string name = atr->name();
				if (name == "y")
				{
					vec.y_ = static_cast<float>(atof(atr->value())) * lpTimeManager.GetDeltaTimeF();
				}
			}

			// 当たり判定
			for (auto offset : myself->offset_[InputID::Up])
			{
				Raycast::Ray ray{ myself->pos_,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset };
				_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
					static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

				float height{};
				if (HitRay(ray, myself->tileMap_->GetCollitionData(), myself->raycast_, height))
				{
					myself->isJump_ = false;
					return false;
				}
			}

			myself->pos_.y_ += vec.y_;
		}
		return true;
	}

};
/// <summary>
/// 重力処理
/// </summary>
struct Gravity
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{

		// 重力操作
		float vy = displacement_ + GRAVITY * g_elapsedTime_;
		displacement_ = GRAVITY / 2.0f * (g_elapsedTime_ * g_elapsedTime_);
		Vector2f vec{ 0.0f,vy };
		// 当たり判定
		for (auto offset : myself->offset_[InputID::Down])
		{
			Raycast::Ray ray{ myself->pos_,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset };
			_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
				static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

			auto& colData = myself->tileMap_->GetCollitionData();

			float height = 0.0f;
			if (HitRay(ray,colData , myself->raycast_, height))
			{
				// 高さ合わせ
				float value = height - myself->pos_.y_ + offset.y_;
				if (value > 0.0f)
				{
					myself->pos_.y_ = height - offset.y_ - 1.0f;
				}

				displacement_ = 1.0f;
				g_elapsedTime_ = 4.0;
				myself->isGround_ = true;
				return false;
			}
		}

		myself->pos_.y_ += vy * lpTimeManager.GetDeltaTimeF();
		g_elapsedTime_ += lpTimeManager.GetDeltaTimeF() * 8.0f;
		myself->isGround_ = false;
		return true;
	}

private:
	float displacement_;										// 変化量
	float g_elapsedTime_;										// 重力の経過時間計測用
};

/// <summary>
/// 本体
/// </summary>
struct ModuleNode
{
	/// <param name="myself">自分自身</param>
	/// <param name="node">ノード</param>
	/// <returns></returns>
	bool operator()(Pawn* myself,rapidxml::xml_node<>* node)
	{
		for (auto moduleNode = node->first_node(); moduleNode != nullptr; moduleNode = moduleNode->next_sibling())
		{
			if (moduleNode->first_attribute("name") != nullptr)
			{
				std::string str = moduleNode->first_attribute("name")->value();
				if (module_.count(str))
				{
					if (!module_[str](myself, moduleNode))
					{
						continue;
					}

					// 再帰
					auto subMolude = moduleNode->first_node();
					if (subMolude != nullptr)
					{
						if (!(*this)(myself, moduleNode))
						{
							return false;
						}
					}
				}
			}
			// assert(!"state.h 98 : 対応する関数が見つかりません");
		}
		return true;
	}
private:
	std::map<std::string, std::function<bool(Pawn* myself, rapidxml::xml_node<>* node)>> module_ =
	{
		{"Move",Move()},
		{"CheckState",CheckState()},
		{"CheckKey",CheckKey()},
		{"SetAnimation",SetAnimation()},
		{"Turn",SetTurn()},
		{"CheckCollision",CheckCollision()},
		{"Gravity",Gravity()},
		{"Jump",Jump()},
		{"SetJump",SetJump()},
	};
};
