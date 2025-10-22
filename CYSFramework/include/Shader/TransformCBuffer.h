#pragma once
#include "ConstantBufferData.h"

// 월드의 Transform 행렬 정보를 가지고 있는 상수 버퍼 데이터 클래스
class CTransformCBuffer : public CConstantBufferData
{
public:
	CTransformCBuffer();
	CTransformCBuffer(const CTransformCBuffer& Data);
	CTransformCBuffer(CTransformCBuffer&& Data);
	virtual ~CTransformCBuffer();

private:
	FTransformCBufferInfo mData;

	virtual bool Init();
	virtual void UpdateBuffer();

	virtual CConstantBufferData* Clone();

};

