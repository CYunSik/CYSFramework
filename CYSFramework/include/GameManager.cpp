#include "GameManager.h"

// 리소스 정보
#include "resource.h"

// 매니져 헤더
#include "Share/Timer.h"

#include "Device.h"

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
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

	// DC : 디바이스 컨텍스트
	// 주의사항 -> GetDC 꼭 해제해줘야한다.
	mhDC = GetDC(mhWnd);

	///////// 게임 초기화
	if (!CDevice::GetInst()->Init(mhWnd, 1600, 800, true))
	{
		return false;
	}

	CTimer::Init();


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

	PostUpdate(DeltaTime);

	Collision(DeltaTime);

	PostCollisionUpdate(DeltaTime);

	Render(DeltaTime);				// 그려주기
}

void CGameManager::Input(float DeltaTime)
{
	// GetAsyncKeyState 이걸 통해서 키 입력을 확인할 수 있다.
	FVector2D PlayerMoveDir = { 0.f, 0.f };

	// W A S D 이동
	if (GetAsyncKeyState('W') & 0x8000)
	{
		// W키가 눌려있음
		//mRC.Top -= 400.f * DeltaTime;
		//mRC.Bottom -= 400.f * DeltaTime;

		// mPlayerPos.y -= 400.f * DeltaTime;
		PlayerMoveDir.y -= 1.f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		// S키가 눌려있음
		//mRC.Top += 400.f * DeltaTime;
		//mRC.Bottom += 400.f * DeltaTime;

		// mPlayerPos.y += 400.f * DeltaTime;
		PlayerMoveDir.y += 1.f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		// A키가 눌려있음
		//mRC.Left -= 400.f * DeltaTime;
		//mRC.Right -= 400.f * DeltaTime;

		// mPlayerPos.x -= 400.f * DeltaTime;
		PlayerMoveDir.x -= 1.f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		// D키가 눌려있음
		//mRC.Left += 400.f * DeltaTime;
		//mRC.Right += 400.f * DeltaTime;

		// mPlayerPos.x += 400.f * DeltaTime;
		PlayerMoveDir.x += 1.f;
	}

	PlayerMoveDir.Normalize();
	mPlayerPos += PlayerMoveDir * 400.f * DeltaTime;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			Bullet.MoveDir = FVector2D(1.f, 0.f);
			Bullet.Distance = 1000;

			mBulletList.push_back(Bullet);
		}
	}

	// 플레이어 스킬
	// 산탄
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			FBullet Bullet;

			for (float i = -0.5f; i < 0.5f; i += 0.2f)
			{
				Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
				Bullet.Pos.y = mPlayerPos.y;

				Bullet.Size = FVector2D(50.f, 50.f);
				Bullet.MoveDir = FVector2D(1.f, i);
				Bullet.Distance = 1000;

				mBulletList.push_back(Bullet);
			}
		}
	}
	// 8방향
	if (GetAsyncKeyState('2') & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			std::vector<BulletInfo> DirOffSet =
			{
				{ FVector2D(0.f, -1.f), FVector2D(0.f, -70.f) },		// 위
				{ FVector2D(0.f, 1.f), FVector2D(0.f, 70.f) },			// 아래
				{ FVector2D(-1.f, 0.f), FVector2D(-70.f, 0.f) },		// 왼쪽
				{ FVector2D(1.f, 0.f), FVector2D(70.f, 0.f) },			// 오른쪽
				{ FVector2D(-1.f, -1.f), FVector2D(-70.f, -70.f) },		// 왼쪽 대각선
				{ FVector2D(1.f, -1.f), FVector2D(70.f, -70.f) },		// 오른쪽 대각선
				{ FVector2D(-1.f, 1.f), FVector2D(-70.f, 70.f) },		// 왼쪽 아래 대각선
				{ FVector2D(1.f, 1.f), FVector2D(70.f, 70.f) },			// 오른쪽 아래 대각선
			};

			FBullet Bullet;

			for (const BulletInfo& info : DirOffSet)
			{
				Bullet.Pos = mPlayerPos + info.OffSet;

				Bullet.Size = FVector2D(50.f, 50.f);
				Bullet.MoveDir = info.Dir;
				Bullet.MoveDir.Normalize();
				Bullet.Distance = 1000;

				mBulletList.push_back(Bullet);
			}
		}
	}
	// 총알 튕기기
	if (GetAsyncKeyState('3') & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			Bullet.MoveDir = FVector2D(1.f, -1.f);
			Bullet.MoveDir.Normalize();
			Bullet.Distance = FLT_MAX;
			Bullet.Option = EBulletOption::Bound;

			mBulletList.push_back(Bullet);
		}
	}
	// 물결 총알
	if (GetAsyncKeyState('4') & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			Bullet.MoveDir = FVector2D(0.5f, 0.f);
			Bullet.MoveDir.Normalize();
			Bullet.Distance = FLT_MAX;
			Bullet.Option = EBulletOption::Wave;

			mBulletList.push_back(Bullet);
		}
	}
	// 나선형 총알
	if (GetAsyncKeyState('5') & 0x8000)
	{
		if (mBulletTimer >= mBulletCoolDown)
		{
			mBulletTimer = 0.f;

			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			Bullet.MoveDir = FVector2D(0.5f, 0.f);
			Bullet.MoveDir.Normalize();
			Bullet.Distance = FLT_MAX;
			Bullet.Option = EBulletOption::Storm;

			mBulletList.push_back(Bullet);
		}
	}


}

