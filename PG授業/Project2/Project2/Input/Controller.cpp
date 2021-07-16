#include "Controller.h"
#include "../_debug/_DebugDispOut.h"
#include "../_debug/_DebugConOut.h"
#include <DxLib.h>

Controller::Controller()
{
	// 初期化
	for (auto id : InputID())
	{
		triggerMap_[id].first = 0;
		triggerMap_[id].second = 0;
	}

	auto createBuf = [&](int&& num)
	{
		RingBuffer* now;
		now = new RingBuffer;

		RingBuffer* first = now;
		first->id_ = 0;
		first->num_ = 0;
		// 最初に一個作らないといけないからiは１から始める
		for (int i = 1; i < num; i++)
		{
			// 新しく作る
			RingBuffer* next;
			next = new RingBuffer;
			next->id_ = 0;
			next->num_ = i;								// 番号保持

			// 前後のポインター保持
			now->next_ = next;
			now->next_->prev_ = now;
			// 現在のポインター更新
			now = next;
		}
		// 最後に先頭ポインタの前後をセットする
		now->next_ = first;
		first->prev_ = now;
		startBuf_ = now;
		return first;
	};

	ringBuf_ = createBuf(CREATE_RINGBUF_NUM);
}

Controller::~Controller()
{
	// 一番後ろのnextを最初に消してから全部消す
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
	bool neutral = false;
	ringBuf_ = ringBuf_->next_;
	ringBuf_->id_ = 0;
	for (auto id : InputID())
	{
		if (GetPushingTrigger(id))
		{
			ringBuf_->id_ |= static_cast<unsigned int>(id);
			//TRACE("%d\n", ringBuf_->id_);
			neutral = true;
		}
	}
	// 入力がされなかった
	if (!neutral)
	{
		ringBuf_->id_ = 0;
		startBuf_ = ringBuf_->next_;
	}
	else 
	{
		if (startBuf_ == ringBuf_)
		{
			startBuf_ = startBuf_->next_;
		}
	}

	auto debug = startBuf_;
	int i = 0;
	while (debug != ringBuf_)
	{
		_dbgDrawFormatString(30 * (CREATE_RINGBUF_NUM - i), 700, 0xfff, "%d", debug->id_);
		debug = debug->next_;
		i++;
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

const Controller::RingBuffer* Controller::GetRingBuf(void) const
{
	return ringBuf_;
}

const Controller::RingBuffer* Controller::GetStartBuf(void) const
{
	return startBuf_;
}

const bool Controller::GetReleasingTrigger(InputID id) const
{
	return !triggerMap_.at(id).first && !triggerMap_.at(id).second;
}
