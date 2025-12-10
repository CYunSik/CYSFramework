#pragma once
#include "Component.h"
#include "Tile.h"

class CTileMapComponent :
	public CComponent
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

	//외곽선 그리기
	bool mTileOutlineRender = false;
	//메쉬
	CSharedPtr<class CMesh> mOutlineMesh;
	//쉐이더 
	CSharedPtr<class CShader> mOutlineShader;
	//위치용 상수버퍼 
	class CTransformCBuffer* mLineTransformCBuffer = nullptr;
	//충돌체 상수버퍼 
	class CColliderCBuffer* mCBuffer = nullptr;


	//그리기 범위
	//화면이 그려지고있는 범위를 구할것이다. 
	int mViewStartX;
	int mViewStartY;
	int mViewEndX;
	int mViewEndY;


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

public:
	//외곽선 그리기
	void SetTileOutLineRender(bool Render);
	void RenderTileOutLine();


	//타일그리기
	void RenderTile();


public:
	//타일 인덱스 구하기
	int GetTileIndexX(const FVector3D& Pos) const;
	int GetTileIndexX(const FVector2D& Pos) const;
	int GetTileIndexX(float x) const;

	int GetTileIndexY(const FVector3D& Pos) const;
	int GetTileIndexY(const FVector2D& Pos) const;
	int GetTileIndexY(float y) const;

	int GetTileIndex(const FVector3D& Pos) const;
	int GetTileIndex(const FVector2D& Pos) const;
	int GetTileIndex(float x, float y) const;

public:
	//타일 타입 변경해주기
	ETileType ChangeTileType(ETileType Type, const FVector3D& Pos);
	ETileType ChangeTileType(ETileType Type, const FVector2D& Pos);
	ETileType ChangeTileType(ETileType Type, float x, float y);
	ETileType ChangeTileType(ETileType Type, int Index);

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

