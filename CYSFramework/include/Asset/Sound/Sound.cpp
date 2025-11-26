#include "Sound.h"

// FMOD 라이브러리 링크
#pragma comment(lib, "../Bin/fmod_vc.lib");

#include "../../Share/Log.h"

CSound::CSound()
{
}

CSound::~CSound()
{
}

bool CSound::LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group, bool Loop, const char* FileName)
{
	mSystem = System;
	mGroup = Group;
	mLoop = Loop;

	char FullPath[MAX_PATH] = {};

	// 문자열 복사
	// strcpy
	strcpy_s(FullPath, gRootPathMultibyte);
	// 문자열 합치기
	// strcat
	strcat_s(FullPath, "Asset\\");
	strcat_s(FullPath, FileName);

	FMOD_MODE Mode = FMOD_DEFAULT;

	if (Loop)
	{
		Mode = FMOD_LOOP_NORMAL;
	}

	if (mSystem->createSound(FullPath, Mode, nullptr, &mSound) != FMOD_OK)
	{
		return false;
	}

	return true;
}

bool CSound::LoadSoundFullPath(FMOD::System* System, FMOD::ChannelGroup* Group, bool Loop, const char* FullPath)
{
	mSystem = System;
	mGroup = Group;
	mLoop = Loop;

	FMOD_MODE Mode = FMOD_DEFAULT;

	if (Loop)
	{
		Mode = FMOD_LOOP_NORMAL;
	}

	if (mSystem->createSound(FullPath, Mode, nullptr, &mSound) != FMOD_OK)
	{
		return false;
	}

	return true;
}

void CSound::Play()
{
	mSystem->playSound(mSound, mGroup, false, &mChannel);
	++mPlayCount;

	mChannel->setCallback(CSound::SoundEnd);
}

FMOD_RESULT CSound::SoundEnd(FMOD_CHANNELCONTROL* channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype,
	FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void* commanddata1, void* commanddata2)
{
	CLog::PrintLog("SoundEnd");

	return FMOD_OK;
}