#include "Collision.h"
#include "Component/ColliderAABB2D.h"
#include "Component/ColliderSphere2D.h"

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, CColliderAABB2D* Src,CColliderAABB2D* Dest)
{
	if(CollisionAABB2DToAABB2D(HitPoint, Src->GetBox(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionSphere2DToSphere2D(FVector3D& HitPoint, CColliderSphere2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionSphere2DToSphere2D(HitPoint, Src->GetWorldPosition(), Src->GetRadius(), Dest->GetWorldPosition(), Dest->GetRadius()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToSphere2D(FVector3D& HitPoint, CColliderAABB2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionAABB2DToSphere2D(HitPoint, Src->GetBox(), Dest->GetWorldPosition(), Dest->GetRadius()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, const FAABB2D& Src, const FAABB2D& Dest)
{
	// AABB 충돌
	// 좌표
	if (Src.Min.x > Dest.Max.x)
	{
		// 충돌체 왼쪽이 노드의 오른쪽 보다 크다.
		return false;
	}
	else if (Dest.Min.x > Src.Max.x)
	{
		// 충돌체 오른쪽이 노드의 왼쪽보다 작다
		return false;
	}
	else if (Src.Min.y > Dest.Max.y)
	{
		// 충돌체의 아래가 노드의 위보다 크다.
		return false;
	}
	else if (Dest.Min.y > Src.Max.y)
	{
		// 충돌체의 위가 노드의 아래보다 작다.
		return false;
	}

	// 충돌했다!
	// 충돌 좌표
	FVector3D Min, Max;
			// 비교 ? 참 : 거짓
	// 겹친부분의 최소부분
	Min.x = Src.Min.x > Dest.Min.x ? Src.Min.x : Dest.Min.x;
	Min.y = Src.Min.y > Dest.Min.y ? Src.Min.y : Dest.Min.y;

	// 겹친부분의 최대 좌표
	Max.x = Src.Max.x < Dest.Max.x ? Src.Max.x : Dest.Max.x;
	Max.y = Src.Max.y < Dest.Max.y ? Src.Max.y : Dest.Max.y;

	HitPoint.x = (Min.x + Max.x) * 0.5f;
	HitPoint.y = (Min.y + Max.y) * 0.5f;

	return true;
}

bool CCollision::CollisionSphere2DToSphere2D(FVector3D& HitPoint, const FVector3D& SrcCenter, float SrcRadius, const FVector3D& DestCenter, float DestRadius)
{
	// Src와 Dest의 원충돌이 일어날것이다.
	// 두 원의 중심간의 거리를 구한다.
	float Dist = SrcCenter.Distance(DestCenter);

	// 원충돌 했니?
	// 두 원점의 거리가 두 원의 반지름의 합보다 작니?
	if (Dist <= SrcRadius + DestRadius)
	{
		// 충돌

		// 충돌 지점의 길이의 절반을 구한다.
		float Gap = SrcRadius + DestRadius - Dist;
		Gap *= 0.5f;

		// 두 중심을 잇는 방향 벡터를 구한다.
		FVector3D Dir = DestCenter - SrcCenter;
		Dir.Normalize();	// Src에서 Dest로 가는 방향을 구했다.

		// 충돌했으면 HitPoint 어디니?
		HitPoint = SrcCenter + Dir * (SrcRadius - Gap);	// 충돌 사이 좌표

		return true;
	}

	// 충돌 안함!
	return false;
}

bool CCollision::CollisionAABB2DToSphere2D(FVector3D& HitPoint, const FAABB2D& Src, const FVector3D& DestCenter, float DestRadius)
{
	// 1. 원의 중심이 사각형의 안에 있는지 검사해야한다.
	// 원의 중점의 x값이 AABB 사각형의 좌, 우 사이에 있거나
	// 또는 y값이 AABB 사각형의 위, 아래 사이에 있는지 먼저 검사한다.
	if ((DestCenter.x >= Src.Min.x && DestCenter.x <= Src.Max.x) || 
		(DestCenter.y >= Src.Min.y && DestCenter.y <= Src.Max.y))
	{
		// 사각형의 크기에서 반지름 만큼 더한 사각형 안에 있는지 검사한다.
		// 사각형을 원의 반지름 만큼 확장시킨다.
		FAABB2D SrcExtent;
		SrcExtent.Min = Src.Min - DestRadius;
		SrcExtent.Max = Src.Max + DestRadius;

		// 확장된 사각형 안에 원의 중점이 들어있는지 확인한다.
		if (DestCenter.x < SrcExtent.Min.x)
		{
			return false;
		}
		else if (DestCenter.x > SrcExtent.Max.x)
		{
			return false;
		}
		else if (DestCenter.y < SrcExtent.Min.y)
		{
			return false;
		}
		else if (DestCenter.y > SrcExtent.Max.y)
		{
			return false;
		}

		// 충돌
		// Dest 원을 내접원으로 하는 사각형을 구했다.
		FAABB2D SphereAABB;
		SphereAABB.Min.x = DestCenter.x - DestRadius;
		SphereAABB.Min.y = DestCenter.y - DestRadius;
		SphereAABB.Max.x = DestCenter.x + DestRadius;
		SphereAABB.Max.y = DestCenter.y + DestRadius;

		FVector3D Min, Max;
		// 비교 ? 참 : 거짓
		// 겹친부분의 최소 좌표
		Min.x = Src.Min.x > SphereAABB.Min.x ? Src.Min.x : SphereAABB.Min.x;
		Min.y = Src.Min.y > SphereAABB.Min.y ? Src.Min.y : SphereAABB.Min.y;

		// 겹친부분의 최대 좌표
		Max.x = Src.Max.x < SphereAABB.Max.x ? Src.Max.x : SphereAABB.Max.x;
		Max.y = Src.Max.y < SphereAABB.Max.y ? Src.Max.y : SphereAABB.Max.y;

		HitPoint.x = (Min.x + Max.x) * 0.5f;
		HitPoint.y = (Min.y + Max.y) * 0.5f;

		return true;
	}

	// 3. 대각선 영역을 검사한다.
	FVector3D Vertex;
	// 가장 가까운 꼭짓점을 구하고
	// 왼쪽 대각선 영역에 있는가?
	if (DestCenter.x < Src.Min.x)
	{
		Vertex.x = Src.Min.x;
	}
	else
	{
		Vertex.x = Src.Max.x;
	}

	// 대각선에 아래쪽인지 위쪽인지
	if (DestCenter.y < Src.Min.y)
	{
		Vertex.y = Src.Min.y;
	}
	else
	{
		Vertex.y = Src.Max.y;
	}

	// 두 점 사이 거리
	float Dist = Vertex.Distance(DestCenter);

	// 해당 꼭짓점이랑 원의 중심이랑 거리가 반지름보다 작은지 확인해야한다.
	if (Dist <= DestRadius)
	{
		// 모서리할때는 충돌 지점을 모서리로 하겠다.
		HitPoint = Vertex;
		return true;
	}

	return false;
}