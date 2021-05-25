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
	const double& GetElapsedTime(void)const;
	const float GetElapsedTimeF(void)const;
	/// <summary>
	/// デルタタイム取得用
	/// </summary>
	/// <returns>デルタタイム</returns>
	const double& GetDeltaTime(void)const;
	const float GetDeltaTimeF(void)const;

	/// <summary>
	/// 更新
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_;
	ChronoTimeP now_;
	ChronoTimeP old_;

	double deltaTime_;															// 1フレーム間の時間
	double elapsedTime_;														// 経過時間
};

