#pragma once

#include "../GameInfo.h"
#include "Shader.h"

class CShaderManager
{
	DECLARE_SINGLETON(CShaderManager)

private:
	std::unordered_map<std::string, CSharedPtr<CShader>> mShaderMap;

public:
	bool Init();

};

