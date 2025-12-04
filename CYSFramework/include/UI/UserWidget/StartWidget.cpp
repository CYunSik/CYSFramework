#include "StartWidget.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Button.h"
#include "../../Component/SpriteComponent.h"
#include "../Common/TextBlock.h"
#include "../Common/Image.h"

#include "../../Share/Log.h"

CStartWidget::CStartWidget()
{
}

CStartWidget::~CStartWidget()
{
}

bool CStartWidget::Init()
{
	CUserWidget::Init();

	// 배경 이미지
	mBackGround = mScene->GetUIManager()->CreateWidget<CImage>("StartBG");

	mBackGround->SetPos(640.f, 360.f);
	mBackGround->SetSize(960.f, 720.f);
	mBackGround->SetPivot(FVector2D(0.5f, 0.5f));
	mBackGround->SetMouseCollisionEnable(false);
	mBackGround->SetZOrder(0);
	mBackGround->SetTexture("StartBG", TEXT("Texture/UI/IMAGE_MENU.png"));

	AddWidget(mBackGround);

	// 배경 이미지 애니메이션
	mBackGroundAnim = mScene->GetUIManager()->CreateWidget<CImage>("StartBGAnim");
	
	mBackGroundAnim->SetPos(640.f, 100.f);
	mBackGroundAnim->SetSize(960.f, 200.f);
	mBackGroundAnim->SetPivot(FVector2D(0.5f, 0.5f));
	mBackGround->SetMouseCollisionEnable(false);
	mBackGround->SetZOrder(3);

	mBackGroundAnim->SetTexture("StartBGAnim", TEXT("Texture/UI/IMAGE_MENU_ANIMATION/Animation_MENU.png"));

	mBackGroundAnim->AddBrushFrame(0.f, 0.f, 0.2f, 1.f);
	mBackGroundAnim->AddBrushFrame(0.2f, 0.f, 0.4f, 1.f);
	mBackGroundAnim->AddBrushFrame(0.4f, 0.f, 0.6f, 1.f);
	mBackGroundAnim->AddBrushFrame(0.6f, 0.f, 0.8f, 1.f);
	mBackGroundAnim->AddBrushFrame(0.8f, 0.f, 1.0f, 1.f);
	//mBackGroundAnim->SetCurrentFrame(0);
	mBackGroundAnim->SetBrushAnimation(true);
	mBackGroundAnim->SetAnimationPlayTime(1.f);
	mBackGroundAnim->SetAnimationPlayRate(1.f);
	
	AddWidget(mBackGroundAnim);

	// 로고 추가
	mLogo = mScene->GetUIManager()->CreateWidget<CImage>("StartLogo");

	mLogo->SetPos(640.f, 500.f);
	mLogo->SetSize(448.f, 68.f);
	mLogo->SetPivot(FVector2D(0.5f, 0.5f));
	mLogo->SetMouseCollisionEnable(false);
	mLogo->SetZOrder(3);
	mLogo->SetTexture("StartLogo", TEXT("Texture/UI/IMAGE_LOGO_CENTER.png"));

	AddWidget(mLogo);

	// 버튼 추가하기
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");

	mButton->SetPos(600.f, 200.f);
	mButton->SetSize(100.f, 100.f);
	//mButton->SetPivot(FVector2D(0.5f, 0.5f));
	mButton->SetZOrder(5);

	mButton->SetTexture(EButtonState::Normal, "StartButton", TEXT("Texture/spr_nothing.png"));
	mButton->SetTexture(EButtonState::Hovered, "StartButton");
	mButton->SetTexture(EButtonState::Click, "StartButton", TEXT("Texture/spr_nothing.png"));
	mButton->SetTexture(EButtonState::Disable, "StartButton", TEXT("Texture/spr_nothing.png"));

	mButton->SetTint(EButtonState::Normal, 1.f, 1.f, 1.f);
	mButton->SetTint(EButtonState::Hovered, 0.8f, 0.8f, 0.8f);
	mButton->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButton->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	mButton->SetEventCallBack(EButtonEventState::Click, this, &CStartWidget::StartButtonClick);

	AddWidget(mButton);

	CSharedPtr<CTextBlock> Text = mScene->GetUIManager()->CreateWidget<CTextBlock>("ButtonText");

	Text->SetText(TEXT("게임 시작"));
	Text->SetTextColor(0, 0, 0, 255);
	Text->SetPos(600.f, 200.f);
	Text->SetSize(100.f, 100.f);
	Text->SetFontSize(20.f);
	Text->SetZOrder(8);
	Text->SetAlignH(ETextAlignH::Center);
	Text->SetAlignV(ETextAlignV::Middle);

	mButton->SetChild(Text);


	return true;
}

void CStartWidget::StartButtonClick()
{
	CLog::PrintLog("Start Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneMain>();
}
