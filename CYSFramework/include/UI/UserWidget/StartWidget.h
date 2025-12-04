#pragma once
#include "UserWidget.h"

class CStartWidget : public CUserWidget
{
	friend class CSceneUIManager;

protected:
	CStartWidget();
	virtual ~CStartWidget();

protected:
	CSharedPtr<class CButton> mButton;
	CSharedPtr<class CImage> mBackGround;
	CSharedPtr<class CImage> mLogo;
	CSharedPtr<class CImage> mBackGroundAnim;

	class CAnimation2D* mAnimation = nullptr;

public:
	virtual bool Init();

private:
	void StartButtonClick();
};

