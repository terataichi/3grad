#include "Controller.h"

Controller::Controller()
{
	// èâä˙âª
	for (auto id : InputID())
	{
		triggerMap_[id].first = 0;
		triggerMap_[id].second = 0;
	}

	commandBuf_.reserve(20);
	commandBuf_.resize(20);
}

Controller::~Controller()
{
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
