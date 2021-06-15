#pragma once
#include "Controller.h"

class Gamepad :
    public Controller
{
public:
    Gamepad();
    ~Gamepad();

    ControllType GetControllType(void)override;
    void Update(void)override;

private:
    int padID_;                                     // �ǂ̃Q�[���p�b�h������͂��󂯎�邩�̎���ID
};

