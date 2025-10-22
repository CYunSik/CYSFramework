#include "ConstantBuffer.h"
#include "../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
}

bool CConstantBuffer::Init(int Size, int Register, int ShaderBufferType)
{
	mSize = Size;
	mRegister = Register;
	mShaderBufferType = ShaderBufferType;

	// 버퍼 만들기
	D3D11_BUFFER_DESC Desc = {};

	// 상숭버퍼는 정보갱신이 많기 때문에 Dynamic으로 만들어준다.
	// ex) 플레이어 이동 할때마다 갱신이 일어나기 때문에..
	Desc.Usage = D3D11_USAGE_DYNAMIC;

	// 버퍼의 크기
	Desc.ByteWidth = Size;

	// D3D11_BIND_FLAG
	// 상수 버퍼로 사용하겠다고 바인딩 한다.
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// D3D11_CPU_ACCESS_FLAG
	// CPU에서 상수버퍼에 값을 쓰겠다고 정의한다.
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// Desc정보 토대로 디바이스가 반환해줄거다.
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&Desc, nullptr, &mBuffer)))
	{
		return false;
	}

	return true;
}

// 상수버퍼에 들어갈 데이터 정보가 들어올 것이다.
void CConstantBuffer::Update(void* Data)
{

}
