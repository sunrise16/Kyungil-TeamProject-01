#pragma once
#include "singletonBase.h"

/* FMOD ����ϱ� ���� ���̺귯�� �߰� */
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;

// ����� ���� ���� (���� ������ 30���� �Ѿ�� ũ�⸦ �� �÷���� ��)
#define SOUNDBUFFER 30

// soundManager Ŭ����
class soundManager : public singletonBase <soundManager>
{
private:
	// �� ����
	typedef map<string, Sound**> arrSound;						// ���� ������ ��Ƶ� ��
	typedef map<string, Sound**>::iterator arrSoundIter;		// ���� ������ ��Ƶ� �� �ݺ���

	// Ŭ���� ����
	System* _system;		// �ý��� Ŭ����
	Sound** _sound;			// ���� Ŭ����
	Channel** _channel;		// ä�� Ŭ����			   
	arrSound _mTotalSound;	// �ʿ� ��� �� �����

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ���� �߰� (Ű��, �����̸�, BGM, ���� ����)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	// ���� ���
	void play(string keyName, float volume = 1.0f);		//0.0f(min) ~ 1.0f(max)

	// ���� ����
	void stop(string keyName);

	// ���� �Ͻ� ����
	void pause(string keyName);

	// ���� �ٽ� ���
	void resume(string keyName);

	// �÷��� ������ üũ
	bool isPlaySound(string keyName);

	// �Ͻ� ���� ������ üũ
	bool isPauseSound(string keyName);

	// ������, �Ҹ���
	soundManager() {}
	~soundManager() {}
};

