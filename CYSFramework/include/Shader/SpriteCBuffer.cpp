#include "SpriteCBuffer.h"

CSpriteCBuffer::CSpriteCBuffer()
{
}

CSpriteCBuffer::CSpriteCBuffer(const CSpriteCBuffer& Data)
	: CConstantBufferData(Data), mData(Data.mData)
{
}

CSpriteCBuffer::CSpriteCBuffer(CSpriteCBuffer&& Data)
	: CConstantBufferData(Data), mData(Data.mData)
{
}

CSpriteCBuffer::~CSpriteCBuffer()
{
}

bool CSpriteCBuffer::Init()
{
	SetConstantBuffer("Sprite");

	return true;
}

void CSpriteCBuffer::UpdateBuffer()
{
	mBuffer->Update(&mData);
}

CSpriteCBuffer* CSpriteCBuffer::Clone()
{
	return new CSpriteCBuffer(*this);
}
