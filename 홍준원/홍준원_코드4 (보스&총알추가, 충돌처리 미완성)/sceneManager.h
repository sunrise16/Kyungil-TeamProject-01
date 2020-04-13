#pragma once
#include "singletonBase.h"

// �̱����� ��ӹ��� ���̵��� static���� ��������� ������
// �Ϲ� Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

// Ŭ���� ���� ����
class gameNode;

// sceneManager Ŭ����
class sceneManager : public singletonBase <sceneManager>
{
private:
	// �� ����
	typedef map<string, gameNode*> mSceneList;					// ������ ���� �� ���
	typedef map<string, gameNode*>::iterator miSceneList;		// ������ ���� �� ����� �ݺ���

	// Ŭ���� ����
	mSceneList _mSceneList;										// ������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;									// ���� ��

public:
	// �ʱ�ȭ ó��
	HRESULT init();

	// ���� ó��
	void release();

	// ���� ó��
	void update();

	// ȭ�� ��� ó��
	void render();

	// �� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);

	// �� �ε�
	HRESULT loadScene(string sceneName);

	// ������, �Ҹ���
	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

