#pragma once
#include <array>
#include <map>
#include <vector>
#include "InputID.h"

/// <summary>
/// ���͑��u�̎�ޒ�`
/// </summary>
enum class ControllType
{
	Keybord,
	GamePad,
	Max
};

//enum class Command_ID
//{
//	neutral,
//	left,
//	right,
//	up,
//	down,
//	LowerRight,
//	LowerLeft,
//	UpperRight,
//	UpperLeft,
//	Button1,
//	Button2,
//	Button3,
//	Button4,
//};

/// <summary>
/// ID�ɑΉ�����trigger�����i�[����
/// first : �����t���[���̏��
/// Second : �P�t���[���O�̏��
/// </summary>
using TriggerMap = std::map<InputID, std::pair<bool, bool>>;

class Controller
{
public:
	Controller();
	virtual ~Controller();

	/// <summary>
	/// ���݈����Ă���͑��u�̎�ނ�Ԃ�
	/// </summary>
	/// <returns>���͑��u�̎��</returns>
	virtual ControllType GetControllType() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update(void) = 0;

	/// <summary>
	/// �����ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="id">�擾������ID</param>
	const bool GetPushTrigger(InputID id)const;
	/// <summary>
	/// �����ꑱ���Ă��邩�ǂ���
	/// </summary>
	/// <param name="id">�擾������ID</param>
	const bool GetPushingTrigger(InputID id)const;
	/// <summary>
	/// �����ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="id">�擾������ID</param>
	const bool GetReleaseTrigger(InputID id)const;
	/// <summary>
	/// �����ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="id">�擾������ID</param>
	const bool GetReleasingTrigger(InputID id)const;
private:

protected:

	TriggerMap triggerMap_;

	std::map<InputID, int> config_;												// ID�ɑΉ������R���t�B�O�i�[

	std::vector<std::pair<int,double>> commandBuf_;								// ���͂��ꂽ�R�}���h�Ƌ��e���Ԃ�ۑ�����
	int commandCnt_ = 0;
};

