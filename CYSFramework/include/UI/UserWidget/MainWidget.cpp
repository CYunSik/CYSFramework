#include "MainWidget.h"

#include "../Common/Button.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"

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
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TextButton");

	mButton->SetPos(100.f, 100.f);
	mButton->SetSize(100.f, 100.f);
	mButton->SetPivot(FVector2D(0.5f, 0.5f));

	AddWidget(mButton);

	return true;
}
