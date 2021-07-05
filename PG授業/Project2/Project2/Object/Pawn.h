#pragma once
#include "Object.h"

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

struct Move;
struct ModuleNode;
struct CheckKey;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	~Pawn();

protected:
	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p

	double elapsedTime_;									// �o�ߎ��ԕێ��p
	std::string animKey_;									// �o�^�����A�j���[�V������key�ۑ��p
	Anim_State state_;										// �X�e�[�^�X�Ǘ��p

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	// --- �֐��I�u�W�F�N�g

	friend struct Move;
	friend struct ModuleNode;
	friend struct CheckKey;
};

