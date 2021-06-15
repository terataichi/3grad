#pragma once
#include <memory>

#define lpSysMng SystemManager::GetInstatnce()

class SystemManager
{
public:
	static SystemManager& GetInstatnce()
	{
		return *sInstance_;
	}

	const int& GetScreenSize(const char* x_or_y) const;

private:
	SystemManager();

	struct SystemManagerDeleter
	{
		void operator()(SystemManager* system)const
		{
			delete system;
		}
	};

	int screenSizeX_;
	int screenSizeY_;

	static std::unique_ptr<SystemManager, SystemManagerDeleter>sInstance_;
};

