#include "stdafx.h"
#include "soundManager.h"

// �ʱ�ȭ (init)
HRESULT soundManager::init()
{
	// FMOD �ý��� ����
	System_Create(&_system);

	// ����, ä�� �� ����
	_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	// ����, ä�� Ŭ���� ���� �Ҵ�
	_sound = new Sound*[SOUNDBUFFER];
	_channel = new Channel*[SOUNDBUFFER];

	// �޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * SOUNDBUFFER);

	// �ʱ�ȭ ����
	return S_OK;
}

// ���� (release)
void soundManager::release()
{
	// ���� �� ä�� ����
	if (_sound != NULL || _channel != NULL)
	{
		for (int i = 0; i < SOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	// �޸� ����
	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	// �ý��� �ݱ�
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

// ������Ʈ (update)
void soundManager::update()
{
	// ���ΰ��ӿ� ����Ŵ����� ������Ʈ �� ����� ��
	// _system : ���� ���� �Ѱ� ���
	// ���� �ý����� ������ ����ǰų�, ����� ���� �� ���带 �����ϴ� ��
	// ���� ���������� ������ �̷���� �� �ﰢ������ ó��
	_system->update();
}

// ���� �߰�
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)	// �Ϲ������� BGM
	{
		if (bgm)
		{
			// ���� ������ �̸� ���ε� �صΰ� ���
			// �Ѱ��� ���ϸ� ��� ����
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
		else	// ���� ������� ����
		{
			// ���� ������ �׶��׶� �ǽð����� �ε�
			// ���� ȿ������ ���� ũ�Ⱑ Ŭ ��� ���۰� ���� ���� ����
			// �������� ������ ���ÿ� ����� �����ϱ� ������ ȿ������ ����ϱ� ����
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
	}
	else	// �Ϲ������� ȿ����
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	// �ʿ� ���带 Ű���� �Բ� ���
	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));
}

// ���� ���
void soundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			// ���� ����
			_channel[count]->setVolume(volume);
		}
	}
}

// ���� ����
void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� ����
			_channel[count]->stop();
		}
	}
}

// ���� �Ͻ� ����
void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �Ͻ� ����
			_channel[count]->setPaused(true);
		}
	}
}

// ���� �ٽ� ���
void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �ٽ� ���
			_channel[count]->setPaused(false);
		}
	}
}

// �÷��� ������ üũ
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �Ͻ� ����
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

// �Ͻ� ���� ������ üũ
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �Ͻ� ����
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}