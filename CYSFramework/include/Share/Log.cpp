#include "Log.h"

std::vector<std::string> CLog::mVecLog;
HANDLE CLog::hConsole;

bool CLog::Init()
{
#ifdef _DEBUG
	// 콘솔창 열어준다.
	AllocConsole();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#else

#endif // _DEBUG

	// 공간 10000개 예약해두기
	// size opacity
	mVecLog.reserve(10000);
	// mVecLog.resize(10000);

	return true;
}

void CLog::Destroy()
{
#ifdef _DEBUG
	// 콘솔창 닫아준다.
	FreeConsole();
#else

#endif // _DEBUG
}

void CLog::PrintLog(const std::string& Text, ELogPrintType PrintType)
{
	// 로그 출력시
	// 시간 출력
	// LPSYSTEMTIME;
	SYSTEMTIME sysTime;

	// UTC 표준 시간
	// GetSystemTime(&sysTime);

	// 지역시간
	GetLocalTime(&sysTime);

	char TimeText[256] = {};

	sprintf_s(TimeText, "[%d_%d_%d %d:%d:%d:%d]", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

	std::string OutputText = TimeText;

	OutputText += " : ";
	OutputText += Text;
	OutputText += "\n";
	mVecLog.emplace_back(OutputText);

	DWORD Number = 0;
	switch (PrintType)
	{
	case ELogPrintType::Console:

		WriteConsoleA(hConsole, OutputText.c_str(), (DWORD)OutputText.length(), &Number, nullptr);

		break;
	case ELogPrintType::VisualOutput:

		OutputDebugStringA(OutputText.c_str());

		break;
	case ELogPrintType::All:
		WriteConsoleA(hConsole, OutputText.c_str(), (DWORD)OutputText.length(), &Number, nullptr);
		OutputDebugStringA(OutputText.c_str());

		break;
	}
}

void CLog::SaveLog()
{
	// 로그 출력시
	// 시간 출력
	// LPSYSTEMTIME;
	SYSTEMTIME sysTime;

	// UTC 표준 시간
	// GetSystemTime(&sysTime);

	GetLocalTime(&sysTime);

	char TimeText[256] = {};

	sprintf_s(TimeText, "../Bin/Log/[%d_%d_%d_%d_%d_%d_%d].txt", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);

	// 파일 열기
	FILE* File = nullptr;
	fopen_s(&File, TimeText, "wt");

	if (!File)
	{
		return;
	}

	size_t Size = mVecLog.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 한줄씩 넣겠다.
		fputs(mVecLog[i].c_str(), File);
	}

	// 파일 닫기
	fclose(File);
}
