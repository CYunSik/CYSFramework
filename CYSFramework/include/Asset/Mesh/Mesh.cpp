#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
    size_t Size = mMeshSlot.size();

    for (size_t i = 0; i < Size; ++i)
    {
        SAFE_DELETE(mMeshSlot[i]);
    }

}

bool CMesh::CreateMesh(void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
    mVertexBuffer.Size = Size;
    mVertexBuffer.Count = Count;
    mVertexBuffer.Data = new char[Size * Count];
    memcpy(mVertexBuffer.Data, VertexData, Size * Count);

    // 정점 버퍼 만들기
    if (!CreateBuffer(&mVertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData, Size, Count, VertexUsage))
    {
        return false;
    }

    mPrimitive = Primitive;

    // 인덱스 버퍼 만들기
    if (IndexData)
    {
        FMeshSlot* Slot = new FMeshSlot;
        Slot->IndexBuffer.Size = IndexSize;
        Slot->IndexBuffer.Count = IndexCount;
        Slot->IndexBuffer.Fmt = Fmt;
        Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
        memcpy(Slot->IndexBuffer.Data, IndexData, IndexSize * IndexCount);

        if (!CreateBuffer(&Slot->IndexBuffer.Buffer, D3D11_BIND_INDEX_BUFFER, IndexData, IndexSize, IndexCount, IndexUsage))
        {
            SAFE_DELETE(Slot);
            return false;
        }
        mMeshSlot.push_back(Slot);
    }


    return true;
}

bool CMesh::CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage)
{
    // 버퍼 사용 설명서 만들어서
    // 설명서 대로 만들어주세요
    // 버퍼 만드는 용도이다
    D3D11_BUFFER_DESC BufferDesc = {};

    BufferDesc.ByteWidth = Size * Count;
   
    if (Usage == D3D11_USAGE_DYNAMIC)
    {
        BufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    }
    else if (Usage == D3D11_USAGE_STAGING)
    {
        BufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    }

    // 버퍼를 생성한다.
    D3D11_SUBRESOURCE_DATA BufferData = {};
    BufferData.pSysMem = Data;

    if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&BufferDesc, &BufferData, Buffer)))
    {
        return false;
    }


    return true;
}
