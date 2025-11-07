#include "GameManager.h"

// 리소스 정보
#include "resource.h"

// 매니져 헤더
#include "Share/Timer.h"
#include "Share/Log.h"
#include "Device.h"

#include "Asset/AssetManager.h"
#include "Asset/Mesh/MeshManager.h"
#include "Asset/Mesh/Mesh.h"

#include "Shader/ShaderManager.h"
#include "Shader/Shader.h"

#include "Shader/TransformCBuffer.h"
#include "Scene/SceneManager.h"

#include "ProfileManager.h"

#include "time.h"

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
	CLog::Destroy();

	// DC 반납
	ReleaseDC(mhWnd, mhDC);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	mhInst = hInst;

	lstrcpy(mClassName, TEXT("CYSFramework"));
	lstrcpy(mTitleName, TEXT("CYSFramework"));

	RegisterWindowClass();

	if (!Create())
	{
		return false;
	}

	if (!CLog::Init())
	{
		return false;
	}

	// DC : 디바이스 컨텍스트
	// 주의사항 -> GetDC 꼭 해제해줘야한다.
	mhDC = GetDC(mhWnd);

	///////// 게임 초기화
	if (!CDevice::GetInst()->Init(mhWnd, 1280, 720, true))
	{
		return false;
	}

	if (!CAssetManager::GetInst()->Init())
	{
		return false;
	}

	if (!CShaderManager::GetInst()->Init())
	{
		return false;
	}

	// Collision Profile 매니져 초기화
	if (!CProfileManager::GetInst()->Init())
	{
		return false;
	}

	// 타이머 초기화
	CTimer::Init();
	srand((unsigned int)time(0));

	// 씬매니저 초기화
	if (!CSceneManager::GetInst()->Init())
	{
		return false;
	}

	return true;
}

