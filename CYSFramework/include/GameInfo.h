#pragma once

// 미리 컴파일된 헤더
#include <Windows.h>
#include <crtdbg.h>

 // 자료구조 리스트
#include <list>
#include <vector>
#include <map>				// 기본 트리

#include <unordered_map>	// 해쉬 트리

#include <string>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix.h"

#include "Share/SharedPtr.h"

// DX를 사용하기 위한 헤더
#include <d3d11.h>
#include <d3dcompiler.h>

/*
	라이브러리를 가져와서 사용하는 방식이다.
	lib, dll

	lib : 정적 라이브러리
	프로그램 빌드 시점에서 실행파일에 코드가 직접 포함된다.

	dll : 동적 라이브러리
	프로그램 시작되면 그때 메모리에 별도로 로드된다. 런타임중 기능을 불러온다. 프로그램 빌드시 코드가 포함은 안된다.
	dll은 배포할때 dll 파일을 같이 배포해줘야한다.
*/

// .lib를 통해서 DX11 기능을 불러와야 한다.
// 링크를 거는 방법
#pragma comment(lib, "d3d11.lib")			// DX11 기능을 포함하는 애
// DX11은 쉐이더를 별도로 컴파일 해줘야 하므로, 그 컴파일을 하기 위해서 필요하다.
// 왜? 쉐이더는 hlsl 이라는 언어로 작성되기 때문에 해당 언어를 컴파일 하기 위해서 추가한다.
#pragma comment(lib, "d3dcompiler.lib")
// GUID를 사용하기 위해서 필요하다.
#pragma comment(lib, "dxguid.lib")

// RELEASE 매크로
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr;}

// 마이어스 싱글톤
#define DECLARE_SINGLETON(ClassName)\
private:\
	ClassName();\
	~ClassName();\
public:\
	static ClassName* GetInst()\
	{\
		static ClassName instance;\
		return &instance;\
	}

// 해상도 저장 구조체
struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

// 정점 버퍼 vertex buffer
struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	void* Data = nullptr;

	FVertexBuffer() = default;
	~FVertexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

// 인덱스 버퍼
struct FIndexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer() = default;
	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

// 정점의 정보를 저장하는 구조체
struct FVertexColor
{
	FVector3D Pos;
	FVector4D Color;

	FVertexColor()
	{

	}

	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color)
		: Pos(_Pos), Color(_Color)
	{

	}

	FVertexColor(float x, float y, float z, float r, float g, float b, float a)
		: Pos(x, y, z), Color(r, g, b, a)
	{

	}
};

namespace EShaderBufferType
{
	enum Type
	{
		Vertex = 0x1,	// 첫번째 비트값
		Pixel = 0x2,	// 두번째 비트값
		Hull = 0x4,		// 세번째 비트값
		Domain = 0x8,	// ...
		Geometry = 0x10,
		Compute = 0x20,
		Graphic = Vertex | Pixel | Hull | Domain | Geometry,
		All = Vertex | Pixel | Hull | Domain | Geometry | Compute
	};
}