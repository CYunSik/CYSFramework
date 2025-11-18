#include "Texture.h"
#include "../../Device.h"

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

bool CTexture::LoadTexture(const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};

	// 문자열 복사
	// strcpy
	lstrcpy(FullPath, gRootPath);
	// 문자열 합치기
	// strcat
	lstrcat(FullPath, TEXT("Asset\\"));
	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(FullPath);
}

bool CTexture::LoadTextureFullPath(const TCHAR* FullPath)
{
	// E:\StudyCys\Framework\CYSFramework\CYSFramework\Bin\Asset\Texture\AA.png
	// Texture\AA.png

	FTextureInfo* Texture = new FTextureInfo;
	
	int Length = lstrlen(FullPath);

	// 파일 이름 가져오기
	for (int i = 0; i < Length; ++i)	// 복사비용 아끼려고 ++i 사용 (속도가 더 빠름)
	{
		if (gRootPath[i] != FullPath[i])
		{
			lstrcpy(Texture->FileName, &FullPath[i]);
			break;
		}
	}

	// 이미지 로드하기
	// 확장자로 이미지 불러오는게 달라진다.
	// 크게 DDS, TGA, 나머지(PNG, JPG 등등)

	// 파일 확장자를 구분하여 가져온다.
	TCHAR FileExt[_MAX_EXT] = {};

	//						드라이브,					디렉토리					파일 이름						확장자
	_wsplitpath_s(FullPath, nullptr, 0, nullptr, 0, nullptr, 0, FileExt, _MAX_EXT);

	// 대문자로 변경하려면 유니코드를 멀티바이트 문자열로 변환해주는 작업이 필요하다.
	// 대문자로 만들어주는 함수 _strupr_s 멀티바이트 문자열만 받기 때문에
	char ConvertExt[_MAX_EXT] = {};

	// 변환에 필요한 버퍼크기를 계산
	int Count = WideCharToMultiByte(CP_ACP, 0, FileExt, -1, nullptr, 0, nullptr, nullptr);

	WideCharToMultiByte(CP_ACP, 0, FileExt, -1, ConvertExt, Count, nullptr, nullptr);

	// 확장자를 대문자로 통일시켜준다.
	_strupr_s(ConvertExt);

	DirectX::ScratchImage* Image = new DirectX::ScratchImage;

	if (strcmp(ConvertExt, ".DDS") == 0)
	{
		if (FAILED(DirectX::LoadFromDDSFile(FullPath, DirectX::DDS_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);
			
			return false;
		}
	}
	else if (strcmp(ConvertExt, ".TGA") == 0)
	{
		if (FAILED(DirectX::LoadFromTGAFile(FullPath, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);

			return false;
		}
	}
	else
	{
		// PNG, JPG, BMP 등등
		if (FAILED(DirectX::LoadFromWICFile(FullPath, DirectX::WIC_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);

			return false;
		}
	}

	Texture->Image = Image;
	mTextureList.emplace_back(Texture);

	// 여기까지해서 이미지 정보를 불러왔다.

	return CreateResourceView(0);
}

void CTexture::SetShader(int Register, int ShaderBufferType, int TextureIndex)
{
	// 1번 인자 : 레지스터 번호
	// 2번 인자 : 몇개의 버퍼가 세팅되어 있는지
	// 3번 인자 : 세팅할 버퍼의 주소
	if (ShaderBufferType & EShaderBufferType::Vertex)
	{
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
	// 픽셀
	if (ShaderBufferType & EShaderBufferType::Pixel)
	{
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
	// 훌
	if (ShaderBufferType & EShaderBufferType::Hull)
	{
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
	// 도메인
	if (ShaderBufferType & EShaderBufferType::Domain)
	{
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
	// 지오메트리
	if (ShaderBufferType & EShaderBufferType::Geometry)
	{
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
	// 컴퓨트
	if (ShaderBufferType & EShaderBufferType::Compute)
	{
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &mTextureList[TextureIndex]->SRV);
	}
}

void CTexture::ResetShader(int Register, int ShaderBufferType)
{
	ID3D11ShaderResourceView* SRV = nullptr;

	if (ShaderBufferType & EShaderBufferType::Vertex)
	{
		CDevice::GetInst()->GetContext()->VSSetShaderResources(Register, 1, &SRV);
	}
	// 픽셀
	if (ShaderBufferType & EShaderBufferType::Pixel)
	{
		CDevice::GetInst()->GetContext()->PSSetShaderResources(Register, 1, &SRV);
	}
	// 훌
	if (ShaderBufferType & EShaderBufferType::Hull)
	{
		CDevice::GetInst()->GetContext()->HSSetShaderResources(Register, 1, &SRV);
	}
	// 도메인
	if (ShaderBufferType & EShaderBufferType::Domain)
	{
		CDevice::GetInst()->GetContext()->DSSetShaderResources(Register, 1, &SRV);
	}
	// 지오메트리
	if (ShaderBufferType & EShaderBufferType::Geometry)
	{
		CDevice::GetInst()->GetContext()->GSSetShaderResources(Register, 1, &SRV);
	}
	// 컴퓨트
	if (ShaderBufferType & EShaderBufferType::Compute)
	{
		CDevice::GetInst()->GetContext()->CSSetShaderResources(Register, 1, &SRV);
	}
}

bool CTexture::CreateResourceView(int Index)
{
	if (FAILED(DirectX::CreateShaderResourceView(CDevice::GetInst()->GetDevice(), mTextureList[Index]->Image->GetImages(), mTextureList[Index]->Image->GetImageCount(), mTextureList[Index]->Image->GetMetadata(), &mTextureList[Index]->SRV)))
	{
		return false;
	}
	mTextureList[Index]->Width = static_cast<unsigned int>(mTextureList[Index]->Image->GetImages()[0].width);
	mTextureList[Index]->Height = static_cast<unsigned int>(mTextureList[Index]->Image->GetImages()[0].height);

	return true;
}
