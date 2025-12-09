#include "TileMapObj.h"

CTileMapObj::CTileMapObj()
{
}

CTileMapObj::CTileMapObj(const CTileMapObj& Obj)
{
}

CTileMapObj::CTileMapObj(CTileMapObj&& Obj)
{
}

CTileMapObj::~CTileMapObj()
{
}

bool CTileMapObj::Init()
{
	CSceneObject::Init();

	mTileMapRender = CreateComponent<CTileMapRenderComponent>();

	mTileMap = CreateComponent<CTileMapComponent>();

	mTileMapRender->SetBackTexture("TileMapBack", TEXT("Texture/MapBackGround.png"));

	SetRootComponent(mTileMapRender);

	mTileMap->CreateTile(100, 100, FVector2D(64.f, 64.f), 0);

	return true;
}

void CTileMapObj::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
