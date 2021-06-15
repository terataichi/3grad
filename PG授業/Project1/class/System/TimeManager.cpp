#include "TimeManager.h"

TimeManager::TimeManager()
{
	startTime_ = std::chrono::system_clock::now();
	now_ = startTime_;
	old_ = now_;
	deltaTime_ = 0;
	elapsedTime_ = 0;
}

TimeManager::~TimeManager()
{
}

const float& TimeManager::GetElapsedTime(void)
{
	return elapsedTime_;
}

const float& TimeManager::GetDeltaTime(void)
{
	return deltaTime_;
}

void TimeManager::Update(void)
{
	old_ = now_;
	now_ = std::chrono::system_clock::now();

	deltaTime_ = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now_ - old_).count()) / 1000.0f;
	if (deltaTime_ > 1.0) deltaTime_ = 0;

	elapsedTime_ = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now_ - startTime_).count());
}
