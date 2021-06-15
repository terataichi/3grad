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
    int padID_;                                     // どのゲームパッドから入力を受け取るかの識別ID
};

