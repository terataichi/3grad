#pragma once
#include <array>
#include <map>
#include <vector>
#include "InputID.h"

#define CREATE_RINGBUF_NUM 60

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
		unsigned int id_;			// ���͂������i�[
		double time_;				// ���͂����Ƃ��̎��Ԃ�ێ����Ă���
		int num_;					// �f�o�b�O�p�����̔ԍ�
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
	/// <summary>
	/// ���͏������߂��o�b�t�@�[�擾
	/// </summary>
	const RingBuffer* GetRingBuf(void)const;
	const RingBuffer* GetStartBuf(void)const;
	/// <summary>
	/// �o�b�t�@�[�̃��Z�b�g
	/// </summary>
	/// <param name="reset">���Z�b�g���邩���Ȃ���</param>
	void ResetBuffer(bool reset);
private:

protected:
	/// <summary>
	/// �����O�o�b�t�@�[�X�V����
	/// </summary>
	void UpdateRingBuf(void);


	TriggerMap triggerMap_;

	std::map<InputID, int> config_;												// ID�ɑΉ������R���t�B�O�i�[

	RingBuffer* ringBuf_ = nullptr;												// ���͏����ێ��悤�o�������X�g
	RingBuffer* startBuf_ = nullptr;											// ���͊J�n�ʒu
};

