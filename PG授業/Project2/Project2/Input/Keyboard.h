#pragma once
#include <array>
#include "Controller.h"

class Keyboard :
    public Controller
{
public:
    Keyboard();
    ~Keyboard();

    ControllType GetControllType(void)override;
    void Update(void)override;

private:
    std::array<char, 256U> buf_;                        // unsigned
};

