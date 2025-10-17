#pragma once

#include "../GameInfo.h"

class CAssetManager
{
public:
	DECLARE_SINGLETON(CAssetManager)

private:
	class CMeshManager* mMeshManager = nullptr;

public:
	class CMeshManager* GetMeshManager() const
	{
		return mMeshManager;
	}

public:
	bool Init();
};

