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

/// <summary>
/// ID�ɑΉ�����trigger�����i�[����
/// first : �����t���[���̏��
/// Second : �P�t���[���O�̏��
/// </summary>
using TriggerMap = std::map<InputID, std::pair<bool, bool>>;


class Controller
{
public:
	// �o�������X�g
	struct RingBuffer
	{
		int id_;
		RingBuffer* next_;			// ���̗v�f
		RingBuffer* prev_;			// �O�̗v�f
	};

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
	/// �����O�o�b�t�@�[�X�V����
	/// </summary>
	void UpdateRingBuf(void);
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
	RingBuffer* ringBuf_;														// ���͏����ێ��悤�o�������X�g
};

