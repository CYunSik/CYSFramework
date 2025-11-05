#pragma once
#include "GameInfo.h"

class CProfileManager
{
	DECLARE_SINGLETON(CProfileManager)

private:
	// 맵이라는 자료구조를 사용할거다 <키 값 : string, 밸류 값 : FCollisionProfile> 형식으로 저장할 것이다.
	std::unordered_map<std::string, FCollisionProfile*> mProfileMap;

public:
	bool Init();
	// 프로파일 생성
	bool CreateProfile(const std::string& Name, ECollisionChannel::Type Channel, bool Enable, ECollisionInteraction::Type Interaction);
	// 원하는 프로파일의 상호작용할 채널의 충돌 여부를 변경해준다.
	bool SetInteraction(const std::string& Name, ECollisionChannel::Type Channel, ECollisionInteraction::Type Interaction);
	// 충돌 여부
	bool SetEnable(const std::string& Name, bool Enable);

	FCollisionProfile* FindProfile(const std::string& Name);
};

