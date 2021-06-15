#pragma once
#include <chrono>

using ChronoTimeP = std::chrono::system_clock::time_point;

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	/// <summary>
	/// �J�n���Ԃ���̌o�ߎ���
	/// </summary>
	/// <returns></returns>
	const float& GetElapsedTime(void);
	/// <summary>
	/// �f���^�^�C���擾�p
	/// </summary>
	/// <returns>�f���^�^�C��</returns>
	const float& GetDeltaTime(void);

	void SetOld();

	void SetNow();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_ = std::chrono::system_clock::now();
	ChronoTimeP now_ = startTime_;
	ChronoTimeP old_;

	float deltaTime_;
	float elapsedTime_;														// �o�ߎ���
};

