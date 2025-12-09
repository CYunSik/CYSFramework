#pragma once
#include "SceneObject.h"
#include "../Component/TileMapComponent.h"
#include "../Component/TileMapRenderComponent.h"

class CTileMapObj : public CSceneObject
{
	friend class CScene;

protected:
	CTileMapObj();
	CTileMapObj(const CTileMapObj& Obj);
	CTileMapObj(CTileMapObj&& Obj);
	virtual ~CTileMapObj();

private:
	//타일맵 컴포넌트 
	CSharedPtr<CTileMapComponent> mTileMap;
	CSharedPtr <CTileMapRenderComponent> mTileMapRender;

public:
	virtual bool Init() override;
	virtual void Update(float DeltaTime) override;
};