void CGameManager::Update(float DeltaTime)
{
	Sleep(12);

	InvalidateRect(mhWnd, NULL, TRUE); // TRUE → 이전 프레임 지움
	UpdateWindow(mhWnd);

	// 매번 갱신해야 하는 것들
	mBulletTimer += DeltaTime;
	std::list<FBullet>::iterator iter = mBulletList.begin();
	std::list<FBullet>::iterator iterEnd = mBulletList.end();

	for (; iter != iterEnd;)
	{
		FBullet& Bullet = *iter;
		// 기본 위치 + 원하는 방향 * 원하는 속도 * 델타 타임;
		FVector2D Move = Bullet.MoveDir * 500.f * DeltaTime;
		Bullet.Pos += Move;

		// 거리만큼만 이동
		float Dist = Move.Length();	// 총알이 현재 이동한 거리
		Bullet.Distance -= Dist;
		// 거리가 멀어지면 삭제
		if (Bullet.Distance <= 0.f)
		{
			iter = mBulletList.erase(iter);
			iterEnd = mBulletList.end();
			continue;
		}
		// 화면 밖으로 나갔을때 삭제
		if (Bullet.Pos.x - Bullet.Size.x >= 1600.f ||
			Bullet.Pos.x + Bullet.Size.x <= 0.f ||
			Bullet.Pos.y - Bullet.Size.y >= 800.f ||
			Bullet.Pos.y + Bullet.Size.y <= 0.f)
		{
			iter = mBulletList.erase(iter);
			iterEnd = mBulletList.end();
			continue;
		}
		
		if (Bullet.Option == EBulletOption::Bound)
		{
			FVector2D Normal;
			// 벽에 부딪혔는지 판단
			if (Bullet.Pos.x - Bullet.Size.x / 2.f <= 0.f) // 왼쪽 벽
			{
				Bullet.MoveDir.x = 1.f;
			}
			else if (Bullet.Pos.x + Bullet.Size.x / 2.f >= 1600.f)
			{
				Bullet.MoveDir.x = -1;
			}
			else if (Bullet.Pos.y - Bullet.Size.y / 2.f <= 0.f) // 위 벽
			{
				Bullet.MoveDir.y = 1.f;
			}
			else if (Bullet.Pos.y + Bullet.Size.y / 2.f >= 800.f) // 아래 벽
			{
				Bullet.MoveDir.y = -1.f;
			}
		}

		if (Bullet.Option == EBulletOption::Wave)
		{
			Bullet.AccTime += DeltaTime;
			Bullet.Pos.y += 10 * sinf(20 * Bullet.AccTime);
		}

		if (Bullet.Option == EBulletOption::Storm)
		{
			Bullet.AccTime += DeltaTime;

			float AngleSpeed = 3.f;     // 회전 속도
			float RadiusSpeed = 100.f;  // 반지름 증가 속도

			float Angle = AngleSpeed * Bullet.AccTime;
			float Radius = RadiusSpeed * Bullet.AccTime;

			Bullet.Pos.x = mPlayerPos.x + cosf(Angle) * Radius;
			Bullet.Pos.y = mPlayerPos.y + sinf(Angle) * Radius;
		}

		++iter;
	}


	//////////// 적
	// 적 이동
	mEnemyPos.y += mEnemyDir * 300 * DeltaTime;

	if (mEnemyPos.y + mEnemySize.y / 2.f >= 800) // 화면 아래 닿음
	{
		mEnemyPos.y = 750.f;
		mEnemyDir = -1.f;
	}
	else if (mEnemyPos.y - mEnemySize.y / 2.f <= 0) // 화면 위에 닿음
	{
		mEnemyPos.y = 50.f;
		mEnemyDir = 1.f;
	}

	// 적 총알
	mFireAccTime += DeltaTime;	// 시간을 누적한다.
	if (mFireAccTime >= mFireTime)
	{
		mFireAccTime -= mFireTime;

		FBullet Bullet1;

		Bullet1.Pos.x = mEnemyPos.x - mEnemySize.x / 2.f - 25.f;
		Bullet1.Pos.y = mEnemyPos.y;

		Bullet1.Size = FVector2D(50.f, 50.f);
		Bullet1.MoveDir = mPlayerPos - mEnemyPos;
		Bullet1.MoveDir.Normalize();
		Bullet1.Distance = 1000;

		mEnemyBulletList.push_back(Bullet1);
	}

	// 적 총알 발사
	std::list<FBullet>::iterator iterEnemy = mEnemyBulletList.begin();
	std::list<FBullet>::iterator iterEndEnemy = mEnemyBulletList.end();

	for (; iterEnemy != iterEndEnemy;)
	{
		FBullet& Bullet1 = *iterEnemy;
		// Bullet1.Pos += Bullet1.MoveDir * 1.f * DeltaTime;
		// 한프레임당 이동량을 구한다.
		FVector2D Move = Bullet1.MoveDir * 500.f * DeltaTime;
		Bullet1.Pos += Move;

		float Dist1 = Move.Length();
		Bullet1.Distance -= Dist1;
		// 거리가 멀어지면 삭제
		if (Bullet1.Distance <= 0.f)
		{
			iterEnemy = mEnemyBulletList.erase(iterEnemy);
			iterEndEnemy = mEnemyBulletList.end();
			continue;
		}
		// 화면 밖으로 나갔을때 삭제
		if (Bullet1.Pos.x - Bullet1.Size.x >= 1600.f ||
			Bullet1.Pos.x + Bullet1.Size.x <= 0.f ||
			Bullet1.Pos.y - Bullet1.Size.y >= 800.f ||
			Bullet1.Pos.y + Bullet1.Size.y <= 0.f)
		{
			iterEnemy = mEnemyBulletList.erase(iterEnemy);
			iterEndEnemy = mEnemyBulletList.end();
			continue;
		}
		++iterEnemy;
	}

}

