#include "AssetManager.h"

#include "Asset.h"
#include "Mesh/MeshManager.h"
#include "Texture/TextureManager.h"
#include "Material/MaterialManager.h"

CAssetManager::CAssetManager()
{

}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager);
	SAFE_DELETE(mMaterialManager);
	SAFE_DELETE(mTextureManager);
}

bool CAssetManager::Init()
{
	// 이런게 있구나 정도. 메모해두고 사용할때 찾아서 사용
	// gRootPath 경로를 초기화 해준다.
	GetModuleFileName(0, gRootPath, MAX_PATH);

	// E:\StudyCys\Framework\CYSFramework\CYSFramework\Bin\CYSFramework_Debug.exe
	// 실행파일부분을 제거하고 폴더 경로만 사용하고 싶다.
	// '/' 비슷하다 '\\'
	int Length = lstrlen(gRootPath);

	for (int i = Length - 1; i >= 0; --i)
	{
		if (gRootPath[i] == '/' || gRootPath[i] == '\\')
		{
			// abc\def
			// 0123456
			// memset 함수는 메모리의 내용을 원하는 크기만큼 특정값으로 설정 가능하다.
			memset(&gRootPath[i + 1], 0, sizeof(TCHAR) * (Length - (i + 1)));
			break;
		}
	}

	// 머티리얼
	mMaterialManager = new CMaterialManager;

	if (!mMaterialManager->Init())
	{
		SAFE_DELETE(mMaterialManager);
		return false;
	}

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

void CAssetManager::ReleaseAsset(CAsset* Asset)
{
	switch (Asset->GetAssetType())
	{
	case EAssetType::Mesh:
		mMeshManager->ReleaseMesh(Asset);
		break;
	case EAssetType::Texture:
		mTextureManager->ReleaseTexture(Asset);
		break;
	}
}