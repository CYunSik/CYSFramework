#pragma once
#include "../GameInfo.h"
#include "../Component/ColliderBase.h"

#define QUADTREE_DIVISION_COUNT 10
#define QUADTREE_DEPTH_MAX 4

// 이진 트리 만든다고 생각. 
// 다만 노드가 4개일 뿐이다.

class CCollisionQuadTreeNode
{
	friend class CCollisionQuadTree;

private:
	CCollisionQuadTreeNode();
	~CCollisionQuadTreeNode();

private:
	class CScene* mScene = nullptr;
	// 부모 노드
	CCollisionQuadTreeNode* mParent = nullptr;

	// 자식 노드 4개
	CCollisionQuadTreeNode* mChild[4] = {};

	// 노드의 중앙 위치
	FVector2D mCenter;
	
	// 노드의 다음 길이? 크기?
	FVector2D mSize;

	// 트리의 깊이
	int mDepth = 0;

	// 몇개라면 분할할지
	int mDivisionCount = QUADTREE_DIVISION_COUNT;

	// 해당 노드에 속한 충돌체들
	std::vector<CSharedPtr<class CColliderBase>> mColliderList;

public:
	void AddCollider(class CColliderBase* Collider, std::vector<CCollisionQuadTreeNode*>& NodePool);
	void CreateChild(std::vector<CCollisionQuadTreeNode*>& NodePool);

private:
	// 충돌체가 이 노드에 속하는지 검사한다.
	bool IsInCollider(class CColliderBase* Collider);
};

class CCollisionQuadTree
{
	friend class CSceneCollision;

private:
	CCollisionQuadTree();
	~CCollisionQuadTree();

private:
	class CScene* mScene = nullptr;
	CCollisionQuadTreeNode* mRoot = nullptr;
	int mDivisionCount = QUADTREE_DIVISION_COUNT;
	// 노드 풀 : 이미 할당된 노드를 재사용하기 위해
	std::vector<CCollisionQuadTreeNode*> mNodePool;

public:
	void SetDivisionCount(int Count);

public:
	bool Init();
	void AddCollider(class CColliderBase* Collider);
	void Update(float DeltaTime);
};

