#pragma once
#include "SceneComponent.h"

class CSpriteComponent : public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& Com);
	CSpriteComponent(CSpriteComponent&& Com);
	virtual ~CSpriteComponent();

protected:
	CSharedPtr<class CShader> mShader;
	//CSharedPtr<class CMesh> mMesh;

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);

	// 시점 함수
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSpriteComponent* Clone();
};