int CGameManager::Run()
{
	MSG msg = {};

	// *PeekMessage : 메시지큐의 메시지를 얻어오는 함수이다.
	// *이 함수는 메시지큐가 비어있을 경우 바로 빠져나오면서 0을 반환한다.
	// *메시지큐에 메시지가 있다면 해당 메시지를 가져온다.
	while (mLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// *메시지를 처리하는 함수
			// *키보드 입력 메시지가 발생할 경우 동작한다.
			// *WM_KEYDOWN, WM_KEYUP 등 메시지가 발생하면 호출된다.
			TranslateMessage(&msg);
			// *WndProc 함수로 메시지를 전달해주는 함수다.
			DispatchMessage(&msg);
		}
		else
		{
			// *윈도우 데드타임
			// *여기서부터 게임을 만들 수 있게 된다.
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CGameManager::Logic()
{
	// DeltaTime : 프레임과 프레임 사이 (한번 갔다 돌아오는 시간)
	float DeltaTime = CTimer::Update();

	Input(DeltaTime);				// 입력

	Update(DeltaTime);				// 정보 갱신

	Collision(DeltaTime);

	Render(DeltaTime);				// 그려주기
}

void CGameManager::Input(float DeltaTime)
{
	CSceneManager::GetInst()->Input(DeltaTime);
}

void CGameManager::Update(float DeltaTime)
{
	CSceneManager::GetInst()->Update(DeltaTime);

	//CLog::PrintLog("GameManger Update", ELogPrintType::All);

	//static bool push = false;

	//if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	//{
	//	push = true;
	//}
	//else if (push)
	//{
	//	push = false;
	//	CLog::SaveLog();
	//}
}


void CGameManager::Collision(float DeltaTime)
{
	CSceneManager::GetInst()->Collision(DeltaTime);
}

void CGameManager::Render(float DeltaTime)
{
	// 새로운 도화지 준비
	CDevice::GetInst()->ClearBackBuffer(mClearColor);
	CDevice::GetInst()->ClearDepthStencill(1.f, 0);
	CDevice::GetInst()->SetTarget();

	// 준비된 도화지에 출력
	CSceneManager::GetInst()->Render();

	//static CTransformCBuffer buffer;
	//static FVector3D Pos, Rot;

	//Pos.z = 5.f;

	//// 임시로 키입력
	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	Pos.y += 0.5f * DeltaTime;
	//}
	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	Pos.y -= 0.5f * DeltaTime;
	//}
	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	Rot.z += 90.f * DeltaTime;
	//}
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	Rot.z -= 90.f * DeltaTime;
	//}
	//
	//buffer.Init();

	//FMatrix matWorld, matProj;
	//FMatrix matScale, matRot, matTranslate;

	//matScale.Scaling(5.f, 5.f, 1.f);
	//matRot.Rotation(Rot);
	//matTranslate.Translation(Pos);

	//matWorld = matScale * matRot * matTranslate;
	//// 원근 투영 행렬을 만들어준다.
	//// 시야각, 종횡비, 근평원, 원평원
	//matProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90.f), 1280.f / 720.f, 0.5f, 1000.f);

	//buffer.SetWorldMatrix(matWorld);
	//buffer.SetProjMatrix(matProj);
	//buffer.UpdateBuffer();

	//CSharedPtr<CShader> Shader = CShaderManager::GetInst()->FindShader("ColorMeshShader");
	//CSharedPtr<CMesh> Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("CenterRect");

	//Shader->SetShader();
	//Mesh->Render();

	// 도화지에 다 그렸으면 출력할거다.
	CDevice::GetInst()->Render();

}

ATOM CGameManager::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	// *윈도우 클래스 구조체의 크기를 나타낸다. 반드시 지정되어야 한다.
	wcex.cbSize = sizeof(WNDCLASSEX);

	// *윈도우 클래스의 스타일을 지정한다.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// *메시지를 처리하는 함수의 포인터이다.
	wcex.lpfnWndProc = WndProc;

	// *윈도우 클래스에 대한 추가 메모리를 지정한다.
	wcex.cbClsExtra = 0;
	// *윈도우 인스턴스에 대한 추가 메모리를 지정한다.
	wcex.cbWndExtra = 0;

	// *운영체제에서 부여해준 HINSTANCE를 지정해준다.
	wcex.hInstance = mhInst;

	// *실행파일 아이콘을 지정한다.
	// 솔루션탐색기 - 리소스 파일 - 우클릭 - 추가 - 리소스
	wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IDI_ICON2));

	// *커서모양
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// *클라이언트 영역의 색상을 지정해준다.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// *윈도우 메뉴를 지정해준다.
	// wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY20251013);
	// *0을 넣으면 메뉴가 없는 윈도우가 된다.
	wcex.lpszMenuName = 0;

	// *윈도우 클래스의 이름을 지정한다.
	wcex.lpszClassName = mClassName;

	// *타이틀바 왼쪽위 아이콘을 의미한다.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	// *위에서 설정한 윈도우 클래스를 등록한다.
	return RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
	// *잘못된 생성일 경우 0을 반환한다.
	mhWnd = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1280, 720, nullptr, nullptr, mhInst, nullptr);

	if (!mhWnd)
	{
		return FALSE;
	}

	// 위의 CreateWindowW 타이틀바, 메뉴바 등의 크기가 모두 합쳐진 크기로 지정된다.
	// 그래서 윈도우 클라이언트 영역을 다시 계산해서 윈도우창을 재조정한다.
	RECT WindowRC = { 0, 0, 1280, 720 };
	// 클라이언트 영역이 1280, 720이 되도록 윈도우 크기를 재조정한다.
	AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(mhWnd, HWND_TOPMOST, 100, 100, WindowRC.right - WindowRC.left, WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);

	// *위에서 윈도우 창을 만들었다면 이제 ShowWindow 함수를 이용해서 창을 보여줄지 숨길지 결정한다.
	// ShowWindow(hWnd, nCmdShow);
	ShowWindow(mhWnd, SW_SHOW);
	// ShowWindow(hWnd, SW_MAXIMIZE);

	// *클라이언트 영역을 강제로 다시 그리게 요청해주는 함수이다.
	// *처음 생성시나 특정상황에 창을 다시 그려야 할때 호출된다.
	UpdateWindow(mhWnd);

	return TRUE;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//case WM_PAINT:
		//{
		//	PAINTSTRUCT ps;
		//	// *hdc 화면에 그릴때 필요한 것
		//	// *hinstance, hwnd, hdc 이런게 있구나
		//	// *함수에서 원하는 핸들을 넣어주면 된다. 
		//	// *hdc를 이용해서 화면에 무언가 그릴 수 있게 된다.
		//	HDC hdc = BeginPaint(hWnd, &ps);
		//	// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		//	// *위가 Y- 아래가 Y+


		//	EndPaint(hWnd, &ps);
		//}
		break;

	case WM_SYSKEYDOWN:
		break;
	case WM_DESTROY:
		mLoop = false; // *윈도우를 종료하게되면 루프를 종료해준다.
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
