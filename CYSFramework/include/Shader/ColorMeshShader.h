#pragma once
#include "GraphicShader.h"

class CColorMeshShader : public CGraphicShader
{
protected:
	CColorMeshShader();
	virtual ~CColorMeshShader();

public:
	bool Init() override;
};

