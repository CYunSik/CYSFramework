#include "MeshManager.h"
#include "StaticMesh.h"

CMeshManager::CMeshManager()
{

}

CMeshManager::~CMeshManager()
{

}

bool CMeshManager::CreateMesh(const std::string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
	// 메쉬 찾아오기
	// 기존에 같은 이름으로 등록된 mesh가 있는지 검사한다.
	CMesh* Mesh = FindMesh(Name);

	if (Mesh)
	{
		return true;
	}
	// 기존에 사용한 mesh가 없으면 새로 추가한다.
	Mesh = new CStaticMesh;

	if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitive, IndexData, IndexSize, IndexCount, Fmt, IndexUsage))
	{
		SAFE_DELETE(Mesh);
		return false;
	}

	mMeshMap.insert(std::make_pair(Name, CSharedPtr(Mesh)));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	std::unordered_map<std::string, CSharedPtr>::iterator iter = mMeshMap.find(Name);

	if (iter == mMeshMap.end())
	{
		return nullptr;
	}

	return (CMesh*)iter->second.Get();
}
