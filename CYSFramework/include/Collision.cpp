#include "Collision.h"
#include "Component/ColliderAABB2D.h"
#include "Component/ColliderLine2D.h"
#include "Component/ColliderOBB2D.h"
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

bool CCollision::CollisionOBB2DToOBB2D(FVector3D& HitPoint, CColliderOBB2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionOBB2DToOBB2D(HitPoint, Src->GetBox(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToOBB2D(FVector3D& HitPoint, CColliderAABB2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionAABB2DToOBB2D(HitPoint, Src->GetBox(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionSphere2DToOBB2D(FVector3D& HitPoint, CColliderSphere2D* Src, CColliderOBB2D* Dest)
{
	if (CollisionSphere2DToOBB2D(HitPoint, Src->GetWorldPosition(), Src->GetRadius(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionLine2DToLine2D(FVector3D& HitPoint, class CColliderLine2D* Src, class CColliderLine2D* Dest)
{
	if (CollisionLine2DToLine2D(HitPoint, Src->GetLine(), Dest->GetLine()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionLine2DToAABB2D(FVector3D& HitPoint, class CColliderLine2D* Src, class CColliderAABB2D* Dest)
{
	if (CollisionLine2DToAABB2D(HitPoint, Src->GetLine(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionLine2DToOBB2D(FVector3D& HitPoint, class CColliderLine2D* Src, class CColliderOBB2D* Dest)
{
	if (CollisionLine2DToOBB2D(HitPoint, Src->GetLine(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionLine2DToSphere2D(FVector3D& HitPoint, class CColliderLine2D* Src,
	class CColliderSphere2D* Dest)
{
	if (CollisionLine2DToSphere2D(HitPoint, Src->GetLine(), Dest->GetWorldPosition(), Dest->GetRadius()))
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

bool CCollision::CollisionOBB2DToOBB2D(FVector3D& HitPoint, const FOBB2D& Src, const FOBB2D& Dest)
{
	// 두 충돌체의 중심의 거리 벡터를 구한다.
	FVector2D CenterLine = Src.Center - Dest.Center;

	// 축검사를 실시한다.
	// Src X축
	if (!ComputeAxisProjection(CenterLine, Src.Axis[EAxis::X], Src.HalfSize.x, Dest.Axis, Dest.HalfSize))
	{
		return false;
	}

	// Src Y축
	if (!ComputeAxisProjection(CenterLine, Src.Axis[EAxis::Y], Src.HalfSize.y, Dest.Axis, Dest.HalfSize))
	{
		return false;
	}

	// Dest X축
	if (!ComputeAxisProjection(CenterLine, Dest.Axis[EAxis::X], Dest.HalfSize.x, Src.Axis, Src.HalfSize))
	{
		return false;
	}

	// Dest Y축
	if (!ComputeAxisProjection(CenterLine, Dest.Axis[EAxis::Y], Dest.HalfSize.y, Src.Axis, Src.HalfSize))
	{
		return false;
	}

	// 충돌 성공

	// 충돌 지점은 AABB 정보로 만들어서 두 교집합의 중점을 충돌지점으로 사용할 것이다.
	FAABB2D Hit1, Hit2;

	Hit1 = CreateAABB2D(Src);
	Hit2 = CreateAABB2D(Dest);

	FVector3D Min, Max;
	// 비교 ? 참 : 거짓
	// 겹친부분의 최소 좌표
	Min.x = Hit1.Min.x > Hit2.Min.x ? Hit1.Min.x : Hit2.Min.x;
	Min.y = Hit1.Min.y > Hit2.Min.y ? Hit1.Min.y : Hit2.Min.y;

	// 겹친부분의 최대 좌표
	Max.x = Hit1.Max.x < Hit2.Max.x ? Hit1.Max.x : Hit2.Max.x;
	Max.y = Hit1.Max.y < Hit2.Max.y ? Hit1.Max.y : Hit2.Max.y;

	HitPoint.x = (Min.x + Max.x) * 0.5f;
	HitPoint.y = (Min.y + Max.y) * 0.5f;

	return true;
}

// AABB to OBB
bool CCollision::CollisionAABB2DToOBB2D(FVector3D& HitPoint, const FAABB2D& Src, const FOBB2D& Dest)
{
	FOBB2D SrcOBB = CreateOBB2D(Src);

	return CollisionOBB2DToOBB2D(HitPoint, SrcOBB, Dest);
}

bool CCollision::CollisionSphere2DToOBB2D(FVector3D& HitPoint, const FVector3D& SrcCenter, float SrcRadius, const FOBB2D& Dest)
{
	FVector2D ConvertCenter;
	ConvertCenter.x = SrcCenter.x;
	ConvertCenter.y = SrcCenter.y;

	FVector2D CenterLine = ConvertCenter - Dest.Center;

	FVector2D Axis = CenterLine;
	Axis.Normalize();	// 정사영 받을 축을 구했다.

	// 중앙 연결 라인을 축으로 검사한다.
	if (!ComputeAxisProjection(CenterLine, Axis, SrcRadius, Dest.Axis, Dest.HalfSize))
	{
		// 충돌 실패
		return false;
	}

	// Dest의 각 축을 분리축으로 사용한다.
	// Dest의 x축
	float CenterProjectionDist = abs(CenterLine.Dot(Dest.Axis[EAxis::X]));

	if (CenterProjectionDist > SrcRadius + Dest.HalfSize.x)
	{
		return false;
	}

	// Dest의 y축
	CenterProjectionDist = abs(CenterLine.Dot(Dest.Axis[EAxis::Y]));

	if (CenterProjectionDist > SrcRadius + Dest.HalfSize.y)
	{
		return false;
	}

	FAABB2D Hit1, Hit2;

	Hit1 = CreateAABB2D(ConvertCenter, SrcRadius);
	Hit2 = CreateAABB2D(Dest);

	FVector3D Min, Max;
	// 비교 ? 참 : 거짓
	// 겹친부분의 최소 좌표
	Min.x = Hit1.Min.x > Hit2.Min.x ? Hit1.Min.x : Hit2.Min.x;
	Min.y = Hit1.Min.y > Hit2.Min.y ? Hit1.Min.y : Hit2.Min.y;

	// 겹친부분의 최대 좌표
	Max.x = Hit1.Max.x < Hit2.Max.x ? Hit1.Max.x : Hit2.Max.x;
	Max.y = Hit1.Max.y < Hit2.Max.y ? Hit1.Max.y : Hit2.Max.y;

	HitPoint.x = (Min.x + Max.x) * 0.5f;
	HitPoint.y = (Min.y + Max.y) * 0.5f;

	return true;
}

bool CCollision::CollisionLine2DToLine2D(FVector3D& HitPoint, const FLine2D& Src, const FLine2D& Dest)
{
	// A : Src.Start
	// B : Src.End
	// C : Dest.Start
	// D : Dest.End
	FVector2D A = Src.Start;
	FVector2D B = Src.End;
	FVector2D C = Dest.Start;
	FVector2D D = Dest.End;

	// A B C
	int ccw1 = CCW2D(A, B, C);
	// A B D
	int ccw2 = CCW2D(A, B, D);
	// C D A
	int ccw3 = CCW2D(C, D, A);
	// C D B
	int ccw4 = CCW2D(C, D, B);

	if (ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0)
	{
		// 두 직선은 충돌했다.
		// 추가 제작 필요

		return true;
	}

	// 직선 검사
	// 직선 A B에 점 C가 있니?
	if (ccw1 == 0 && PointOnLine2D(A, B, C))
	{
		HitPoint.x = C.x;
		HitPoint.y = C.y;

		return true;
	}

	// A B D
	if (ccw2 == 0 && PointOnLine2D(A, B, D))
	{
		HitPoint.x = D.x;
		HitPoint.y = D.y;

		return true;
	}

	// C D A
	if (ccw3 == 0 && PointOnLine2D(C, D, A))
	{
		HitPoint.x = A.x;
		HitPoint.y = A.y;

		return true;
	}

	// C D B
	if (ccw4 == 0 && PointOnLine2D(C, D, B))
	{
		HitPoint.x = B.x;
		HitPoint.y = B.y;

		return true;
	}

	return false;
}

bool CCollision::CollisionLine2DToAABB2D(FVector3D& HitPoint, const FLine2D& Src, const FAABB2D& Dest)
{
	return false;
}

bool CCollision::CollisionLine2DToOBB2D(FVector3D& HitPoint, const FLine2D& Src, const FOBB2D& Dest)
{
	return false;
}

bool CCollision::CollisionLine2DToSphere2D(FVector3D& HitPoint, const FLine2D& Src, const FVector3D& Center,
	float Radius)
{
	return false;
}

// 축 검사
// 정사영
bool CCollision::ComputeAxisProjection(const FVector2D& CenterLine, const FVector2D& SeparationAxis, float AxisHalfSize,
	const FVector2D* DestAxis, const FVector2D& DestHalfSize)
{
	// 중심을 연결하는 벡터를 분리축에 투영하여 구간의 길이를 구했다.
	// 길이값이므로 부호가 필요 없어서 절대값으로 사용한다.
	// abs : 절대값
	float CenterProjectionDist = abs(CenterLine.Dot(SeparationAxis));

	float DestProjectionDist = 
		abs(SeparationAxis.Dot(DestAxis[EAxis::X]))* DestHalfSize.x + 
		abs(SeparationAxis.Dot(DestAxis[EAxis::Y]))* DestHalfSize.y;

	// 두 점의 거리 > 각 축에 투영된 두 도형의 반길이의 합
	// 충돌 실패
	if (CenterProjectionDist > DestProjectionDist + AxisHalfSize)
	{
		return false;
	}

	return true;
}

FAABB2D CCollision::CreateAABB2D(const FOBB2D& Info)
{
	FAABB2D result;
	
	// 사각형을 구상하는 꼭짓점 구하기
	FVector2D Pos[4];

	// 좌 상
	Pos[0] = Info.Center - Info.Axis[0] * Info.HalfSize.x + Info.Axis[1] * Info.HalfSize.y;
	// 좌 하
	Pos[1] = Info.Center - Info.Axis[0] * Info.HalfSize.x - Info.Axis[1] * Info.HalfSize.y;
	// 우 상
	Pos[2] = Info.Center + Info.Axis[0] * Info.HalfSize.x + Info.Axis[1] * Info.HalfSize.y;
	// 우 하
	Pos[3] = Info.Center + Info.Axis[0] * Info.HalfSize.x - Info.Axis[1] * Info.HalfSize.y;

	// 4개의 꼭짓점에서 가장 작은 X, Y 값을 Min. 가장 큰 X, Y 값을 Max로 넣으면 된다.

	// 초기화
	result.Min.x = Pos[0].x;
	result.Min.y = Pos[0].y;

	result.Max.x = Pos[0].x;
	result.Max.y = Pos[0].y;

	for (int i = 0; i < 4; ++i)
	{
		result.Min.x = result.Min.x > Pos[i].x ? Pos[i].x : result.Min.x;
		result.Min.y = result.Min.y > Pos[i].y ? Pos[i].y : result.Min.y;

		result.Max.x = result.Max.x < Pos[i].x ? Pos[i].x : result.Max.x;
		result.Max.y = result.Max.y < Pos[i].y ? Pos[i].y : result.Max.y;
	}

	return result;
}

FAABB2D CCollision::CreateAABB2D(const FVector2D& Center, float Radius)
{
	FAABB2D result;

	result.Min = Center - Radius;
	result.Max = Center + Radius;

	return result;
}

FOBB2D CCollision::CreateOBB2D(const FAABB2D& Info)
{
	FOBB2D result;

	result.Center = (Info.Min + Info.Max) * 0.5f;

	result.Axis[EAxis::X].x = 1.f;
	result.Axis[EAxis::X].y = 0.f;

	result.Axis[EAxis::Y].x = 0.f;
	result.Axis[EAxis::Y].y = 1.f;

	result.HalfSize = (Info.Max - Info.Min) * 0.5f;

	return result;
}

ECCWResult::Type CCollision::CCW2D(const FVector2D& P1, const FVector2D& P2, const FVector2D& P3)
{
	// CCW(Counter ClockWise) 알고리즘
	// 점 3개가 이루는 방향을 계산하는 알고리즘
	// CCW(A, B, C) = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
	// CCW(P1, P2, P3) = (P2x - P1x) * (P3y - P1y) - (P2y - P1y) * (P3x - P1x)

	// CCW는 외적이다.
	float Cross = (P2.x - P1.x) * (P3.y - P1.y) - (P2.y - P1.y) * (P3.x - P1.x);

	// 음수
	if (Cross < 0)
	{
		return ECCWResult::CW;
	}
	// 양수
	else if (Cross > 0)
	{
		return ECCWResult::CCW;
	}
	// 직선
	return ECCWResult::Line;
}

bool CCollision::PointOnLine2D(const FVector2D& LineStart, const FVector2D& LineEnd, const FVector2D& Point)
{
	float MinX, MinY, MaxX, MaxY;

	if (LineStart.x < LineEnd.x)
	{
		MinX = LineStart.x;
		MaxX = LineEnd.x;
	}
	else
	{
		MinX = LineEnd.x;
		MaxX = LineStart.x;
	}

	if (LineStart.y < LineEnd.y)
	{
		MinY = LineStart.y;
		MaxY = LineEnd.y;
	}
	else
	{
		MinY = LineEnd.y;
		MaxY = LineStart.y;
	}

	if (Point.x < MinX)
	{
		return false;
	}
	else if (MaxX < Point.x)
	{
		return false;
	}
	else if (Point.y < MinY)
	{
		return false;
	}
	else if (MaxY < Point.y)
	{
		return false;
	}

	return true;
}
