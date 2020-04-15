#pragma once
#include "singletonBase.h"

/* FMOD 사용하기 위해 라이브러리 추가 */
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;

// 사용할 사운드 버퍼 (사운드 갯수가 30개를 넘어가면 크기를 더 늘려줘야 함)
#define SOUNDBUFFER 30

// soundManager 클래스
class soundManager : public singletonBase <soundManager>
{
private:
	// 맵 관련
	typedef map<string, Sound**> arrSound;						// 사운드 파일을 담아둘 맵
	typedef map<string, Sound**>::iterator arrSoundIter;		// 사운드 파일을 담아둘 맵 반복자

	// 클래스 관련
	System* _system;		// 시스템 클래스
	Sound** _sound;			// 사운드 클래스
	Channel** _channel;		// 채널 클래스			   
	arrSound _mTotalSound;	// 맵에 담아 둘 사운드들

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 사운드 추가 (키값, 파일이름, BGM, 루프 여부)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	// 사운드 재생
	void play(string keyName, float volume = 1.0f);		//0.0f(min) ~ 1.0f(max)

	// 사운드 정지
	void stop(string keyName);

	// 사운드 일시 정지
	void pause(string keyName);

	// 사운드 다시 재생
	void resume(string keyName);

	// 플레이 중인지 체크
	bool isPlaySound(string keyName);

	// 일시 정지 중인지 체크
	bool isPauseSound(string keyName);

	// 생성자, 소멸자
	soundManager() {}
	~soundManager() {}
};

