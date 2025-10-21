#pragma once

/*
	공용체 union
	메모리를 공유하는 문법
*/

//union MyTestUnion
//{
//	int Number;
//	float fNum;
//};

// 4차원 행렬을 이용할 것이다
#include "Vector4D.h"

// DX에서는 행렬을 지원 안해주냐? 해주고는 있다. 다만 사용이 까다롭다
// __declspec(align(16)) : DX에서 지원하는 수학 라이브러리에서 행렬 연산할때 이거 없으면 크래시 난다.
// XM_ALIGNED_STRUCT(16) XMMATRIX
// __declspec(align(x)) : x만큼 메모리 정렬을 지정하는 키워드
__declspec(align(16)) union FMatrix
{
	// DX에서 제공하는 행렬
	DirectX::XMMATRIX m;	// 사용하기 까다롭기 때문에 랩핑을 해주려고 공용체 union을 사용한 것이다.

	// 이름을 안붙이는 이유
	// 
	struct
	{
		 float _11, _12, _13, _14;
		 float _21, _22, _23, _24;
		 float _31, _32, _33, _34;
		 float _41, _42, _43, _44;
	};

	FVector4D v[4];

	// 생성자
	FMatrix()
	{
		// 기본이면 단위행렬로 초기화 해주자
		// XMMatrixIdentity() == 단위행렬
		m = DirectX::XMMatrixIdentity();
	}
	FMatrix(const FMatrix& _m)
	{
		m = _m.m;
	}
	FMatrix(FMatrix&& _m) noexcept
	{
		m = _m.m;
	}
	FMatrix(const DirectX::XMMATRIX& _m)
	{
		m = _m;
	}
	FMatrix(const FVector4D _v[4])
	{
		memcpy(v, _v, sizeof(FVector4D) * 4 );
	}

	// 연산자
	// 대입연산자
	const FMatrix& operator = (const FMatrix& _m)
	{
		m = _m.m;
		return *this;
	}

	const FMatrix& operator = (const DirectX::XMMATRIX& _m)
	{
		m = _m;
		return *this;
	}

	const FMatrix& operator = (const FVector4D _v[4])
	{
		memcpy(v, _v, sizeof(FVector4D) * 4);
		return *this;
	}

	// 곱셈
	// DirectX::XMMATRIX 곱셈 연산을 지원해준다
	FMatrix operator * (const FMatrix& _m) const
	{
		return FMatrix(m * _m.m);
	}

	FMatrix operator * (const DirectX::XMMATRIX& _m) const
	{
		return FMatrix(m * _m);
	}

	// 기능

	// 단위행렬로 만들어주는 기능
	void Identity()
	{
		m = DirectX::XMMatrixIdentity();
	}

	// 전치행렬로 만들어주는 기능
	void Transpose()
	{
		m = DirectX::XMMatrixTranspose(m);
	}

	// 역행렬 만들어주는 기능
	void Inverse()
	{
		// 행렬식 먼저 구해주고
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m);	// 행렬식을 구해준다.

		// 역행렬을 만들어주기
		m = DirectX::XMMatrixInverse(&det, m);
	}

	// 로컬좌표계 -> 월드좌표계 계산하는 행렬 만들것이다.



};
