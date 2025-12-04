#pragma once

#include "../Widget.h"
#include "../UIInfo.h"

class CImage : public CWidget
{
    friend class CSceneUIManager;

protected:
    CImage();
    virtual ~CImage();

protected:
    // 이미지 브러쉬
    FUIBrush mBrush;

	// 마우스 충돌 비활성화
	bool mMouseCollisionEnable = true;

public:
	void SetMouseCollisionEnable(bool Enable)
	{
		mMouseCollisionEnable = Enable;
	}

public:
	// Name으로 찾아와서 텍스쳐를 넣어주는 방법
	void SetTexture(const std::string& Name);
	// 파일 이름으로 텍스쳐 매니져에서 로드 후 추가하기
	void SetTexture(const std::string& Name, const TCHAR* FileName);
	// 세팅 바로 해주기
	void SetTexture(class CTexture* Texture);

	// 색상 세팅
	void SetTint(float r, float g, float b, float a = 1.f);

	// 애니메이션 프레임
	void AddBrushFrame(const FVector2D& Start, const FVector2D& Size);
	void AddBrushFrame(float StartX, float StartY, float SizeX, float SizeY);

	// 애니메이션 사용 유무
	void SetBrushAnimation(bool Animation);

	// 출력할 프레임
	void SetCurrentFrame(int Frame);

	// 프레임 재생 시간
	void SetAnimationPlayTime(float PlayTime);

	// 재생 속도
	void SetAnimationPlayRate(float PlayRate);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
	virtual bool CollisionMouse(CWidget** Result, const FVector2D& MousePos);
};
