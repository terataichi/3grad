#pragma once
#include "../BaseScene.h"

enum class Trantision
{
    CrossFade,
    FadeInOut,
    Max
};

class TransitionScene :
    public BaseScene
{
public:
    TransitionScene(UniqueBase beforScene, UniqueBase afterScene);
    ~TransitionScene();

private:
    bool Init(void)override;
    UniqueBase Update(UniqueBase scene)override;
    virtual bool TransitionUpdate() = 0;
    SceneName MyName()override final { return SceneName::Transition; };
protected:
    UniqueBase beforScene_;
    UniqueBase afterScene_;
};

