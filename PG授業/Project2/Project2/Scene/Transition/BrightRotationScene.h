#pragma once
#include "TransitionScene.h"

class BrightRotationScene :
    public TransitionScene
{
public:
	/// <summary>
	/// �����ɑO�̃V�[���Ǝ��̃V�[����n��
	/// </summary>
	/// <param name="prev">���݂̃V�[��</param>
	/// <param name="next">�ڍs���������V�[��</param>
	/// <param name="limit">���b�Ŋ������Ăق�����</param>
	BrightRotationScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit);
	~BrightRotationScene();

private:
	bool TransitionUpdate()override;
	void DrawOwnScreen()override;

	double angle_;													// �p�x
	float angleCount_;												
	double limit_;													// ���b�Ŋ������Ăق�����
	double time_;													// �o�ߎ���
	double fadeCount_;												// ��ʌ��ʗp
};

