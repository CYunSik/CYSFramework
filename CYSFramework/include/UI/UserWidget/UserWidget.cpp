#include "UserWidget.h"

#include "../../Scene/Input.h"
#include "../../Scene/Scene.h"
#include "../Common/Button.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

bool CUserWidget::Init()
{
	CWidget::Init();

	CInput* Input = mScene->GetInput();

	// 왼쪽 선택
	Input->AddBindKey("UI_Left", VK_LEFT);
	Input->AddBindFunction("UI_Left", EInputType::Down, this, &CUserWidget::OnLeft);

	// 오른쪽 선택
	Input->AddBindKey("UI_Right", VK_RIGHT);
	Input->AddBindFunction("UI_Right", EInputType::Down, this, &CUserWidget::OnRight);

	// Z키로 확인
	Input->AddBindKey("UI_Confirm", 'Z');
	Input->AddBindFunction("UI_Confirm", EInputType::Down, this, &CUserWidget::OnConfirm);

	// X키로 취소 뒤로가기
	Input->AddBindKey("UI_Cancel", 'X');
	Input->AddBindFunction("UI_Cancel", EInputType::Down, this, &CUserWidget::OnCancel);

	return true;
}

void CUserWidget::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		// Active
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CUserWidget::Render()
{
	CWidget::Render();

	// 그려줄 위젯 정렬
	if (mWidgetList.size() >= 2)
	{
		// vector
		// Z오더는 숫자가 클수록 나중에 그려진다.
		// UI는 나중에 그려지는애가 가장 맨 위에 그려진다.
		std::sort(mWidgetList.begin(), mWidgetList.end(), CUserWidget::SortRender);
	}

	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		// Active
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// UI 그려줘
		(*iter)->Render();
		++iter;
	}
}

void CUserWidget::Render(const FVector3D& Pos)
{
	CWidget::Render(Pos);

	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}
		// UI 그려줘
		(*iter)->Render(Pos);
		++iter;
	}
}

bool CUserWidget::CollisionMouse(CWidget** Result, const FVector2D& MousePos)
{
	// 충돌 할것들 정렬 해준다.
	if (mWidgetList.size() >= 2)
	{
		std::sort(mWidgetList.begin(), mWidgetList.end(), CUserWidget::SortCollision);
	}

	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		if ((*iter)->CollisionMouse(Result, MousePos))
		{
			return true;
		}
		++iter;
	}

	return false;
}

bool CUserWidget::SortCollision(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();
}

bool CUserWidget::SortRender(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}

void CUserWidget::OnLeft(float DeltaTime)
{
	MoveSelection(-1);
}

void CUserWidget::OnRight(float DeltaTime)
{
	MoveSelection(1);
}

void CUserWidget::OnConfirm(float DeltaTime)
{
	ActivateCurrentButton();
}

void CUserWidget::OnCancel(float DeltaTime)
{
	// 뒤로가기 처리
}

void CUserWidget::MoveSelection(int Offset)
{
	int Count = (int)mWidgetList.size();

	if (Count == 0)
	{
		return;
	}

	// 이전 선택 해제
	if (mSelectedIndex >= 0 && mSelectedIndex < Count)
	{
		CButton* PrevBtn = dynamic_cast<CButton*>(mWidgetList[mSelectedIndex].Get());
		if (PrevBtn)
		{
			PrevBtn->SetKeyboardHovered(false);
		}
	}

	// 새로운 선택 후보 검색
	int NewIndex = mSelectedIndex;

	for (int i = 0; i < Count; ++i)
	{
		NewIndex += Offset;

		if (NewIndex < 0)
		{
			NewIndex = Count - 1;
		}
		else if (NewIndex >= Count)
		{
			NewIndex = 0;
		}

		CButton* Btn = dynamic_cast<CButton*>(mWidgetList[NewIndex].Get());
		if (Btn && Btn->IsEnable() && Btn->IsActive())
		{
			mSelectedIndex = NewIndex;
			Btn->SetKeyboardHovered(true);
			return;
		}
	}

	mSelectedIndex = -1;
}


void CUserWidget::ActivateCurrentButton()
{
	if (mSelectedIndex < 0 || mSelectedIndex >= (int)mWidgetList.size())
	{
		return;
	}

	CButton* Btn = dynamic_cast<CButton*>(mWidgetList[mSelectedIndex].Get());
	if (!Btn)
	{
		return;
	}

	Btn->CallClickEvent();
}