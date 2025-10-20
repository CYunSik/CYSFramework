#include "ShaderManager.h"
#include "ColorMeshShader.h"

CShaderManager::CShaderManager()
{

}

CShaderManager::~CShaderManager()
{

}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	auto iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
	{
		return nullptr;
	}

	return (CShader*)iter->second.Get();
}

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshShader");

	return true;
}