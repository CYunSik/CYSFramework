#include "SceneEditor.h"
#include "../Object/EditorPlayer.h"
#include "../Object/TileMapObj.h"

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

	return true;
}

void CSceneEditor::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}
