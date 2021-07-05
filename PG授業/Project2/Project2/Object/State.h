#pragma once
#include <string>
#include <functional>
#include <map>
#include <cassert>
#include "Player.h"
#include "../Input/InputID.h"

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

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
				myself->pos_.x_ += static_cast<float>(atof(atr->value()));
			}
			if (name == "y")
			{
				myself->pos_.y_ += static_cast<float>(atof(atr->value()));
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

private:
	// stringに対応したID
	std::map<std::string, InputID>keyMap_ = 
	{
		{"Left",InputID::Left},
		{"Right",InputID::Right}
	};
};
/// <summary>
/// ステータスチェック
/// </summary>
struct CheckState
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{

		return true;
	}
};
/// <summary>
/// アニメーションの設定
/// </summary>
struct SetAnimation
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		return true;
	}
};


struct ModuleNode
{
	/// <summary>
	/// 本体
	/// </summary>
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



	std::map<std::string, std::function<bool(Pawn* myself, rapidxml::xml_node<>* node)>> module_ =
	{
		{"Move",Move()},
		{"CheckState",CheckState()},
		{"CheckKey",CheckKey()},
		{"SetAnimation",SetAnimation()},
	};
};
