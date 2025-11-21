#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "FrameMeshShader.h"
#include "ConstantBuffer.h"
#include "StaticMeshShader.h"
#include "SpriteShader.h"

#include "../Device.h"

CShaderManager::CShaderManager()
{

}

CShaderManager::~CShaderManager()
{
	auto iter = mPixelShaderMap.begin();
	auto iterEnd = mPixelShaderMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

CShader* CShaderManager::FindShader(const std::string& Name)
{
	auto iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
	{
		return nullptr;
	}

	return (CShader*)iter->second.Get();
}

void CShaderManager::ReleaseShader(const std::string& Name)
{
	auto iter = mShaderMap.find(Name);

	if (iter != mShaderMap.end())
	{
		mShaderMap.erase(iter);
	}
}

bool CShaderManager::CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShaderBufferType)
{
	CConstantBuffer* CBuffer = FindCBuffer(Name);

	if (CBuffer)
	{
		return true;
	}

	CBuffer = new CConstantBuffer;

	if (!CBuffer->Init(Size, Register, ShaderBufferType))
	{
		SAFE_DELETE(CBuffer);
		return false;
	}

	mCBufferMap.insert(std::make_pair(Name, CBuffer));
	return true;
}

CConstantBuffer* CShaderManager::FindCBuffer(const std::string& Name)
{
	auto iter = mCBufferMap.find(Name);

	if (iter == mCBufferMap.end())
	{
		return nullptr;
	}

	return (CConstantBuffer*)iter->second.Get();
}

void CShaderManager::ReleaseCBuffer(const std::string& Name)
{
	auto iter = mCBufferMap.find(Name);

	if (iter != mCBufferMap.end())
	{
		mCBufferMap.erase(iter);
	}
}

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshShader");
	CreateShader<CFrameMeshShader>("FrameMeshShader");
	CreateShader<CStaticMeshShader>("StaticMeshShader");
	CreateShader<CSpriteShader>("SpriteShader");

	// 전용 픽셀쉐이더만 만들어둔다.
	if (!LoadPixelShader("DefaultMaterialShader", "DefaultMaterialPS", TEXT("Mesh.fx")))
	{
		return false;
	}

	// 우리가 사용할 상수버퍼도 만들어둔다.
	CreateConstantBuffer("Transform", sizeof(FTransformCBufferInfo), 0, EShaderBufferType::Vertex);

	// 머티리얼 용 상수버퍼
	CreateConstantBuffer("Material", sizeof(FMaterialCBufferInfo), 1, EShaderBufferType::Pixel);

	// 스프라이트 전용 상수버퍼
	CreateConstantBuffer("Sprite", sizeof(FSpriteCBufferInfo), 2, EShaderBufferType::Pixel);

	// 충돌체에 사용할 상수버퍼
	CreateConstantBuffer("Collider", sizeof(FColliderCBufferInfo), 3, EShaderBufferType::Pixel);

	return true;
}

bool CShaderManager::LoadPixelShader(const std::string& Name, const char* EntryName, const TCHAR* FileName)
{
	if (FindPixelShader(Name))
	{
		return true;
	}

	// 최종 경로가 나온다.
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);
	// 원하는 쉐이더 파일의 풀 경로가 나온다.

	// 컴파일 했는데 에러가 나면 여기에 들어올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	FMaterialPixelShader* mps = new FMaterialPixelShader;

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "ps_5_0", Flag, 0, &mps->Blob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	// 컴파일이 성공했다!
	// 컴파일이 성공했으면 해당 쉐이더로 객체를 생성시켜줘야한다.
	// GetBufferPointer -> 컴파일 된 코드
	// GetBufferSize -> 컴파일 된 코드의 크기
	if (FAILED(CDevice::GetInst()->GetDevice()->CreatePixelShader(mps->Blob->GetBufferPointer(), mps->Blob->GetBufferSize(), nullptr, &mps->PS)))
	{
		return false;
	}

	mPixelShaderMap.insert(std::make_pair(Name, mps));

	return true;
}

const FMaterialPixelShader* CShaderManager::FindPixelShader(const std::string& Name)
{
	auto iter = mPixelShaderMap.find(Name);

	if (iter == mPixelShaderMap.end())
	{
		return nullptr;
	}

	return iter->second;
}
