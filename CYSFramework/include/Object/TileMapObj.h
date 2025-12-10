#pragma once
#include "SceneObject.h"
#include "../Component/TileMapComponent.h"
#include "../Component/TileMapRenderComponent.h"

class CTileMapObj :
	public CSceneObject
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

	//에디터 모드
	EEditorMode mEditorMode = EEditorMode::TileType;
	//변경할 타일타입
	ETileType mEditTileType = ETileType::Normal;

	// 마우스 오버 전용 
	//이전 타일타입 저장
	ETileType mOnMousePrevTileType = ETileType::None;
	int mOnMousePrevIndex = -1;

public:
	void SetEditorMod(EEditorMode Mode)
	{
		mEditorMode = Mode;
	}

	void AddTileType();

public:
	virtual bool Init() override;
	virtual void Update(float DeltaTime) override;
};

