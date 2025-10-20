#pragma once

#include "../GameInfo.h"
#include "Shader.h"

class CShaderManager
{
	DECLARE_SINGLETON(CShaderManager)

private:
	std::unordered_map<std::string, CSharedPtr<CShader>> mShaderMap;

public:
	// 쉐이더 클래스 생성 해주기
	template<typename T>
	bool CreateShader(const std::string& Name)
	{
		CShader* Shader = FindShader(Name);

		if (Shader)
		{
			return true;
		}

		Shader = new T;

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		mShaderMap.insert(std::make_pair(Name, Shader));
		return true;
	}

	class CShader* FindShader(const std::string& Name);

public:
	bool Init();

};

