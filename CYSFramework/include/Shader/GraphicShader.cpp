#include "GraphicShader.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
}

void CGraphicShader::AddInputLayoutDesc()
{
	D3D11_INPUT_ELEMENT_DESC Desc = {};

	Desc.SemanticName;
	Desc.SemanticIndex;

	Desc.Format;

	Desc.InputSlot;
	Desc.InputSlotClass;
	Desc.InstanceDataStepRate;

	Desc.AlignedByteOffset;

	// emplace_back :
	mvecDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{


	return false;
}

bool CGraphicShader::Init()
{

	return true;
}

void CGraphicShader::SetShader()
{
}
