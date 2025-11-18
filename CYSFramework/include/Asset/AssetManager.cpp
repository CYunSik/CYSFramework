#include "AssetManager.h"

#include "Mesh/MeshManager.h"
#include "Texture/TextureManager.h"

CAssetManager::CAssetManager()
{

}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager);
	SAFE_DELETE(mTextureManager);
}

bool CAssetManager::Init()
{
	// 메쉬를 관리
	mMeshManager = new CMeshManager;

	if (!mMeshManager->Init())
	{
		SAFE_DELETE(mMeshManager);
		return false;
	}

	// 이미지 텍스쳐

	mTextureManager = new CTextureManager;

	if (!mTextureManager->Init())
	{
		SAFE_DELETE(mTextureManager);
		return false;
	}

	// 사운드, 이펙트 등 다양한 리소스들을 관리할 수도 있다.


	return true;
}