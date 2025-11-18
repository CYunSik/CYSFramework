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

	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(class CAsset* Texture);
};

