#include "Widget.h"
#include "../Shader/ShaderManager.h"

CWidget::CWidget()
{
}

CWidget::~CWidget()
{
	SAFE_RELEASE(mShader);
}

void CWidget::SetShader(const std::string& Name)
{
	mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CWidget::SetShader(class CShader* Shader)
{
	mShader = Shader;
}

bool CWidget::Init()
{

	return true;
}

void CWidget::Update(float DeltaTime)
{
}

void CWidget::Render()
{
}

bool CWidget::CollisionMouse(const FVector2D& MousePos)
{
	if (mRotation == 0.f || mRotation == 360.f)
	{
		// AABB
		// Widget 사각형의 정보를 만든다.
		FVector2D Min = mPos - mPivot * mSize;
		FVector2D Max = Min + mSize;

		if (MousePos.x < Min.x)
		{
			return false;
		}
		else if (MousePos.x > Max.x)
		{
			return false;
		}
		else if (MousePos.y < Min.y)
		{
			return false;
		}
		else if (MousePos.y > Max.y)
		{
			return false;
		}

		return true;
	}

	// OBB
	// 점과 OBB 충돌
	// 사각형의 축
	FVector2D Axis[2];

	// 하프사이즈
	FVector2D HalfSize = mSize * 0.5f;

	// 중심점
	FVector2D Center = mPos - mPivot * mSize + HalfSize;

	// 사각형의 축 -> 회전만큼 축을 돌려주고
	// 회전량
	FMatrix matRot;
	matRot.RotationZ(mRotation);	// Z축 회전행렬

	FVector3D OriginAxis[2];	// 순서 1 0 0 / 0 1 0
	OriginAxis[0] = FVector3D::Axis[EAxis::X];
	OriginAxis[1] = FVector3D::Axis[EAxis::Y];

	OriginAxis[0] = OriginAxis[0].TransformNormal(matRot);
	OriginAxis[1] = OriginAxis[1].TransformNormal(matRot);

	// 최종 사각형 축
	Axis[0].x = OriginAxis[0].x;
	Axis[0].y = OriginAxis[0].y;
	Axis[1].x = OriginAxis[1].x;
	Axis[1].y = OriginAxis[1].y;

	// 비교축이기 때문에 정규화
	Axis[0].Normalize();
	Axis[1].Normalize();

	// 마우스 좌표랑 사각형의 원점을 잇는 선
	FVector2D CenterLine = Center - MousePos;

	// 사각형의 X축
	float Dist = abs(CenterLine.Dot(Axis[0]));

	if (Dist > HalfSize.x)
	{
		return false;
	}

	// 사각형의 Y축
	Dist = abs(CenterLine.Dot(Axis[1]));

	if (Dist > HalfSize.y)
	{
		return false;
	}

	return true;


}
