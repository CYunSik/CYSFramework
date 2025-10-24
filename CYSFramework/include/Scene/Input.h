#pragma once

#include "../GameInfo.h"

// 다이렉트 전용 입력 헤더를 가져올 것이다.
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")

enum class EInputSystem_Type
{
	DInput,
	Window
};

class CInput
{
	friend class CScene;

private:
	CInput();
	~CInput();

private:
	HINSTANCE mhInst;
	HWND mhWnd;

	// 디바이스 입력
	// 디바이스 같은 녀석인데 디바이스는 아니다.
	// IDirectInput8 객체로부터 내가 원하는 장치의 디바이스를 얻어온다.
	// 키보드 디바이스, 마우스 디바이스, 게임패드 디바이스 등등
	IDirectInput8* mInput = nullptr;
	IDirectInputDevice8* mKeyboard = nullptr;	// 키보드 디바이스
	IDirectInputDevice8* mMouse = nullptr;		// 마우스 디바이스

	EInputSystem_Type mInputType = EInputSystem_Type::DInput;

private:
	bool InitInput();


public:
	bool Init();
	void Update(float DeltaTime);
};

