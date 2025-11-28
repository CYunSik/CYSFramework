#pragma once
#include "RenderState.h"

class CDepthStencilState : public CRenderState
{
	friend class CRenderStateManager;

protected:
	CDepthStencilState();
	virtual ~CDepthStencilState();

protected:
	// 스텐실에 넣을 기본값
	unsigned int mStencilRef = 0xffffffff;
	unsigned int mPrevStencilRef = 0xffffffff;

public:
	bool CreateState(bool DepthEnable, 
		D3D11_DEPTH_WRITE_MASK DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		D3D11_COMPARISON_FUNC DepthFunc = D3D11_COMPARISON_LESS,
		BOOL StencilEnable = false,
		UINT8 StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK,
		UINT8 StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK,
		D3D11_DEPTH_STENCILOP_DESC FrontFace =
		{D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS},
		D3D11_DEPTH_STENCILOP_DESC BackFace =
		{D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS }
		);
	//BOOL DepthEnable;     깊이 체크 여부

public:
	// 내 블렌드 스테이트로 설정해줘
	virtual void SetState() override;
	// 이전 스테이트로 복구해줘
	virtual void ResetState() override;
};

