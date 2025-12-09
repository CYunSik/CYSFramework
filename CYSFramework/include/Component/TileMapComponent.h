#pragma once
#include "Component.h"
#include "Tile.h"

class CTileMapComponent : public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CTileMapComponent();
	CTileMapComponent(const CTileMapComponent& Com);
	CTileMapComponent(CTileMapComponent&& Com);
	virtual ~CTileMapComponent();

protected:
	std::vector<CTile*> mTileList;
	int mCountX = 0;
	int mCountY = 0;
	FVector2D mTileSize;
	//타일맵 전체크기
	FVector2D mMapSize;

public:
	const FVector2D& GetTileSize() const
	{
		return mTileSize;
	}

	int GetTileCountX() const
	{
		return mCountX;
	}

	int GetTileCountY() const
	{
		return mCountY;
	}

public:
	void CreateTile(int CountX, int CountY, const FVector2D& TileSize, int TileTextureFrame = -1);

	//시점 함수 
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PostRender();
	virtual CTileMapComponent* Clone();
	virtual void EndFrame();
};

