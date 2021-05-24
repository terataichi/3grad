#pragma once
#include <chrono>

using ChronoTimeP = std::chrono::system_clock::time_point;

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	/// <summary>
	/// 開始時間からの経過時間
	/// </summary>
	/// <returns></returns>
	const double& GetElapsedTime(void);
	const float& GetElapsedTimeF(void);
	/// <summary>
	/// デルタタイム取得用
	/// </summary>
	/// <returns>デルタタイム</returns>
	const double& GetDeltaTime(void);
	const float& GetDeltaTimeF(void);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_;
	ChronoTimeP now_;
	ChronoTimeP old_;

	double deltaTime_;
	double elapsedTime_;														// 経過時間
};

