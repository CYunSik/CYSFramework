#pragma once
#include "../Share/Object.h"

#include "UIInfo.h"
#include "../Object/SceneObject.h"

class CWidget abstract : public CObject
{
	friend class CSceneUIManager;

protected:
	CWidget();
	virtual ~CWidget();

	// UI 전용 투영행렬을 만들기
protected:
	static FMatrix mUIProj;

public:
	static void CreateUIProjection(float Width, float Height, float ViewDist)
	{
		// 직교 투영
		mUIProj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, Width, 0, Height, 0, ViewDist);
	}

protected:
	// UI가 포함된 Scene
	class CScene* mScene = nullptr;

	// 해당 위젯을 들고있는 오브젝트
	CSharedPtr<CSceneObject> mOwnerObject;

	// 화면에 그려질 쉐이더
	CSharedPtr<class CShader> mShader;
	CSharedPtr<class CMesh> mMesh;
	class CUICBuffer* mUICBuffer = nullptr;
	class CTransformCBuffer* mTransformCBuffer = nullptr;

	// 이름
	std::string mName;

	// 위치
	FVector2D mPos;

	// 사이즈
	FVector2D mSize;

	// 피봇
	FVector2D mPivot;

	// Z오더
	int mZOrder = 0;

	// 로테이션
	float mRotation = 0.f;

public:
	const FVector2D& GetPos() const
	{
		return mPos;
	}

	const FVector2D& GetSize() const
	{
		return mSize;
	}

	const FVector2D& GetPivot() const
	{
		return mPivot;
	}

	int GetZOrder() const
	{
		return mZOrder;
	}

	float GetRotation() const
	{
		return mRotation;
	}

public:
	void SetPos(const FVector2D& Pos)
	{
		mPos = Pos;
	}

	void SetPos(float X, float Y)
	{
		mPos.x = X;
		mPos.y = Y;
	}

	void SetSize(const FVector2D& Size)
	{
		mSize = Size;
	}

	void SetSize(float X, float Y)
	{
		mSize.x = X;
		mSize.y = Y;
	}

	void SetPivot(const FVector2D& Pivot)
	{
		mPivot = Pivot;
	}

	void SetZOrder(int ZOrder)
	{
		mZOrder = ZOrder;
	}

	void SetRotation(float Rotation)
	{
		// 360 보다 큰 경우
		if (Rotation > 360.f)
		{
			// ex) 365.5f
			// 정수 부분
			int Angle1 = static_cast<int>(Rotation);
			// 소수 부분
			float Angle2 = Rotation - Angle1;

			// 정수 부분을 0 ~ 360도 사이로 만들고 싶다.
			Angle1 %= 360;

			mRotation = Angle1 + Angle2;
		}
		else if (Rotation < 0.f)
		{
			Rotation *= -1;

			// 정수 부분
			int Angle1 = static_cast<int>(Rotation);
			// 소수 부분
			float Angle2 = Rotation - Angle1;

			// 정수 부분을 0 ~ 360도 사이로 만들고 싶다.
			Angle1 %= 360;

			mRotation = 360.f - (Angle1 + Angle2);
		}

		mRotation = Rotation;
	}

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
	virtual bool CollisionMouse(const FVector2D& MousePos);
	virtual void EndFrame();
};

