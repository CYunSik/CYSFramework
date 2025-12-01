#pragma once
#include "WindowWidget.h"

class CMainWidget : public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CMainWidget();
	virtual ~CMainWidget();

protected:
	CSharedPtr<class CButton> mButtonAttack;
	CSharedPtr<class CButton> mButtonAct;
	CSharedPtr<class CButton> mButtonItem;
	CSharedPtr<class CButton> mButtonSpare;
	CSharedPtr<class CButton> mButtonDefend;

public:


public:
	virtual bool Init();
};

