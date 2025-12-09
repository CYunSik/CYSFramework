#include "BattleWidget.h"

#include "../../UI/Common/Button.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../../UI/Common/Image.h"
#include "../../UI/Common/TextBlock.h"

CBattleWidget::CBattleWidget()
{
}

CBattleWidget::~CBattleWidget()
{
}

bool CBattleWidget::Init()
{
	CWindowWidget::Init();

	// 전투UI 텍스트
	CSharedPtr<CTextBlock> Text = mScene->GetUIManager()->CreateWidget<CTextBlock>("ButtonText");

	Text->SetText(TEXT("*    게임을  시작하자 !"));
	Text->SetTextColor(255, 255, 255, 255);
	Text->SetPos(65.f, 190.f);
	Text->SetSize(1000.f, 40.f);
	Text->SetFontSize(50.f);
	Text->SetAlignH(ETextAlignH::Left);
	Text->SetAlignV(ETextAlignV::Middle);

	AddWidget(Text);

	// 크리스 상태 버튼
	// 크리스 공격
	mKrisButtonAttack = mScene->GetUIManager()->CreateWidget<CButton>("KrisAttackButton");

	mKrisButtonAttack->SetPos(90.f, 290.f);
	mKrisButtonAttack->SetSize(51.f, 52.f);
	mKrisButtonAttack->SetPivot(FVector2D(0.5f, 0.5f));

	mKrisButtonAttack->SetTexture(EButtonState::Normal, "KrisAttackButton", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));
	mKrisButtonAttack->SetTexture(EButtonState::Hovered, "KriAttackButtonHovered", TEXT("Texture/UI/UIButton/spr_btfight_1.png"));
	mKrisButtonAttack->SetTexture(EButtonState::KeyboardHovered, "KriAttackButtonHovered", TEXT("Texture/UI/UIButton/spr_btfight_1.png"));
	mKrisButtonAttack->SetTexture(EButtonState::Click, "KriAttackButtonClick", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));
	mKrisButtonAttack->SetTexture(EButtonState::Disable, "KriAttackButtonDisable", TEXT("Texture/UI/UIButton/spr_btfight_0.png"));

	AddWidget(mKrisButtonAttack);

	// 크리스 행동
	mKrisButtonAct = mScene->GetUIManager()->CreateWidget<CButton>("KrisActButton");

	mKrisButtonAct->SetPos(150.f, 290.f);
	mKrisButtonAct->SetSize(51.f, 52.f);
	mKrisButtonAct->SetPivot(FVector2D(0.5f, 0.5f));

	mKrisButtonAct->SetTexture(EButtonState::Normal, "KrisActButton", TEXT("Texture/UI/UIButton/spr_btact_0.png"));
	mKrisButtonAct->SetTexture(EButtonState::Hovered, "KrisActButtonHovered", TEXT("Texture/UI/UIButton/spr_btact_1.png"));
	mKrisButtonAct->SetTexture(EButtonState::KeyboardHovered, "KrisActButtonHovered", TEXT("Texture/UI/UIButton/spr_btact_1.png"));
	mKrisButtonAct->SetTexture(EButtonState::Click, "KrisActButtonClick", TEXT("Texture/UI/UIButton/spr_btact_0.png"));
	mKrisButtonAct->SetTexture(EButtonState::Disable, "KrisActButtonDisable", TEXT("Texture/UI/UIButton/spr_btact_0.png"));

	AddWidget(mKrisButtonAct);

	// 크리스 아이템
	mKrisButtonItem = mScene->GetUIManager()->CreateWidget<CButton>("KrisItemButton");

	mKrisButtonItem->SetPos(210.f, 290.f);
	mKrisButtonItem->SetSize(51.f, 52.f);
	mKrisButtonItem->SetPivot(FVector2D(0.5f, 0.5f));

	mKrisButtonItem->SetTexture(EButtonState::Normal, "KrisItemButton", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));
	mKrisButtonItem->SetTexture(EButtonState::Hovered, "KrisItemButtonHovered", TEXT("Texture/UI/UIButton/spr_btitem_1.png"));
	mKrisButtonItem->SetTexture(EButtonState::KeyboardHovered, "KrisItemButtonHovered", TEXT("Texture/UI/UIButton/spr_btitem_1.png"));
	mKrisButtonItem->SetTexture(EButtonState::Click, "KrisItemButtonClick", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));
	mKrisButtonItem->SetTexture(EButtonState::Disable, "KrisItemButtonDisable", TEXT("Texture/UI/UIButton/spr_btitem_0.png"));

	AddWidget(mKrisButtonItem);

	// 크리스 스페어
	mKrisButtonSpare = mScene->GetUIManager()->CreateWidget<CButton>("KrisSpareButton");

	mKrisButtonSpare->SetPos(270.f, 290.f);
	mKrisButtonSpare->SetSize(51.f, 52.f);
	mKrisButtonSpare->SetPivot(FVector2D(0.5f, 0.5f));

	mKrisButtonSpare->SetTexture(EButtonState::Normal, "KrisSpareButton", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));
	mKrisButtonSpare->SetTexture(EButtonState::Hovered, "KrisSpareButtonHovered", TEXT("Texture/UI/UIButton/spr_btspare_1.png"));
	mKrisButtonSpare->SetTexture(EButtonState::KeyboardHovered, "KrisSpareButtonHovered", TEXT("Texture/UI/UIButton/spr_btspare_1.png"));
	mKrisButtonSpare->SetTexture(EButtonState::Click, "KrisSpareButtonClick", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));
	mKrisButtonSpare->SetTexture(EButtonState::Disable, "KrisSpareButtonDisable", TEXT("Texture/UI/UIButton/spr_btspare_0.png"));

	AddWidget(mKrisButtonSpare);

	// 크리스 디펜드
	mKrisButtonDefend = mScene->GetUIManager()->CreateWidget<CButton>("KrisDefendButton");

	mKrisButtonDefend->SetPos(330.f, 290.f);
	mKrisButtonDefend->SetSize(51.f, 52.f);
	mKrisButtonDefend->SetPivot(FVector2D(0.5f, 0.5f));

	mKrisButtonDefend->SetTexture(EButtonState::Normal, "KrisDefendButton", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));
	mKrisButtonDefend->SetTexture(EButtonState::Hovered, "KrisDefendButtonHovered", TEXT("Texture/UI/UIButton/spr_btdefend_1.png"));
	mKrisButtonDefend->SetTexture(EButtonState::KeyboardHovered, "KrisDefendButtonHovered", TEXT("Texture/UI/UIButton/spr_btdefend_1.png"));
	mKrisButtonDefend->SetTexture(EButtonState::Click, "KrisDefendButtonClick", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));
	mKrisButtonDefend->SetTexture(EButtonState::Disable, "KrisDefendButtonDisable", TEXT("Texture/UI/UIButton/spr_btdefend_0.png"));

	AddWidget(mKrisButtonDefend);

	return true;
}
