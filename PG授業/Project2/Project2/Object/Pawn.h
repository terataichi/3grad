#pragma once
#include "Object.h"
#include <map>
#include <list>
#include <functional>
#include <memory>
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
	std::string name_;											// �R�}���h��
	double allTime_;											// ���̃R�}���h�S�̂ɑ΂��Ă̋��e����
	bool reset_;												// ���Z�b�g�����邩�ǂ���
	std::list<std::pair<unsigned int, double>> input_;			// CommandID��ID�ɑ΂��Ă̋��e����
};


using CommandList = std::list<CommandData>;

// using InstanceFunc = std::function<std::shared_ptr<Object>(void)>;
using InstanceMap = std::map<std::string, std::function<std::shared_ptr<Object>(void)>>;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type,TeamTag& tag);
	virtual ~Pawn();

	/// <summary>
	/// �C���X�^���X����U���̃��X�g
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::list<std::string>& GetAttackList(void);
	/// <summary>
	/// �A�^�b�N���X�g�ɑΉ������C���X�^���X�}�b�v�擾
	/// </summary>
	/// <returns></returns>
	const InstanceMap& GetInstanceFuncMap()const;

	void Damage(int&& value);
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
	/// <summary>
	/// ���������Ă�
	/// instanceMap_
	/// </summary>
	virtual void InitFunction(void) = 0;

	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	std::shared_ptr<TileMap> tileMap_;						// �Q�[���V�[�����������Ă���

	Raycast raycast_;
	std::map<InputID, std::list<Sizef>> offset_;			// ���C���΂����߂̂��

	bool isGround_;											// true:�n��
	bool isJump_;											// true:�W�����v��

	CommandList commandList_;								// �R�}���h��ۑ�

	float hp_;												// �̗�

	std::list<std::string> attackList_;						// �e�Ƃ��ł�
	InstanceMap instanceMap_;								// �A�^�b�N���X�g�ɑΉ������C���X�^���X�}�b�v

	// string�ɑΉ�����ID
	static std::map<std::string, InputID>keyMap_;
private:
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
	friend struct InstanceBulled;
};

