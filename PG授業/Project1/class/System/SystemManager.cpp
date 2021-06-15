#include "SystemManager.h"
#include <cassert>

std::unique_ptr<SystemManager, SystemManager::SystemManagerDeleter>SystemManager::sInstance_(new SystemManager);

const int& SystemManager::GetScreenSize(const char* x_or_y)const
{
    if (x_or_y == "x")
    {
        return screenSizeX_;
    }
    if (x_or_y == "y")
    {
        return screenSizeY_;
    }
    assert(!"ÉGÉâÅ[");
    return screenSizeX_;
}

SystemManager::SystemManager():screenSizeX_(1280), screenSizeY_(780)
{
}
