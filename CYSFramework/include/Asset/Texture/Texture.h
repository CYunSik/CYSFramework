#pragma once
#include "../Asset.h"

// 외부 라이브러리 헤더
#include "DirectXTex.h"

// 텍스쳐를 표현하기 위한 구조체
struct FTextureInfo
{
	// 픽셀 정보를 담기 위한 이미지 정보
	DirectX::ScratchImage* Image = nullptr;

	// 쉐이더 리소스 뷰
	ID3D11ShaderResourceView* SRV = nullptr;
	// 이미지 크기
	unsigned int Width = 0;
	unsigned int Height = 0;
	// 파일 경로 이름
	TCHAR FileName[MAX_PATH] = {};

	~FTextureInfo()
	{
		// 동적할당한거 지워주는거
		SAFE_DELETE(Image);
		// 레퍼런스 카운트로 관리하면
		SAFE_RELEASE(SRV);
	}
};

class CTexture : public CAsset
{
private:
	CTexture();
	~CTexture();

private:
	FTextureInfo* mData;

};