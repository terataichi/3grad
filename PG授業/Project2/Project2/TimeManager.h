#pragma once
#include <chrono>

#define lpTimeManager TimeManager::GetInstance()

using ChronoTimeP = std::chrono::system_clock::time_point;

class TimeManager
{
public:
	/// <summary>
	/// 実体の取得
	/// </summary>
	/// <returns>実体が返る</returns>
	static TimeManager& GetInstance()
	{
		return *sInstance_;
	}

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
	TimeManager();
	~TimeManager();

	/// <summary>
	/// カスタムデリーター
	/// </summary>
	struct TimeManagerDeleter
	{
		void operator()(TimeManager* manager)
		{
			delete manager;
		}
	};

	ChronoTimeP startTime_;
	ChronoTimeP now_;
	ChronoTimeP old_;

	double deltaTime_;															// 1フレーム間の時間
	double elapsedTime_;														// 経過時間

	static std::unique_ptr<TimeManager, TimeManagerDeleter> sInstance_;			// 実体
};

