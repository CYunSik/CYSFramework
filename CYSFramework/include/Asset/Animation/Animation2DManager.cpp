#include "Animation2DManager.h"
#include "Animation2DData.h"
#include "../../Animation/Animation2D.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
	CAnimation2D::DestroyCBuffer();
}

bool CAnimation2DManager::Init()
{
	// 애니메이션용 상수 버퍼 생성
	CAnimation2D::CreateCBuffer();

	// 애니메이션 하나 등록하기
	// Texture/Player/Player.png
	// 스프라이트 형식으로 만들기
	CreateAnimation("PlayerIdle");
	SetAnimationTextureType("PlayerIdle", EAnimationTextureType::SpriteSheet);
	SetTexture("PlayerIdle", "PlayerSprite", TEXT("Texture/Player/Player.png"));

	for (int i = 0; i < 5; ++i)
	{
		AddFrame("PlayerIdle", i * 200.f, 0.f, 200.f, 200.f);
	}

	// 플레이어 오른쪽 걷기
	CreateAnimation("KrisWalkRight");
	SetAnimationTextureType("KrisWalkRight", EAnimationTextureType::Frame);

	std::vector<const TCHAR*> FileNames;
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisr_dark/spr_krisr_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisr_dark/spr_krisr_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisr_dark/spr_krisr_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisr_dark/spr_krisr_dark_3.png"));

	SetTexture("KrisWalkRight", "KrisWalkRight", FileNames);
	AddFrameCount("KrisWalkRight", 4, 0.f, 0.f, 19.f, 38.f);

	// 플레이어 왼쪽 걷기
	CreateAnimation("KrisWalkLeft");
	SetAnimationTextureType("KrisWalkLeft", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisl_dark/spr_krisl_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisl_dark/spr_krisl_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisl_dark/spr_krisl_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisl_dark/spr_krisl_dark_3.png"));

	SetTexture("KrisWalkLeft", "KrisWalkLeft", FileNames);
	AddFrameCount("KrisWalkLeft", 4, 0.f, 0.f, 19.f, 38.f);

	// 플레이어 위로 걷기
	CreateAnimation("KrisWalkUp");
	SetAnimationTextureType("KrisWalkUp", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisu_dark/spr_krisu_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisu_dark/spr_krisu_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisu_dark/spr_krisu_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisu_dark/spr_krisu_dark_3.png"));

	SetTexture("KrisWalkUp", "KrisWalkUp", FileNames);
	AddFrameCount("KrisWalkUp", 4, 0.f, 0.f, 19.f, 38.f);

	// 플레이어 아래로 걷기
	CreateAnimation("KrisWalkDown");
	SetAnimationTextureType("KrisWalkDown", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisd_dark/spr_krisd_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisd_dark/spr_krisd_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisd_dark/spr_krisd_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisd_dark/spr_krisd_dark_3.png"));

	SetTexture("KrisWalkDown", "KrisWalkDown", FileNames);
	AddFrameCount("KrisWalkDown", 4, 0.f, 0.f, 19.f, 38.f);

	// 플레이어 공격
	CreateAnimation("KrisAttack");
	SetAnimationTextureType("KrisAttack", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_krisb_attack/spr_krisb_attack_old_ch1_7.png"));

	SetTexture("KrisAttack", "KrisAttack", FileNames);
	AddFrameCount("KrisAttack", 8, 0.f, 0.f, 63.f, 50.f);

	// 플레이어 공격 이펙트
	CreateAnimation("AttackEffect");
	SetAnimationTextureType("AttackEffect", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_7.png"));

	SetTexture("AttackEffect", "AttackEffect", FileNames);
	AddFrameCount("AttackEffect", 8, 0.f, 0.f, 44.f, 45.f);

	// 제빌 배경
	CreateAnimation("JevilCarousel");
	SetAnimationTextureType("JevilCarousel", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR Path[37][MAX_PATH] = {};
	for (int i = 1; i <= 37; ++i)
	{
		wsprintf(Path[i - 1], TEXT("Texture/Jevil/jevil-carousel/jevil-carousel (%d).png"), i);
		FileNames.emplace_back(Path[i - 1]);
	}
	
	SetTexture("JevilCarousel", "JevilCarousel", FileNames);
	AddFrameCount("JevilCarousel", 37, 0.f, 0.f, 640.f, 480.f);

	// 제빌 클로버 폭탄
	CreateAnimation("ClubBoom");
	SetAnimationTextureType("ClubBoom", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_bomb_club_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_bomb_club_ch1_1.png"));

	SetTexture("ClubBoom", "ClubBoom", FileNames);
	AddFrameCount("ClubBoom", 2, 0.f, 0.f, 23.f, 23.f);

	return true;
}

bool CAnimation2DManager::CreateAnimation(const std::string& Name)
{
	// 생성해야하는데 같은 이름이 있으면 false
	if (FindAnimation(Name))
	{
		return false;
	}

	CAnimation2DData* Animation = new CAnimation2DData;

	Animation->SetName(Name);

	mAnimationMap.insert(std::make_pair(Name, Animation));

	return true;
}

class CAnimation2DData* CAnimation2DManager::FindAnimation(const std::string& Name)
{
	auto iter = mAnimationMap.find(Name);

	if (iter == mAnimationMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimation2DManager::ReleaseAnimation(class CAsset* Animation)
{
	auto iter = mAnimationMap.find(Animation->GetName());

	if (iter != mAnimationMap.end())
	{
		mAnimationMap.erase(iter);
	}
}

bool CAnimation2DManager::SetAnimationTextureType(const std::string& Name, EAnimationTextureType Type)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}
	
	Animation->SetAnimationTextureType(Type);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, class CTexture* Texture)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(Texture);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, std::vector<const TCHAR*> FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const TCHAR* Ext, int Count)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName, Ext, Count);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName, const TCHAR* FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

// 프레임 설정
bool CAnimation2DManager::AddFrame(const std::string& Name, const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name, float StartX, float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(StartX, StartY, SizeX, SizeY);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, float StartX, float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, StartX, StartY, SizeX, SizeY);

	return true;
}