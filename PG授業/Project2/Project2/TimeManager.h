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
	const double& GetElapsedTime(void)const;
	const float GetElapsedTimeF(void)const;
	/// <summary>
	/// �f���^�^�C���擾�p
	/// </summary>
	/// <returns>�f���^�^�C��</returns>
	const double& GetDeltaTime(void)const;
	const float GetDeltaTimeF(void)const;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_;
	ChronoTimeP now_;
	ChronoTimeP old_;

	double deltaTime_;															// 1�t���[���Ԃ̎���
	double elapsedTime_;														// �o�ߎ���
};

