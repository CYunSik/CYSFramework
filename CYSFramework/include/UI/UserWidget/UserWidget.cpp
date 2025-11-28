#include "UserWidget.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

bool CUserWidget::Init()
{
	return CWidget::Init();
}

void CUserWidget::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CUserWidget::Render()
{
	CWidget::Render();
}

bool CUserWidget::CollisionMouse(const FVector2D& MousePos)
{
	return CWidget::CollisionMouse(MousePos);
}
