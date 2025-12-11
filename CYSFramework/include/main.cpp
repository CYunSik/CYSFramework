#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "GameManager.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    _CrtSetBreakAlloc(160);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    char* a = new char[1024];
    // 할당된 메모리를 해제하지 않음으로써 메모리 누수 발생
    std::cout << "Memory leak example" << std::endl;
    // 프로그램 종료 전 메모리 누수를 강제로 확인합니다.
    _CrtDumpMemoryLeaks();

    if (!CGameManager::GetInst()->Init(hInstance))
    {
        return 0;
    }
    CGameManager::GetInst()->Run();

    delete a;

    return 0;
}