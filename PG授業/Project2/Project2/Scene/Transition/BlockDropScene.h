#pragma once
#include "TransitionScene.h"
class BlockDropScene :
    public TransitionScene
{
public:
	BlockDropScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit);
	~BlockDropScene();

private:
	bool TransitionUpdate()override;
	void DrawOwnScreen()override;

	double limit_;													// ���b�Ŋ������Ăق�����
	double time_;													// �o�ߎ���
	double fadeCount_;												// ��ʌ��ʗp

	Size division_;
	int size_;
	float speed_;
	float count_;
};

