#include "BattleHUD.h"

#include "../../Component/SpriteComponent.h"

CBattleHUD::CBattleHUD()
{
}

CBattleHUD::CBattleHUD(const CBattleHUD& Obj)
{
}

CBattleHUD::CBattleHUD(CBattleHUD&& Obj)
{
}

CBattleHUD::~CBattleHUD()
{
}

bool CBattleHUD::Init()
{
	CSceneObject::Init();

	// 맨 밑 전투 UI
	mBattleUIDown = CreateComponent<CSpriteComponent>("BattleUIObj");
	mBattleUIDown->SetTexture("BattleUIDown", TEXT("Texture/UI/Battle/BattleUIdown.png"));
	mBattleUIDown->SetTint(1.f, 1.f, 1.f);
	mBattleUIDown->SetPivot(0.5f, 0.5f);

	SetRootComponent(mBattleUIDown);

	// 기본 검은 배경
	mBlackBG1 = CreateComponent<CSpriteComponent>("BattleUIObj");
	mBlackBG1->SetTexture("BlakcBG1", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mBlackBG1->SetWorldPos(-428.f, -161.5f);
	mBlackBG1->SetWorldScale(423.5f, 44.8f);
	mBlackBG1->SetPivot(0.5f, 0.f);

	mBlackBG2 = CreateComponent<CSpriteComponent>("BattleUIObj");
	mBlackBG2->SetTexture("BlakcBG2", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mBlackBG2->SetWorldPos(-4.f, -161.5f);
	mBlackBG2->SetWorldScale(423.5f, 44.8f);
	mBlackBG2->SetPivot(0.5f, 0.f);

	mBlackBG3 = CreateComponent<CSpriteComponent>("BattleUIObj");
	mBlackBG3->SetTexture("BlakcBG3", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mBlackBG3->SetWorldPos(421.f, -161.5f);
	mBlackBG3->SetWorldScale(423.5f, 44.8f);
	mBlackBG3->SetPivot(0.5f, 0.f);

	// 각 캐릭터별 상태창 검은 배경
	mKrisBlackBlock = CreateComponent<CSpriteComponent>("BattleUIObj");
	mKrisBlackBlock->SetTexture("BlackBlock", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mKrisBlackBlock->SetWorldPos(-428.f, -161.5f);
	mKrisBlackBlock->SetWorldScale(423.5f, 44.8f);
	mKrisBlackBlock->SetPivot(0.5f, 0.f);

	mSusieBlackBlock = CreateComponent<CSpriteComponent>("BattleUIObj");
	mSusieBlackBlock->SetTexture("BlackBlock2", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mSusieBlackBlock->SetWorldPos(-4.f, -161.5f);
	mSusieBlackBlock->SetWorldScale(423.5f, 44.8f);
	mSusieBlackBlock->SetPivot(0.5f, 0.f);

	mRalseiBlackBlock = CreateComponent<CSpriteComponent>("BattleUIObj");
	mRalseiBlackBlock->SetTexture("BlackBlock3", TEXT("Texture/UI/Battle/CharacterBlackBlock.png"));
	mRalseiBlackBlock->SetWorldPos(421.f, -161.5f);
	mRalseiBlackBlock->SetWorldScale(423.5f, 44.8f);
	mRalseiBlackBlock->SetPivot(0.5f, 0.f);

	// TP 글씨
	mTP = CreateComponent<CSpriteComponent>("BattleUIObj");
	mTP->SetTexture("TP", TEXT("Texture/UI/letter/spr_tplogo.png"));
	mTP->SetWorldPos(-605.f, 200.f);
	mTP->SetWorldScale(40.f, 60.f);
	mTP->SetPivot(0.5f, 0.5f);

	// TPBar
	mTPBar = CreateComponent<CSpriteComponent>("BattleUIObj");
	mTPBar->SetTexture("TPBar", TEXT("Texture/UI/spr_tensionbar/spr_tensionbar_0.png"));
	mTPBar->SetWorldPos(-550.f, 150.f);
	mTPBar->SetWorldScale(40.f, 240.f);
	mTPBar->SetPivot(0.5f, 0.5f);

	// TPBar EmptyFill
	mTPBarEmptyFill = CreateComponent<CSpriteComponent>("BattleUIObj");
	mTPBarEmptyFill->SetTexture("TPBarEmptyFill", TEXT("Texture/UI/spr_tensionbar/spr_tensionbar_1.png"));
	mTPBarEmptyFill->SetWorldPos(-550.f, 150.f);
	mTPBarEmptyFill->SetWorldScale(40.f, 240.f);
	mTPBarEmptyFill->SetPivot(0.5f, 0.5f);

	// TPBar Fill
	mTPBarFill = CreateComponent<CSpriteComponent>("BattleUIObj");
	mTPBarFill->SetTexture("TPBarFill", TEXT("Texture/UI/spr_tensionfilling/spr_tensionfilling_0.png"));
	mTPBarFill->SetWorldPos(-550.f, 150.f);
	mTPBarFill->SetWorldScale(40.f, 240.f);
	mTPBarFill->SetPivot(0.5f, 0.5f);

	/////////////////////////////////////크리스/////////////////////////////////////////
	// 크리스 아이콘
	mKrisIcon = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisIcon->SetTexture("KrisIcon", TEXT("Texture/Kris/spr_headkris/spr_headkris_0.png"));
	mKrisIcon->SetWorldPos(-575.f, -140.f);
	mKrisIcon->SetWorldScale(58.f, 33.f);
	mKrisIcon->SetPivot(0.5f, 0.5f);

	// 크리스 이름
	mKrisName = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisName->SetTexture("KrisName", TEXT("Texture/UI/letter/spr_ja_bnamekris.png"));
	mKrisName->SetWorldPos(-500.f, -140.f);
	mKrisName->SetWorldScale(80.f, 20.f);
	mKrisName->SetPivot(0.5f, 0.5f);

	// 크리스 HP
	mKrisHP = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisHP->SetTexture("KrisHP", TEXT("Texture/UI/letter/spr_hpname.png"));
	mKrisHP->SetWorldPos(-410.f, -150.f);
	mKrisHP->SetWorldScale(26.f, 16.f);
	mKrisHP->SetPivot(0.5f, 0.5f);

	// 크리스 HPBar Back
	mKrisHPBarBack = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisHPBarBack->SetTexture("KrisHPBarBack", TEXT("Texture/UI/healthbar/healthbar_black.png"));
	mKrisHPBarBack->SetWorldPos(-310.f, -148.f);
	mKrisHPBarBack->SetWorldScale(150.f, 12.f);
	mKrisHPBarBack->SetPivot(0.5f, 0.5f);

	// 크리스 HPBar
	mKrisHPBar = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisHPBar->SetTexture("KrisHPBar", TEXT("Texture/UI/healthbar/Krishealthbar.png"));
	mKrisHPBar->SetWorldPos(-310.f, -148.f);
	mKrisHPBar->SetWorldScale(150.f, 12.f);
	mKrisHPBar->SetPivot(0.5f, 0.5f);

	// 크리스 최대 HP 90
	// 9
	mKrisHP9 = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisHP9->SetTexture("KrisHP9", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_9.png"));
	mKrisHP9->SetWorldPos(-253.f, -132.f);
	mKrisHP9->SetWorldScale(10.f, 12.f);
	mKrisHP9->SetPivot(0.5f, 0.5f);

	// 0
	mKrisHP0 = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisHP0->SetTexture("KrisHP0", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_0.png"));
	mKrisHP0->SetWorldPos(-240.f, -132.f);
	mKrisHP0->SetWorldScale(10.f, 12.f);
	mKrisHP0->SetPivot(0.5f, 0.5f);

	// 크리스 슬래쉬
	mKrisSlash = CreateComponent<CSpriteComponent>("BattleUI2");
	mKrisSlash->SetTexture("KrisSlash", TEXT("Texture/UI/letter/spr_hpslash.png"));
	mKrisSlash->SetWorldPos(-300.f, -132.f);
	mKrisSlash->SetWorldScale(24.f, 16.f);
	mKrisSlash->SetPivot(0.5f, 0.5f);
	/////////////////////////////////////크리스/////////////////////////////////////////
	
	//////////////////////////////////////수지//////////////////////////////////////////
	// 수지 아이콘
	mSusieIcon = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieIcon->SetTexture("SusieIcon", TEXT("Texture/Susie/spr_headsusie/spr_headsusie_0.png"));
	mSusieIcon->SetWorldPos(-151.f, -143.f);
	mSusieIcon->SetWorldScale(58.f, 33.f);
	mSusieIcon->SetPivot(0.5f, 0.5f);

	// 수지 이름
	mSusieName = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieName->SetTexture("SusieName", TEXT("Texture/UI/letter/spr_ja_bnamesusie.png"));
	mSusieName->SetWorldPos(-70.f, -140.f);
	mSusieName->SetWorldScale(90.f, 20.f);
	mSusieName->SetPivot(0.5f, 0.5f);

	// 수지 HP
	mSusieHP = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHP->SetTexture("SusieHP", TEXT("Texture/UI/letter/spr_hpname.png"));
	mSusieHP->SetWorldPos(14.f, -150.f);
	mSusieHP->SetWorldScale(26.f, 16.f);
	mSusieHP->SetPivot(0.5f, 0.5f);

	// 수지 HPBar Back
	mSusieHPBarBack = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHPBarBack->SetTexture("SusieHPBarBack", TEXT("Texture/UI/healthbar/healthbar_black.png"));
	mSusieHPBarBack->SetWorldPos(114.f, -148.f);
	mSusieHPBarBack->SetWorldScale(150.f, 12.f);
	mSusieHPBarBack->SetPivot(0.5f, 0.5f);

	// 수지 HPBar
	mSusieHPBar = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHPBar->SetTexture("SusieHPBar", TEXT("Texture/UI/healthbar/Susiehealthbar.png"));
	mSusieHPBar->SetWorldPos(114.f, -148.f);
	mSusieHPBar->SetWorldScale(150.f, 12.f);
	mSusieHPBar->SetPivot(0.5f, 0.5f);

	// 수지 최대 HP 110
	// 1
	mSusieHP100 = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHP100->SetTexture("SusieHP100", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_1.png"));
	mSusieHP100->SetWorldPos(158.f, -132.f);
	mSusieHP100->SetWorldScale(10.f, 12.f);
	mSusieHP100->SetPivot(0.5f, 0.5f);

	// 1
	mSusieHP10 = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHP10->SetTexture("SusieHP10", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_1.png"));
	mSusieHP10->SetWorldPos(171.f, -132.f);
	mSusieHP10->SetWorldScale(10.f, 12.f);
	mSusieHP10->SetPivot(0.5f, 0.5f);

	// 0
	mSusieHP0 = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieHP0->SetTexture("SusieHP0", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_0.png"));
	mSusieHP0->SetWorldPos(184.f, -132.f);
	mSusieHP0->SetWorldScale(10.f, 12.f);
	mSusieHP0->SetPivot(0.5f, 0.5f);

	// 수지 슬래쉬
	mSusieSlash = CreateComponent<CSpriteComponent>("BattleUI2");
	mSusieSlash->SetTexture("SusieSlash", TEXT("Texture/UI/letter/spr_hpslash.png"));
	mSusieSlash->SetWorldPos(124.f, -132.f);
	mSusieSlash->SetWorldScale(24.f, 16.f);
	mSusieSlash->SetPivot(0.5f, 0.5f);
	//////////////////////////////////////수지//////////////////////////////////////////

	/////////////////////////////////////랄세이/////////////////////////////////////////
	// 랄세이 아이콘
	mRalseiIcon = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiIcon->SetTexture("RalseiIcon", TEXT("Texture/Ralsei/spr_headralsei/spr_headralsei_0.png"));
	mRalseiIcon->SetWorldPos(274.f, -145.f);
	mRalseiIcon->SetWorldScale(65.f, 37.f);
	mRalseiIcon->SetPivot(0.5f, 0.5f);

	// 랄세이 이름
	mRalseiName = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiName->SetTexture("RalseiName", TEXT("Texture/UI/letter/spr_ja_bnameralsei.png"));
	mRalseiName->SetWorldPos(355.f, -140.f);
	mRalseiName->SetWorldScale(100.f, 18.f);
	mRalseiName->SetPivot(0.5f, 0.5f);

	// 랄세이 HP
	mRalseiHP = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiHP->SetTexture("RalseiHP", TEXT("Texture/UI/letter/spr_hpname.png"));
	mRalseiHP->SetWorldPos(439.f, -150.f);
	mRalseiHP->SetWorldScale(26.f, 16.f);
	mRalseiHP->SetPivot(0.5f, 0.5f);

	// 랄세이 HPBar Back
	mRalseiHPBarBack = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiHPBarBack->SetTexture("RalseiHPBarBack", TEXT("Texture/UI/healthbar/healthbar_black.png"));
	mRalseiHPBarBack->SetWorldPos(539.f, -148.f);
	mRalseiHPBarBack->SetWorldScale(150.f, 12.f);
	mRalseiHPBarBack->SetPivot(0.5f, 0.5f);

	// 랄세이 HPBar
	mRalseiHPBar = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiHPBar->SetTexture("RalseiHPBar", TEXT("Texture/UI/healthbar/healthbar.png"));
	mRalseiHPBar->SetWorldPos(539.f, -148.f);
	mRalseiHPBar->SetWorldScale(150.f, 12.f);
	mRalseiHPBar->SetPivot(0.5f, 0.5f);

	// 랄세이 최대 HP 70
	// 7
	mRalseiHP7 = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiHP7->SetTexture("RalseiHP7", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_7.png"));
	mRalseiHP7->SetWorldPos(596.f, -132.f);
	mRalseiHP7->SetWorldScale(10.f, 12.f);
	mRalseiHP7->SetPivot(0.5f, 0.5f);

	// 0
	mRalseiHP0 = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiHP0->SetTexture("RalseiHP0", TEXT("Texture/UI/letter/spr_hpNumber/spr_numbersfontsmall_ch1_0.png"));
	mRalseiHP0->SetWorldPos(609.f, -132.f);
	mRalseiHP0->SetWorldScale(10.f, 12.f);
	mRalseiHP0->SetPivot(0.5f, 0.5f);

	// 랄세이 슬래쉬
	mRalseiSlash = CreateComponent<CSpriteComponent>("BattleUI2");
	mRalseiSlash->SetTexture("RalseiSlash", TEXT("Texture/UI/letter/spr_hpslash.png"));
	mRalseiSlash->SetWorldPos(549.f, -132.f);
	mRalseiSlash->SetWorldScale(24.f, 16.f);
	mRalseiSlash->SetPivot(0.5f, 0.5f);
	/////////////////////////////////////랄세이/////////////////////////////////////////

	return true;
}

void CBattleHUD::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	// 크리스
	FVector3D Pos = mKrisBlackBlock->GetWorldPosition();
	FVector3D Dir = mKrisBlackBlock->GetAxis(EAxis::Y);

	FVector3D Pos2 = mKrisIcon->GetWorldPosition();
	FVector3D Dir2 = mKrisIcon->GetAxis(EAxis::Y);

	FVector3D Pos3 = mKrisName->GetWorldPosition();
	FVector3D Dir3 = mKrisName->GetAxis(EAxis::Y);

	FVector3D Pos4 = mKrisHP->GetWorldPosition();
	FVector3D Dir4 = mKrisHP->GetAxis(EAxis::Y);

	FVector3D Pos5 = mKrisHPBarBack->GetWorldPosition();
	FVector3D Dir5 = mKrisHPBarBack->GetAxis(EAxis::Y);

	FVector3D Pos6 = mKrisHPBar->GetWorldPosition();
	FVector3D Dir6 = mKrisHPBar->GetAxis(EAxis::Y);

	FVector3D Pos7 = mKrisHP9->GetWorldPosition();
	FVector3D Dir7 = mKrisHP9->GetAxis(EAxis::Y);

	FVector3D Pos8 = mKrisHP0->GetWorldPosition();
	FVector3D Dir8 = mKrisHP0->GetAxis(EAxis::Y);

	FVector3D Pos9 = mKrisSlash->GetWorldPosition();
	FVector3D Dir9 = mKrisSlash->GetAxis(EAxis::Y);

	if (Pos.y <= -116.7f)
	{
		FVector3D NewPos = Pos + Dir * 350.f * DeltaTime;
		mKrisBlackBlock->SetWorldPos(NewPos);

		FVector3D NewPos2 = Pos2 + Dir2 * 350.f * DeltaTime;
		mKrisIcon->SetWorldPos(NewPos2);

		FVector3D NewPos3 = Pos3 + Dir3 * 350.f * DeltaTime;
		mKrisName->SetWorldPos(NewPos3);

		FVector3D NewPos4 = Pos4 + Dir4 * 350.f * DeltaTime;
		mKrisHP->SetWorldPos(NewPos4);

		FVector3D NewPos5 = Pos5 + Dir5 * 350.f * DeltaTime;
		mKrisHPBarBack->SetWorldPos(NewPos5);

		FVector3D NewPos6 = Pos6 + Dir6 * 350.f * DeltaTime;
		mKrisHPBar->SetWorldPos(NewPos6);

		FVector3D NewPos7 = Pos7 + Dir7 * 350.f * DeltaTime;
		mKrisHP9->SetWorldPos(NewPos7);

		FVector3D NewPos8 = Pos8 + Dir8 * 350.f * DeltaTime;
		mKrisHP0->SetWorldPos(NewPos8);

		FVector3D NewPos9 = Pos9 + Dir9 * 350.f * DeltaTime;
		mKrisSlash->SetWorldPos(NewPos9);
	}
}
