#pragma once
#include <string>
#include <functional>
#include <map>
#include <cassert>
#include "Player.h"
#include "../Input/InputID.h"

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

// --- �֐��I�u�W�F�N�g

/// <summary>
/// ����������
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
/// �L�[�`�F�b�N���邾��
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
				assert(!"State.h 53�s�F�L�[��������܂���");
			}
		}
		return false;
	}

private:
	// string�ɑΉ�����ID
	std::map<std::string, InputID>keyMap_ = 
	{
		{"Left",InputID::Left},
		{"Right",InputID::Right}
	};
};
/// <summary>
/// �X�e�[�^�X�`�F�b�N
/// </summary>
struct CheckState
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{

		return true;
	}
};
/// <summary>
/// �A�j���[�V�����̐ݒ�
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
	/// �{��
	/// </summary>
	/// <param name="myself">�������g</param>
	/// <param name="node">�m�[�h</param>
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

					// �ċA
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
			// assert(!"state.h 98 : �Ή�����֐���������܂���");
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
