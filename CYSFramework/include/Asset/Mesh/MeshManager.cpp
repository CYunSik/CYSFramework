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

	CMesh* Mesh = new CStaticMesh;

	if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitive, IndexData, IndexSize, IndexCount, Fmt, IndexUsage))
	{
		SAFE_DELETE(Mesh);
		return false;
	}

	mMeshMap.insert(std::make_pair(Name, Mesh));

	return true;
}
