#include "Button.h"

#include "../../Asset/Texture/Texture.h"
#include "../../Asset/Texture/TextureManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAssetManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Sound/Sound.h"
#include "../../Asset/Sound/SoundManager.h"

CButton::CButton()
{
}

CButton::~CButton()
{
}

// 해당 스테이트에 Texture을 찾아와서 넣어준다
void CButton::SetTexture(EButtonState::Type State, const std::string& Name)
{
	if (mScene)
	{
		mBrush[State].Texture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		mBrush[State].Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}
}

void CButton::SetTexture(EButtonState::Type State, const std::string& Name, const TCHAR* FileName)
{
	if (mScene)
	{
		if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
		{
			return;
		}

		mBrush[State].Texture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
		{
			return;
		}

		mBrush[State].Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}
}

void CButton::SetTexture(EButtonState::Type State, class CTexture* Texture)
{
	mBrush[State].Texture = Texture;
}

void CButton::SetTint(EButtonState::Type State, float r, float g, float b, float a)
{
	mBrush[State].Tint.x = r;
	mBrush[State].Tint.y = g;
	mBrush[State].Tint.z = b;
	mBrush[State].Tint.w = a;
}

void CButton::AddBrushFrame(EButtonState::Type State, const FVector2D& Start, const FVector2D& Size)
{
	FAnimationFrame Frame;
	Frame.Start = Start;
	Frame.Size = Size;

	mBrush[State].Frames.emplace_back(Frame);

	mBrush[State].FrameTime = mBrush[State].PlayTime / mBrush[State].Frames.size();
}

void CButton::AddBrushFrame(EButtonState::Type State, float StartX, float StartY, float SizeX, float SizeY)
{
	FAnimationFrame Frame;
	Frame.Start.x = StartX;
	Frame.Start.y = StartY;
	Frame.Size.x = SizeX;
	Frame.Size.y = SizeY;

	mBrush[State].Frames.emplace_back(Frame);

	mBrush[State].FrameTime = mBrush[State].PlayTime / mBrush[State].Frames.size();
}

void CButton::SetBrushAnimation(EButtonState::Type State, bool Animation)
{
	mBrush[State].AnimationEnable = Animation;
}

void CButton::SetCurrentFrame(EButtonState::Type State, int Frame)
{
	mBrush[State].Frame = Frame;
}

void CButton::SetAnimationPlayTime(EButtonState::Type State, float PlayTime)
{
	mBrush[State].PlayTime = PlayTime;
}

void CButton::SetAnimationPlayRate(EButtonState::Type State, float PlayRate)
{
	mBrush[State].PlayRate = PlayRate;
}

void CButton::SetSound(EButtonState::Type State, const std::string& Name)
{
	if (mScene)
	{
		mSound[State] = mScene->GetAssetManager()->FindSound(Name);
	}
	else
	{
		mSound[State] = CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);
	}
}

void CButton::SetSound(EButtonState::Type State, const std::string& Name, const char* FileName)
{
	if (mScene)
	{
		if (!mScene->GetAssetManager()->LoadSound(Name, "UI", false, FileName))
		{
			return;
		}

		mSound[State] = mScene->GetAssetManager()->FindSound(Name);
	}
	else
	{
		if (!CAssetManager::GetInst()->GetSoundManager()->LoadSound(Name, "UI", false, FileName))
		{
			return;
		}

		mSound[State] = CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);
	}
}

bool CButton::Init()
{
	CWidget::Init();

	return true;
}

void CButton::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CButton::Render()
{
	CWidget::Render();
}
