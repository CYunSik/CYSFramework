#pragma once
#include "../../UI/UserWidget/WindowWidget.h"

class CBattleWidget : public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CBattleWidget();
	virtual ~CBattleWidget();

public:
	CSharedPtr<class CButton> mKrisButtonAttack;
	CSharedPtr<class CButton> mKrisButtonAct;
	CSharedPtr<class CButton> mKrisButtonItem;
	CSharedPtr<class CButton> mKrisButtonSpare;
	CSharedPtr<class CButton> mKrisButtonDefend;

	CSharedPtr<class CImage> mRalseiName;

public:
	virtual bool Init();
};

