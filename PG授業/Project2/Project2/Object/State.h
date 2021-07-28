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

	// �����蔻��p�ŕ����̏ꏊ�Ŏg�p�����������B
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
				if (myself->keyMap_.count(value))
				{
					return myself->controller_->GetPushingTrigger(myself->keyMap_[value]);
				}
				assert(!"State.h 53�s�F�L�[��������܂���");
			}
		}
		return false;
	}
};
/// <summary>
/// �X�e�[�^�X�`�F�b�N
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
					if (myself->animState_ == s_to_Anim[value])
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
/// �A�j���[�V�����̐ݒ�
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
					myself->animState_ = s_to_Anim[value];
					return true;
				}
			}
		}
		return false;
	}
};
/// <summary>
/// �摜�𔽓]�����邩�ǂ���
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
/// �R���W�����f�[�^�Ƃ̓����蔻��
/// </summary>
struct CheckCollision
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		// �K�v�ȏ��̎擾
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
				if (!myself->keyMap_.count(atr->value()))
				{
					return false;
				}
				id = myself->keyMap_[atr->value()];
			}
		}
		// �����蔻��
		int count = 0;
		for (const auto& offset : myself->offset_[id])
		{
			Raycast::Ray ray{ myself->pos_ ,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset};

			//_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
				//static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

			float height{};
			if (HitRay(ray,myself->tileMap_->GetCollitionData(),myself->raycast_, height))
			{
				// �������킹
				float value = height - myself->pos_.y_ + offset.y_;
				if (value > 0.0f)
				{
					myself->pos_.y_ = height - offset.y_ - 1.0f;
				}
				return false;
			}
		}
		count++;
		return true;
	}
};
/// <summary>
/// �W�����v���Z�b�g
/// </summary>
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
/// �W�����v����
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

			// �����蔻��
			for (auto offset : myself->offset_[InputID::Up])
			{
				Raycast::Ray ray{ myself->pos_,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset };
				//_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
					//static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

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
/// �d�͏���
/// </summary>
struct Gravity
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{

		// �d�͑���
		float vy = displacement_ + GRAVITY * g_elapsedTime_;
		displacement_ = GRAVITY / 2.0f * (g_elapsedTime_ * g_elapsedTime_);
		Vector2f vec{ 0.0f,vy };
		// �����蔻��
		for (auto offset : myself->offset_[InputID::Down])
		{
			Raycast::Ray ray{ myself->pos_,vec ,vec * lpTimeManager.GetDeltaTimeF() + offset };
			//_dbgDrawLine(static_cast<int>(ray.p1.x_), static_cast<int>(ray.p1.y_),
				//static_cast<int>(ray.p1.x_ + ray.v.x_), static_cast<int>(ray.p1.y_ + ray.v.y_), 0xff0000);

			auto& colData = myself->tileMap_->GetCollitionData();

			float height = 0.0f;
			if (HitRay(ray,colData , myself->raycast_, height))
			{
				// �������킹
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
	float displacement_;										// �ω���
	float g_elapsedTime_;										// �d�͂̌o�ߎ��Ԍv���p
};
/// <summary>
/// �R�}���h�����͂���Ă��邩�`�F�b�N���Đ������Ă�����Z���X�g�ɂԂ�����
/// </summary>
struct CheckCommand
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		auto ringBuf = myself->controller_->GetRingBuf();
		auto nowBuf = myself->controller_->GetStartBuf();
		auto backupBuf = nowBuf;

		for (auto& cmdData : myself->commandList_)
		{
			int cnt = 0;
			nowBuf = backupBuf;
			bool catchCom = false;														// 1�ڂ̃R�}���h�����m������true
			double allTime = nowBuf->time_;
			for (auto& cmd : cmdData.input_)
			{
				auto checkBuf = nowBuf;													// �����ʒu�ۑ�
				while (nowBuf != ringBuf)
				{
					// ���E���]
					auto command = cmd.first;
					if (command & (1 << static_cast<unsigned int>(InputID::Right)) && myself->turn_)
					{
						command ^= (1 << static_cast<unsigned int>(InputID::Left)) | (1 << static_cast<unsigned int>(InputID::Right));
					}

					if (command == nowBuf->id_)
					{
						// ���͎��ԃ`�F�b�N
						auto time = lpTimeManager.GetElapsedTime() - nowBuf->time_;
						if (time >= cmd.second)
						{
							break;
						}
						if (!catchCom)
						{
							if (nowBuf->prev_->id_ != 0)
							{
								break;
							}
						}

						catchCom = true;
						nowBuf = nowBuf->next_;
						continue;
					}
					// 1�ڂ̃R�}���h��������܂ł͉�
					if (catchCom)
					{
						// neutral�����e���邩���Ȃ���
						if (nowBuf->id_ != 0)
						{
							break;
						}
					}
					nowBuf = nowBuf->next_;
				}

				// �ʒu���ς���Ă��Ȃ�
				if (!catchCom || checkBuf == nowBuf)
				{
					// �R�}���h���f
					break;
				}
				// �R�}���h�������Ă�ꍇ
				cnt++;
			}
			// �R�}���h����
			// cnt��size�Ɠ����Ő���
			if (cnt == cmdData.input_.size())
			{
				// �̑O�ɑS�̂̎��ԃ`�F�b�N���Ē������邩�m�F
				if(nowBuf->time_ - allTime > cmdData.allTime_)
				{
					TRACE("���͎��Ԃ��������܂�\n");
					break;
				}
				myself->controller_->ResetBuffer(cmdData.reset_);
				TRACE(cmdData.name_.c_str());
				TRACE("\n");
				
				// �A�^�b�N���X�g�ɒǉ�
				myself->attackList_.emplace_back(cmdData.name_.c_str());
				return true;
			}
		}
		return false;
	}
};
/// <summary>
/// �e����
/// </summary>
struct InstanceBulled
{
	bool operator()(Pawn* myself, rapidxml::xml_node<>* node)
	{
		return false;
	}
};

/// <summary>
/// �{��
/// </summary>
struct ModuleNode
{
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
		{"CheckCommand",CheckCommand()},
		{"InstanceBulled",InstanceBulled()}
	};
};
