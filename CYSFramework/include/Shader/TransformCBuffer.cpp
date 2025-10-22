#include "TransformCBuffer.h"

CTransformCBuffer::CTransformCBuffer()
{
}

CTransformCBuffer::CTransformCBuffer(const CTransformCBuffer& Data)
{
}

CTransformCBuffer::CTransformCBuffer(CTransformCBuffer&& Data)
{
}

CTransformCBuffer::~CTransformCBuffer()
{
}

bool CTransformCBuffer::Init()
{
	return true;
}

void CTransformCBuffer::UpdateBuffer()
{
}

CConstantBufferData* CTransformCBuffer::Clone()
{
	return new CTransformCBuffer(*this);
}
