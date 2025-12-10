#include "TileMapObj.h"

#include "../Scene/Input.h"
#include "../Scene/Scene.h"

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

void CTileMapObj::AddTileType()
{
	mEditTileType = static_cast<ETileType>((int)mEditTileType + 1);

	if (mEditTileType == ETileType::End)
	{
		mEditTileType = ETileType::Normal;
	}
}

bool CTileMapObj::Init()
{
	CSceneObject::Init();

	mTileMapRender = CreateComponent<CTileMapRenderComponent>();

	mTileMap = CreateComponent<CTileMapComponent>();

	// 아웃라인 그리기 -> 쉐이더랑 메쉬 설정 까지 
	mTileMap->SetTileOutLineRender(true);

	mTileMapRender->SetBackTexture("TileMapBack", TEXT("Texture/MapBackGround.png"));


	SetRootComponent(mTileMapRender);

	mTileMap->CreateTile(100, 100, FVector2D(64.f, 64.f), 0);

	return true;
}

void CTileMapObj::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	const FVector2D& MousePos = mScene->GetInput()->GetMouseWorldPos();

	if (mEditorMode == EEditorMode::TileType)
	{
		if (mScene->GetInput()->GetMouseHold(EMouseButtonType::LButton))
		{
			mTileMap->ChangeTileType(mEditTileType, MousePos);
		}
		//마우스가 올려져 있을때
		else if (!mScene->GetInput()->GetMouseDown(EMouseButtonType::LButton))
		{
			int Index = mTileMap->GetTileIndex(MousePos);

			//이전 인덱스와 지금 인덱스가 다를때만 변경
			if (Index != mOnMousePrevIndex)
			{
				ETileType PrevType = mTileMap->ChangeTileType(ETileType::MouseOver, MousePos);

				if (PrevType != ETileType::None)
				{
					if (mOnMousePrevIndex != -1)
					{
						mTileMap->ChangeTileType(mOnMousePrevTileType, mOnMousePrevIndex);
					}

					mOnMousePrevIndex = mTileMap->GetTileIndex(MousePos);
					mOnMousePrevTileType = PrevType;
				}
				else
				{
					mTileMap->ChangeTileType(mOnMousePrevTileType, mOnMousePrevIndex);
					mOnMousePrevIndex = -1;
					mOnMousePrevTileType = ETileType::None;
				}
			}
		}
	}
}
