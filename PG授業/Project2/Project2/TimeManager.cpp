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

const double& TimeManager::GetElapsedTime(void)const
{
	return elapsedTime_;
}

const float TimeManager::GetElapsedTimeF(void)const
{
	return static_cast<float>(elapsedTime_);
}

const double& TimeManager::GetDeltaTime(void)const
{
	return deltaTime_;
}

const float TimeManager::GetDeltaTimeF(void)const
{
	return static_cast<float>(deltaTime_);
}

void TimeManager::Update(void)
{
	old_ = now_;
	now_ = std::chrono::system_clock::now();

	deltaTime_ = std::chrono::duration_cast<std::chrono::microseconds>(now_ - old_).count() / 1000000.0;
	if (deltaTime_ > 1.0) deltaTime_ = 0.0;

	elapsedTime_ = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(now_ - startTime_).count());
}
