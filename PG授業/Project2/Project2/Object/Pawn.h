#pragma once
#include "Object.h"
#include <map>
#include <list>

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

#include "../common/Vector2.h"
#include "../common/Raycast.h"

class Controller;
class TmxAnimation;
class TileMap;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	~Pawn();

protected:
	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p

	double deltaTime_;										// �P�t���[���Ԃ̎��ԕۑ�
	double elapsedTime_;									// �o�ߎ��ԕێ��p
	std::string animKey_;									// �o�^�����A�j���[�V������key�ۑ��p
	Anim_State state_;										// �X�e�[�^�X�Ǘ��p

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	std::shared_ptr<TileMap> tileMap_;						// �Q�[���V�[�����������Ă���

	Raycast raycast_;
	std::map<InputID, std::list<Sizef>> offset_;			// ���C���΂����߂̂��

	bool isGround_;											// true:�n��
	bool isJump_;											// true:�W�����v��
	// --- �֐��I�u�W�F�N�g
	friend struct Move;
	friend struct CheckKey;
	friend struct CheckState;
	friend struct SetAnimation;
	friend struct SetTurn;
	friend struct CheckCollision;
	friend struct Gravity;
	friend struct Jump;
	friend struct SetJump;
};

