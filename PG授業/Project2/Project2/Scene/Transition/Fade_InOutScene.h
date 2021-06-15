#pragma once
#include "TransitionScene.h"

class Fade_InOutScene :
    public TransitionScene
{
public:
	/// <summary>
	/// �����ɑO�̃V�[���Ǝ��̃V�[����n��
	/// </summary>
	/// <param name="prev">���݂̃V�[��</param>
	/// <param name="next">�ڍs���������V�[��</param>
	/// <param name="limit">���b�Ŋ������Ăق�����</param>
	Fade_InOutScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit);
	~Fade_InOutScene();

private:
	bool TransitionUpdate(const double& deltaTime)override;
	void DrawOwnScreen(const double& deltaTime)override;

	double limit_;													// ���b�Ŋ������Ăق�����
	double time_;													// �o�ߎ���
	double fadeCount_;												// ��ʌ��ʗp
};

