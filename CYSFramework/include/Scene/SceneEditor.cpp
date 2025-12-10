#include "SceneEditor.h"
#include "../Object/EditorPlayer.h"
#include "../Object/TileMapObj.h"
#include "Input.h"

CSceneEditor::CSceneEditor()
{
}

CSceneEditor::~CSceneEditor()
{
}

bool CSceneEditor::Init()
{
	CScene::Init();

	CEditorPlayer* EidtorPlayer = CreateObj<CEditorPlayer>("EditorPlayer");

	mTileMapObj = CreateObj<CTileMapObj>("TileMap");

	//입력
	mInput->AddBindKey("EditorMode", '1');
	mInput->AddBindFunction("EditorMode", EInputType::Down, this, &CSceneEditor::EditorMode);

	mInput->AddBindKey("TileType", '2');
	mInput->AddBindFunction("TileType", EInputType::Down, this, &CSceneEditor::TileTypeKey);

	mInput->AddBindKey("TileFrame", '3');
	mInput->AddBindFunction("TileFrame", EInputType::Down, this, &CSceneEditor::TileFrameKey);

	return true;
}

void CSceneEditor::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}

void CSceneEditor::EditorMode(float DeltaTime)
{
	mEditorMode = static_cast<EEditorMode>((int)mEditorMode + 1);

	if (mEditorMode == EEditorMode::End)
	{
		mEditorMode = EEditorMode::TileType;
	}

	mTileMapObj->SetEditorMod(mEditorMode);

}

void CSceneEditor::TileTypeKey(float DeltaTime)
{
	mTileMapObj->AddTileType();
}

void CSceneEditor::TileFrameKey(float DeltaTime)
{
	mTileMapObj->AddTileFrame();
}
