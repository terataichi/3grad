#include "Controller.h"
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"
#include <DxLib.h>

Controller::Controller()
{
	// ������
	for (auto id : InputID())
	{
		triggerMap_[id].first = 0;
		triggerMap_[id].second = 0;
	}

	auto createBuf = [](int&& num)
	{
		RingBuffer* now;
		now = new RingBuffer;

		RingBuffer* first = now;
		first->id_ = 0;
		// �ŏ��Ɉ���Ȃ��Ƃ����Ȃ�����i�͂P����n�߂�
		for (int i = 1; i < num; i++)
		{
			// �V�������
			RingBuffer* next;
			next = new RingBuffer;
			next->id_ = 0;
			// �O��̃|�C���^�[�ێ�
			now->next_ = next;
			now->next_->prev_ = now;
			// ���݂̃|�C���^�[�X�V
			now = next;
		}
		// �Ō�ɐ擪�|�C���^�̑O����Z�b�g����
		now->next_ = first;
		first->prev_ = now;

		return first;
	};

	ringBuf_ = createBuf(30);
}

Controller::~Controller()
{
	// ��Ԍ���next���ŏ��ɏ����Ă���S������
	RingBuffer* nowDel = ringBuf_;
	ringBuf_->prev_->next_ = nullptr;
	while (nowDel->next_ != nullptr)
	{
		RingBuffer* nextDel = nowDel->next_;
		delete nowDel;
		nowDel = nextDel;
	}
	delete nowDel;
}

void Controller::UpdateRingBuf(void)
{
	bool f = false;
	for (auto id : InputID())
	{
		if (GetPushingTrigger(id))
		{
			ringBuf_->id_ = static_cast<int>(id);
			TRACE("%d\n", ringBuf_->id_);
			ringBuf_ = ringBuf_->next_;
			f = true;
		}
	}
	if (!f)
	{
		ringBuf_->id_ = 0;
		TRACE("%d\n", ringBuf_->id_);
		ringBuf_ = ringBuf_->next_;
	}

	for (int i = 0; i < 30; i++)
	{
		_dbgDrawFormatString(30 * i, 700, 0xfff, "%d", ringBuf_->id_);
		ringBuf_->next_;
	}
}

const bool Controller::GetPushTrigger(InputID id)const
{
	return triggerMap_.at(id).first && !triggerMap_.at(id).second;
}

const bool Controller::GetPushingTrigger(InputID id) const
{
	return triggerMap_.at(id).first;
}

const bool Controller::GetReleaseTrigger(InputID id) const
{
	return !triggerMap_.at(id).first && triggerMap_.at(id).second;
}

const bool Controller::GetReleasingTrigger(InputID id) const
{
	return !triggerMap_.at(id).first && !triggerMap_.at(id).second;
}
