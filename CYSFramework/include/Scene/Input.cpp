#include "Input.h"
#include "../GameManager.h"
#include "../Device.h"

CInput::CInput()
{
}

CInput::~CInput()
{
	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		SAFE_RELEASE(mKeyboard);
	}

	if (mMouse)
	{
		mMouse->Unacquire();
		SAFE_RELEASE(mMouse);
	}
}

bool CInput::InitInput()
{
	// 키보드
	// 디바이스 객체 만든거고
	// 키보드 장치를 얻어온건 아니다!
	if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
	{
		return false;
	}

	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	// 창모드냐 아니냐에 따라서 기본 설정값이 달라진다.
	// DISCL_FOREGROUND		: 활성화 시에만 키를 입력받게 한다.
	// DISCL_BACKGROUND		: 백그라운드에서도 사용할 수 있게 설정한다.
	//						  주의사항 : 창모드에서는 BACKGROUND로 설정해야한다.
	// DISCL_EXCLUSIVE		: 입력 디바이스를 독점모드로 설정한다.
	// DISCL_NONEXCLUSIVE	: 입력 디바이스를 비독점모드로 설정한다.

	if (CDevice::GetInst()->GetWindowMod()) // 창모드
	{
		if(FAILED(mKeyboard->SetCooperativeLevel(mhWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			return false;
		}
	}
	else
	{
		if (FAILED(mKeyboard->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			return false;
		}
	}

	// 키보드 장치를 획득한다.
	if (FAILED(mKeyboard->Acquire()))
	{
		return false;
	}

	///////////////////////// 마우스
	if (FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
	{
		return false;
	}

	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}

	if (CDevice::GetInst()->GetWindowMod()) // 창모드
	{
		if (FAILED(mMouse->SetCooperativeLevel(mhWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		{
			return false;
		}
	}
	else
	{
		if (FAILED(mMouse->SetCooperativeLevel(mhWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			return false;
		}
	}

	// 마우스 장치를 획득한다.
	if (FAILED(mMouse->Acquire()))
	{
		return false;
	}

	return true;
}

bool CInput::Init()
{
	// 입력장치 초기화하는데
	// 윈도우의 Inst, hWnd가 필요하다.
	mhInst = CGameManager::GetInst()->GetWindowInstance();
	mhWnd = CGameManager::GetInst()->GetWindowHandle();

	if (FAILED(DirectInput8Create(mhInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, nullptr)))
	{
		// 다이렉트의 입력을 초기화 못하면
		// 윈도우의 입력을 사용하겠다.
		mInputType = EInputSystem_Type::Window;
	}

	if (mInputType == EInputSystem_Type::DInput)
	{
		// 다이렉트 인풋이 사용 가능하면 장치를 여기서 얻어올 것이다.
		if (!InitInput())
		{
			return false;
		}
	}

	return true;
}

void CInput::Update(float DeltaTime)
{

}