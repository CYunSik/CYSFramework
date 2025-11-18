#include "Texture.h"

#ifdef _DEBUG
#pragma comment(lib, "../Bin/DirectXTex_Debug.lib")
#else
#pragma comment(lib, "../Bin/DirectXTex.lib")
#endif


CTexture::CTexture()
{
	mAssetType = EAssetType::Texture;
}

CTexture::~CTexture()
{
}
