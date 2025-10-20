#pragma once

#include "../../GameInfo.h"
#include "../Asset.h"

/*
	메쉬는
	정점(버텍스)와 인덱스(정점을 어떻게 연결) 버퍼들을 만들고

	정면 부분 : LED 부분
	안 보여지는 후면 부분을 CASE 부분이라고 한다.
	뒷면이라도 정점은 만들어놔야 한다.


	메쉬 타입을 만들어서 이를 공유 포인터(스마트 포인터)를 만들어서 관리할거다.
*/

// 구조체 용도 : 정점버퍼와 인덱스 버퍼를 관리하기 위해서 슬롯으로 만들었다.
struct FMeshSlot
{
	// 인덱스 버퍼 : 여러곳에서 사용할 수 있다.
	FIndexBuffer IndexBuffer;
};


class CMesh abstract : public CAsset
{
public:
	CMesh();
	virtual ~CMesh();

protected:
	// 정점 버퍼
	FVertexBuffer mVertexBuffer;

	// 메쉬 슬롯
	std::vector<FMeshSlot*> mMeshSlot;

	// 삼각형으로 그릴지, 선으로 그릴지, 점으로 그릴지 선택하는 설정이다.
	/*
		D3D11_PRIMITIVE_TOPOLOGY 어떠한 도형을 그릴것인지 정해준다.
		POINTLIST		: 점
		LINELIST		: 선
		LINESTRIP		: 선 연결
		TRIANGLELIST	: 삼각형 (주로 사용할거)
		TRIANGLESTRIP	: 삼각형 끼리 연결 해준다. 게임에서는 트레일 같은거 만들때 사용한다. 궤적 만들때 사용한다.
	*/
	D3D11_PRIMITIVE_TOPOLOGY mPrimitive;

public:
	/*
		D3D11_USAGE 용도
		GPU 메모리 사용 방법
		D3D11_USAGE_DEFAULT     : 비디오 메모리에 만들어진 정보를 갱신할 수 있다.
		D3D11_USAGE_IMMUTABLE   : 생성할때만 값을 넣을 수 있다.
		D3D11_USAGE_DYNAMIC     : 비디오 메모리를 사용하는데 그 데이터를 CPU에도 복사본을 하나 더 만들어서 관리한다.
								  주로 충돌 파티클 같은거 만들때 사용한다.
								  데이터 이동이 너무 많아서 비효율적이다.
		D3D11_USAGE_STAGING     : CPU에서 읽기 쓰기 하겠다.
	*/

	// 메시를 만들기 위한 함수
	// 1번째 인자 : 정점 메모리의 주소
	// 2번째 인자 : 정점 정보의 크기
	// 3번째 인자 : 정점 정보의 갯수
	// 4번째 인자 : 정점 메모리의 사용 용도
	// 5번째 인자 : 어떻게 그려질지
	// 6번째 인자 : 인덱스 메모리의 주소
	// 7번째 인자 : 인덱스 정보의 크기
	// 8번째 인자 : 인덱스 정보의 갯수
	// 9번째 인자 : 인덱스 정보의 포맷
	// 10번째 인자 : 인덱스 메모리의 사용 용도
	bool CreateMesh(void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

public:
	bool CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage);

public:
	void Render();

};

