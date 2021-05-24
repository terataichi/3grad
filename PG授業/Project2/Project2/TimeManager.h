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
	const double& GetElapsedTime(void);
	const float& GetElapsedTimeF(void);
	/// <summary>
	/// �f���^�^�C���擾�p
	/// </summary>
	/// <returns>�f���^�^�C��</returns>
	const double& GetDeltaTime(void);
	const float& GetDeltaTimeF(void);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(void);
private:
	ChronoTimeP startTime_;
	ChronoTimeP now_;
	ChronoTimeP old_;

	double deltaTime_;
	double elapsedTime_;														// �o�ߎ���
};

