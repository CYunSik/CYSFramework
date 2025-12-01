#pragma once
#include "../Object/SceneObject.h"

class CPartyCharacter : public CSceneObject
{
    friend class CScene;

protected:
    CPartyCharacter();
    virtual ~CPartyCharacter();

protected:
    CSharedPtr<class CSpriteComponent> mSprite;
    class CAnimation2D* mAnimation = nullptr;

    float mMoveSpeed = 100.f;
    bool mIsWalking = false;

    // 캐릭터 이름
    std::string mCharacterName;

public:
    void SetCharacterName(const std::string& Name)
    {
        mCharacterName = Name;
    }

    virtual bool Init() override;
    virtual void Update(float DeltaTime) override;

    // 컷씬용 이동
    void MoveRight(float DeltaTime);
    void Stop();
};
