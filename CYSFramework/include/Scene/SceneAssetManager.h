#pragma once
#include <unordered_map>
#include "../GameInfo.h"

class CSceneAssetManager
{
	friend class CScene;

private:
	CSceneAssetManager();
	~CSceneAssetManager();

private:
	class CScene* mScene = nullptr;

private:
	// 관리할 에셋들
	std::unordered_map<std::string, CSharedPtr<class CAsset>> mAssetMap;

public:
	bool Init();

#pragma region Mesh

	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
		void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);

#pragma endregion

#pragma region Texture

	bool LoadTexture(const std::string& Name, const TCHAR* FileName);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);

	class CTexture* FindTexture(const std::string& Name);

#pragma endregion
};

