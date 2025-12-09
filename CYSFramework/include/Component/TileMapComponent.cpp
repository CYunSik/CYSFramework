#include "TileMapComponent.h"

#include "TileMapRenderComponent.h"
#include "../Object/SceneObject.h"

CTileMapComponent::CTileMapComponent()
{
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& Com)
	: CComponent(Com)
{
}

CTileMapComponent::CTileMapComponent(CTileMapComponent&& Com)
	: CComponent(Com)
{
}

CTileMapComponent::~CTileMapComponent()
{
	size_t Size = mTileList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mTileList[i]);
	}

}

void CTileMapComponent::CreateTile(int CountX, int CountY, const FVector2D& TileSize, int TileTextureFrame)
{
	mCountX = CountX;
	mCountY = CountY;
	mTileSize = TileSize;

	//타일맵 전체 크기 
	mMapSize.x = mCountX * mTileSize.x;
	mMapSize.y = mCountY * mTileSize.y;

	CTileMapRenderComponent* Renderer = mOwnerObject->FindSceneComponent<CTileMapRenderComponent>();

	if (Renderer)
	{
		FVector2D Scale;
		Scale.x = mCountX * mTileSize.x;
		Scale.y = mCountY * mTileSize.y;
		Renderer->SetWorldScale(Scale);
	}


	//타일맵 생성
	mTileList.resize(mCountX * mCountY);

	for (int i = 0; i < mCountY; ++i)
	{
		for (int j = 0; j < mCountX; ++j)
		{
			CTile* Tile = new CTile;

			//x축
			Tile->mPos.x = j * mTileSize.x;
			//y축
			Tile->mPos.y = i * mTileSize.y;

			Tile->mSize = mTileSize;

			//타일의 중아
			Tile->mCenter = Tile->mPos + mTileSize * 0.5f;

			Tile->mTextureFrame = TileTextureFrame;

			mTileList[i * mCountX + j] = Tile;
		}
	}

}

bool CTileMapComponent::Init()
{
	CComponent::Init();

	CTileMapRenderComponent* Renderer = mOwnerObject->FindSceneComponent<CTileMapRenderComponent>();

	if (Renderer)
	{
		Renderer->SetTileMapComponent(this);
	}




	return true;
}

bool CTileMapComponent::Init(const char* FileName)
{
	CComponent::Init(FileName);

	return true;
}

void CTileMapComponent::PreUpdate(float DeltaTime)
{
	CComponent::PreUpdate(DeltaTime);
}

void CTileMapComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);
}

void CTileMapComponent::PostRender()
{
	CComponent::PostRender();
}

CTileMapComponent* CTileMapComponent::Clone()
{
	return new CTileMapComponent(*this);
}

void CTileMapComponent::EndFrame()
{
	CComponent::EndFrame();
}
