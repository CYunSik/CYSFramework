#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>> mTextureMap;

public:
	bool Init();

public:
	bool LoadTexture(const std::string& Name, const TCHAR* FileName);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);

	// 파일 여러개 가져오기
	bool LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& FileName);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& FullPath);

	// 규칙적인 파일 이름으로 여러장 불러온다.
	bool LoadTexture(const std::string& Name, const TCHAR* FileName, const TCHAR* Ext, int Count);

	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(class CAsset* Texture);
};

