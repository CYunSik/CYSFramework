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
	float mClearColor[4] = {1.f, 0.f, 1.f, 1.f};

	float mBulletCoolDown = 1.0f;		// 1초
	float mBulletTimer = 0.0f;
	bool mShoot = false;

	// 사각형 하나 띄어보기
	// FRect mRC = { 100, 100, 200, 200 };
	// 플레이어 위치
	FVector2D mPlayerPos = { 150.f, 150.f };
	// 플레이어 크기
	FVector2D mPlayerSize = { 100.f, 100.f };
	// 플레이어 총알 리스트
	std::list<FBullet> mBulletList;	// 여기에 총알을 넣어줄 것이다.
	
	// 적
	// FRect mEnemy = { 1000, 500, 1100, 600 };
	// 적 위치
	FVector2D mEnemyPos = { 1100.f, 500.f };
	// 적 크기
	FVector2D mEnemySize = { 100.f, 100.f };
	float mEnemyDir = 1.f;

	std::list<FBullet> mEnemyBulletList;
	float mFireTime = 1.f;
	float mFireAccTime = 0.f;

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();

	void Input(float DeltaTime);				// 입력
	void Update(float DeltaTime);				// 게임 로직
	void PostUpdate(float DeltaTime);			// 업데이트 이후 로직
	void Collision(float DeltaTime);			// 충돌
	void PostCollisionUpdate(float DeltaTime);	// 충돌 후 업데이트
	void Render(float DeltaTime);				// 화면에 그려주기

private:
	ATOM RegisterWindowClass();
	bool Create();

	// 전역함수로 넣어야하기때문에
	// static을 추가해준다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLETON(CGameManager)
};

