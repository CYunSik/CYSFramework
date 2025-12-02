#pragma once

#include "GameInfo.h"

class CGameManager
{

private:
	static bool mLoop;
	HINSTANCE mhInst = 0;
	HWND mhWnd = 0;
	HDC mhDC = 0;
	TCHAR mClassName[256] = {};
	TCHAR mTitleName[256] = {};

	// 배경색
	// 개발중일때는 검정색 비추
	float mClearColor[4] = { 0.f, 1.f, 1.f, 1.f };

public:
	HINSTANCE GetWindowInstance() const
	{
		return mhInst;
	}

	HWND GetWindowHandle()
	{
		return mhWnd;
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();

	void Input(float DeltaTime);				// 입력
	void Update(float DeltaTime);				// 게임 로직
	void Collision(float DeltaTime);			// 충돌
	void Render(float DeltaTime);				// 화면에 그려주기

private:
	ATOM RegisterWindowClass();
	bool Create();

	// 전역함수로 넣어야하기때문에
	// static을 추가해준다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLETON(CGameManager)
};