void CGameManager::PostUpdate(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::PostCollisionUpdate(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
	// 새로운 도화지 준비
	CDevice::GetInst()->ClearBackBuffer(mClearColor);
	CDevice::GetInst()->ClearDepthStencill(1.f, 0);
	CDevice::GetInst()->SetTarget();

	// 준비된 도화지에 출력

	// 도화지에 다 그렸으면 출력할거다.
	CDevice::GetInst()->Render();


	// Rectangle(mhDC, (int)mRC.Left, (int)mRC.Top, (int)mRC.Right, (int)mRC.Bottom);
	Rectangle(mhDC, (int)(mPlayerPos.x - mPlayerSize.x / 2.f),
		(int)(mPlayerPos.y - mPlayerSize.y / 2.f),
		(int)(mPlayerPos.x + mPlayerSize.x / 2.f),
		(int)(mPlayerPos.y + mPlayerSize.y / 2.f));

	std::list<FBullet>::iterator iter = mBulletList.begin();	// 맨 앞을 가르키는 반복자
	std::list<FBullet>::iterator iterEnd = mBulletList.end();	// 마감
	for (; iter != iterEnd; ++iter)
	{
		FBullet& Bullet = *iter;

		Ellipse(mhDC, (int)(Bullet.Pos.x - Bullet.Size.x / 2.f),
			(int)(Bullet.Pos.y - Bullet.Size.y / 2),
			(int)(Bullet.Pos.x + Bullet.Size.x / 2.f),
			(int)(Bullet.Pos.y + Bullet.Size.y / 2));
	}

	// 적 그리기
	// Rectangle(mhDC, (int)mEnemy.Left, (int)mEnemy.Top, (int)mEnemy.Right, (int)mEnemy.Bottom);
	Rectangle(mhDC, (int)(mEnemyPos.x - mEnemySize.x / 2.f),
		(int)(mEnemyPos.y - mEnemySize.y / 2.f),
		(int)(mEnemyPos.x + mEnemySize.x / 2.f),
		(int)(mEnemyPos.y + mEnemySize.y / 2.f));

	// 적 총알 발사
	std::list<FBullet>::iterator iterEnemy = mEnemyBulletList.begin();	// 맨 앞을 가르키는 반복자
	std::list<FBullet>::iterator iterEndEnemy = mEnemyBulletList.end();	// 마감
	for (; iterEnemy != iterEndEnemy; ++iterEnemy)
	{
		FBullet& Bullet1 = *iterEnemy;
		Ellipse(mhDC, (int)(Bullet1.Pos.x - Bullet1.Size.x / 2.f),
			(int)(Bullet1.Pos.y - Bullet1.Size.y / 2),
			(int)(Bullet1.Pos.x + Bullet1.Size.x / 2.f),
			(int)(Bullet1.Pos.y + Bullet1.Size.y / 2));
	}
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
		CW_USEDEFAULT, 0, 1600, 800, nullptr, nullptr, mhInst, nullptr);

	if (!mhWnd)
	{
		return FALSE;
	}

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
	case WM_DESTROY:
		mLoop = false; // *윈도우를 종료하게되면 루프를 종료해준다.
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
