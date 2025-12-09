#pragma once
#include "../Widget.h"

class CUserWidget : public CWidget
{
	friend class CSceneUIManager;

protected:
	CUserWidget();
	virtual ~CUserWidget();

protected:
	// 위젯들 목록
	std::vector<CSharedPtr<CWidget>> mWidgetList;

protected:
	// 버튼 인덱스
	int mSelectedIndex = -1;

public:
	void AddWidget(CWidget* Widget)
	{
		Widget->SetParent(this);
		mWidgetList.emplace_back(Widget);
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
	virtual void Render(const FVector3D& Pos);
	virtual bool CollisionMouse(CWidget** Result, const FVector2D& MousePos);

	static bool SortCollision(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest);
	static bool SortRender(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest);

public:
	void OnLeft(float DeltaTime);
	void OnRight(float DeltaTime);
	void OnConfirm(float DeltaTime);
	void OnCancel(float DeltaTime);
		
	void MoveSelection(int Offset);
	void ActivateCurrentButton();

};

