#include "SpriteComponent.h"

#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Material/MaterialManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"

CSpriteComponent::CSpriteComponent()
{
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& Com)
	: CSceneComponent(Com)
{
}

CSpriteComponent::CSpriteComponent(CSpriteComponent&& Com)
	: CSceneComponent(Com)
{
}

CSpriteComponent::~CSpriteComponent()
{
}

void CSpriteComponent::SetShader(const std::string& Name)
{
	mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CSpriteComponent::SetShader(class CShader* Shader)
{
	mShader = Shader;
}

bool CSpriteComponent::Init()
{
	CSceneComponent::Init();

	return true;
}

bool CSpriteComponent::Init(const char* FileName)
{
	CSceneComponent::Init(FileName);

	return true;
}

void CSpriteComponent::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}

void CSpriteComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CSpriteComponent::PreRender()
{
	CSceneComponent::PreRender();
}

void CSpriteComponent::Render()
{
	CSceneComponent::Render();
}

void CSpriteComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSpriteComponent* CSpriteComponent::Clone()
{
	return new CSpriteComponent(*this);
}
