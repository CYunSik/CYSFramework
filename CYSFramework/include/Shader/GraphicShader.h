#pragma once
#include "Shader.h"

class CGraphicShader abstract : public CShader
{
	friend class CShaderManager;

private:
	// 입력 레이아웃
	// 정점 구조가 어떻게 구성되어 있는지 알려주는 것
	// FVertexColor == VS_INPUT_Color 같은 타입이다 라고 알려주는 것이다. 매칭시켜준다.
	ID3D11InputLayout* mInputLayout = nullptr;

	// 레지스터에 지정을 위한 구조체
	std::vector<D3D11_INPUT_ELEMENT_DESC> mvecDesc;

protected:
	CGraphicShader();
	~CGraphicShader();

public:
	void AddInputLayoutDesc();
	bool CreateInputLayout();

public:
	virtual bool Init();

	// final 키워드
	// 이 함수는 더이상 오버라이딩 하지 않겠다.
	virtual void SetShader() final;
};

