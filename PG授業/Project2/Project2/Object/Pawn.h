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

// �R�}���h�̏��
struct CommandData 
{
	std::string name_;
	std::list<int> input_;
};

using CommandList = std::list<CommandData>;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	virtual ~Pawn();

protected:
	/// <summary>
	/// �R�}���h�̃o�b�t�@�[�ɂ��߂鏈��
	/// </summary>
	void CommandBufUpdate(void);
	/// <summary>
	/// �X�e�[�^�XUpdate�p��Tmx�ǂݍ���
	/// </summary>
	void LoadStateModule(std::string&& fileName);
	/// <summary>
	/// �R�}���h��ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C���܂ł̃p�X</param>
	/// <returns>�ǂݍ��񂾃R�}���h���X�g</returns>
	void LoadCommandList(std::string&& fileName);

	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p
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

	CommandList commandList_;								// �R�}���h��ۑ�

	// string�ɑΉ�����ID
	static std::map<std::string, InputID>keyMap_;

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
	friend struct CheckCommand;
};

