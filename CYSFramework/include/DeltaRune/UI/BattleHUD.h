#pragma once
#include "../../Object/SceneObject.h"

class CBattleHUD : public CSceneObject
{
	friend class CScene;

protected:
	CBattleHUD();
	CBattleHUD(const CBattleHUD& Obj);
	CBattleHUD(CBattleHUD&& Obj);
	virtual ~CBattleHUD();

protected:
	// 맨 밑 UI창
	CSharedPtr<class CSpriteComponent> mBattleUIDown;
	// 각 캐릭터 상태창 기본 검은 배경
	CSharedPtr<class CSpriteComponent> mBlackBG1;
	CSharedPtr<class CSpriteComponent> mBlackBG2;
	CSharedPtr<class CSpriteComponent> mBlackBG3;
	// TP 글씨
	CSharedPtr<class CSpriteComponent> mTP;
	// TP 바
	CSharedPtr<class CSpriteComponent> mTPBar;
	// TP 빈 바
	CSharedPtr<class CSpriteComponent> mTPBarEmptyFill;
	// TP 프로세스바
	CSharedPtr<class CSpriteComponent> mTPBarFill;

	// 크리스
	CSharedPtr<class CSpriteComponent> mKrisBlackBlock;
	CSharedPtr<class CSpriteComponent> mKrisIcon;
	CSharedPtr<class CSpriteComponent> mKrisName;
	CSharedPtr<class CSpriteComponent> mKrisHP;
	CSharedPtr<class CSpriteComponent> mKrisHPBarBack;
	CSharedPtr<class CSpriteComponent> mKrisHPBar;
	CSharedPtr<class CSpriteComponent> mKrisHP9;
	CSharedPtr<class CSpriteComponent> mKrisHP0;
	CSharedPtr<class CSpriteComponent> mKrisSlash;

	// 수지
	CSharedPtr<class CSpriteComponent> mSusieBlackBlock;
	CSharedPtr<class CSpriteComponent> mSusieIcon;
	CSharedPtr<class CSpriteComponent> mSusieName;
	CSharedPtr<class CSpriteComponent> mSusieHP;
	CSharedPtr<class CSpriteComponent> mSusieHPBarBack;
	CSharedPtr<class CSpriteComponent> mSusieHPBar;
	CSharedPtr<class CSpriteComponent> mSusieHP100;
	CSharedPtr<class CSpriteComponent> mSusieHP10;
	CSharedPtr<class CSpriteComponent> mSusieHP0;
	CSharedPtr<class CSpriteComponent> mSusieSlash;

	// 랄세이
	CSharedPtr<class CSpriteComponent> mRalseiBlackBlock;
	CSharedPtr<class CSpriteComponent> mRalseiIcon;
	CSharedPtr<class CSpriteComponent> mRalseiName;
	CSharedPtr<class CSpriteComponent> mRalseiHP;
	CSharedPtr<class CSpriteComponent> mRalseiHPBarBack;
	CSharedPtr<class CSpriteComponent> mRalseiHPBar;
	CSharedPtr<class CSpriteComponent> mRalseiHP7;
	CSharedPtr<class CSpriteComponent> mRalseiHP0;
	CSharedPtr<class CSpriteComponent> mRalseiSlash;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

