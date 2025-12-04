#include "MainWidget.h"

#include "../Common/Button.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/TextBlock.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::~CMainWidget()
{
}

bool CMainWidget::Init()
{
	CWindowWidget::Init();

	// 버튼을 추가하기
	// 공격
	mButtonAttack = mScene->GetUIManager()->CreateWidget<CButton>("AttackButton");

	mButtonAttack->SetPos(100.f, 100.f);
	mButtonAttack->SetSize(31.f, 32.f);
	mButtonAttack->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButtonAttack->SetTexture(EButtonState::Normal, "AttackButton", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));
	mButtonAttack->SetTexture(EButtonState::Hovered, "AttackButtonHovered", TEXT("Texture/UI/UIButton/spr_btfight_1.png"));
	mButtonAttack->SetTexture(EButtonState::Click, "AttackButtonClick", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));
	mButtonAttack->SetTexture(EButtonState::Disable, "AttackButtonDisable", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));

	mButtonAttack->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButtonAttack->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	AddWidget(mButtonAttack);

	// 행동
	mButtonAct = mScene->GetUIManager()->CreateWidget<CButton>("ActButton");

	mButtonAct->SetPos(135.f, 100.f);
	mButtonAct->SetSize(31.f, 32.f);
	mButtonAct->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButtonAct->SetTexture(EButtonState::Normal, "ActButton", TEXT("Texture/UI/UIButton/spr_btact_0.png"));
	mButtonAct->SetTexture(EButtonState::Hovered, "ActButtonHovered", TEXT("Texture/UI/UIButton/spr_btact_1.png"));
	mButtonAct->SetTexture(EButtonState::Click, "ActButtonClick", TEXT("Texture/UI/UIButton/spr_btact_0.png"));
	mButtonAct->SetTexture(EButtonState::Disable, "ActButtonDisable", TEXT("Texture/UI/UIButton/spr_btact_0.png"));

	mButtonAct->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButtonAct->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	AddWidget(mButtonAct);

	// 아이템
	mButtonItem = mScene->GetUIManager()->CreateWidget<CButton>("ItemButton");

	mButtonItem->SetPos(170.f, 100.f);
	mButtonItem->SetSize(31.f, 32.f);
	mButtonItem->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButtonItem->SetTexture(EButtonState::Normal, "ItemButton", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));
	mButtonItem->SetTexture(EButtonState::Hovered, "ItemButtonHovered", TEXT("Texture/UI/UIButton/spr_btitem_1.png"));
	mButtonItem->SetTexture(EButtonState::Click, "ItemButtonClick", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));
	mButtonItem->SetTexture(EButtonState::Disable, "ItemButtonDisable", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));

	mButtonItem->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButtonItem->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	AddWidget(mButtonItem);

	// 스페어
	mButtonSpare = mScene->GetUIManager()->CreateWidget<CButton>("SpareButton");

	mButtonSpare->SetPos(205.f, 100.f);
	mButtonSpare->SetSize(31.f, 32.f);
	mButtonSpare->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButtonSpare->SetTexture(EButtonState::Normal, "SpareButton", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));
	mButtonSpare->SetTexture(EButtonState::Hovered, "SpareButtonHovered", TEXT("Texture/UI/UIButton/spr_btspare_1.png"));
	mButtonSpare->SetTexture(EButtonState::Click, "SpareButtonClick", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));
	mButtonSpare->SetTexture(EButtonState::Disable, "SpareButtonDisable", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));

	mButtonSpare->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButtonSpare->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	AddWidget(mButtonSpare);

	// 디펜드
	mButtonDefend = mScene->GetUIManager()->CreateWidget<CButton>("DefendButton");

	mButtonDefend->SetPos(240.f, 100.f);
	mButtonDefend->SetSize(31.f, 32.f);
	mButtonDefend->SetPivot(FVector2D(0.5f, 0.5f));
	//mButton->SetZOrder(1);

	mButtonDefend->SetTexture(EButtonState::Normal, "DefendButton", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));
	mButtonDefend->SetTexture(EButtonState::Hovered, "DefendButtonHovered", TEXT("Texture/UI/UIButton/spr_btdefend_1.png"));
	mButtonDefend->SetTexture(EButtonState::Click, "DefendButtonClick", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));
	mButtonDefend->SetTexture(EButtonState::Disable, "DefendButtonDisable", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));

	mButtonDefend->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButtonDefend->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	AddWidget(mButtonDefend);

	////////////////////////// 폰트
	//CSharedPtr<CTextBlock> Text = mScene->GetUIManager()->CreateWidget<CTextBlock>("ButtonText");

	//Text->SetText(TEXT("Jevil"));
	//Text->SetTextColor(0, 0, 0, 255);
	//Text->SetPos(100.f, 100.f);
	//Text->SetSize(100.f, 100.f);
	//Text->SetFontSize(20.f);
	//Text->SetAlignH(ETextAlignH::Center);
	//Text->SetAlignV(ETextAlignV::Middle);

	//mButtonAttack->SetChild(Text);

	return true;
}
