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
	const float& GetElapsedTime(void);
	/// <summary>
	/// デルタタイム取得用
	/// </summary>
	/// <returns>デルタタイム</returns>
	const float& GetDeltaTime(void);

	void SetOld();

	void SetNow();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_ = std::chrono::system_clock::now();
	ChronoTimeP now_ = startTime_;
	ChronoTimeP old_;

	float deltaTime_;
	float elapsedTime_;														// 経過時間
};

