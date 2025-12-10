#include "StartWidget.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneUIManager.h"
#include "../../UI/Common/Button.h"
#include "../../Component/SpriteComponent.h"
#include "../../DeltaRune/Scene/SceneTest.h"
#include "../../UI/Common/TextBlock.h"
#include "../../UI/Common/Image.h"
#include "../../Scene/SceneEditor.h"

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

	mBackGround->SetPos(0.f, 0.f);
	mBackGround->SetSize(1280.f, 960.f);
	mBackGround->SetMouseCollisionEnable(false);
	mBackGround->SetZOrder(0);
	mBackGround->SetTexture("StartBG", TEXT("Texture/UI/IMAGE_MENU.png"));

	AddWidget(mBackGround);

	// 배경 이미지 애니메이션
	mBackGroundAnim = mScene->GetUIManager()->CreateWidget<CImage>("StartBGAnim");
	
	mBackGroundAnim->SetPos(640.f, 100.f);
	mBackGroundAnim->SetSize(1280.f, 310.f);
	mBackGroundAnim->SetPivot(FVector2D(0.5f, 0.5f));
	mBackGround->SetMouseCollisionEnable(false);
	mBackGround->SetZOrder(0);

	mBackGroundAnim->SetTexture("StartBGAnim", TEXT("Texture/UI/IMAGE_MENU_ANIMATION/Animation_MENU.png"));

	mBackGroundAnim->SetBrushAnimation(true);
	mBackGroundAnim->AddBrushFrame(0.f, 0.f, 320.f, 70.f);
	mBackGroundAnim->AddBrushFrame(320.f, 0.f, 320.f, 70.f);
	mBackGroundAnim->AddBrushFrame(640.f, 0.f, 320.f, 70.f);
	mBackGroundAnim->AddBrushFrame(960.f, 0.f, 320.f, 70.f);
	mBackGroundAnim->AddBrushFrame(1280.f, 0.f, 320.f, 70.f);
	mBackGroundAnim->SetAnimationPlayTime(1.f);
	mBackGroundAnim->SetAnimationPlayRate(1.f);
	
	AddWidget(mBackGroundAnim);

	// 로고 추가
	mLogo = mScene->GetUIManager()->CreateWidget<CImage>("StartLogo");

	mLogo->SetPos(640.f, 700.f);
	mLogo->SetSize(672.f, 102.f);
	mLogo->SetPivot(FVector2D(0.5f, 0.5f));
	mLogo->SetMouseCollisionEnable(false);
	mLogo->SetZOrder(5);
	mLogo->SetTexture("StartLogo", TEXT("Texture/UI/IMAGE_LOGO_CENTER.png"));

	AddWidget(mLogo);

	// 버튼 추가하기
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");
	mEditorButton = mScene->GetUIManager()->CreateWidget<CButton>("SceneEditorButton");

	mButton->SetPos(550.f, 250.f);
	mButton->SetSize(200.f, 200.f);
	//mButton->SetPivot(FVector2D(0.5f, 0.5f));
	mButton->SetZOrder(7);
	mEditorButton->SetZOrder(7);

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
	AddWidget(mEditorButton);

	CSharedPtr<CTextBlock> Text = mScene->GetUIManager()->CreateWidget<CTextBlock>("ButtonText");

	Text->SetText(TEXT("게임 시작"));
	Text->SetTextColor(0, 0, 0, 255);
	Text->SetPos(550.f, 250.f);
	Text->SetSize(200.f, 200.f);
	Text->SetFontSize(30.f);
	Text->SetZOrder(9);
	Text->SetAlignH(ETextAlignH::Center);
	Text->SetAlignV(ETextAlignV::Middle);

	mButton->SetChild(Text);

	// 에디터 모드 가는 버튼 
	mEditorButton->SetPos(640.f, 100.f);
	mEditorButton->SetSize(100.f, 100.f);
	mEditorButton->SetPivot(FVector2D(0.5f, 0.5f));
	mEditorButton->SetTexture(EButtonState::Normal, "EditButton", TEXT("Texture/Edit.png"));
	mEditorButton->SetTexture(EButtonState::Hovered, "EditButton");
	mEditorButton->SetTexture(EButtonState::Click, "EditButton", TEXT("Texture/Edit.png"));
	mEditorButton->SetTexture(EButtonState::Disable, "EditButton", TEXT("Texture/Edit.png"));
	mEditorButton->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
	mEditorButton->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
	mEditorButton->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mEditorButton->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	mEditorButton->SetEventCallBack(EButtonEventState::Click, this, &CStartWidget::StartEditButtonClick);




	return true;
}

void CStartWidget::StartButtonClick()
{
	CLog::PrintLog("Start Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneMain>();
}

void CStartWidget::StartEditButtonClick()
{
	CLog::PrintLog("Start SceneEditor Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneEditor>();
}
