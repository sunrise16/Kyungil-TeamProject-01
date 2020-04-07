#pragma once
#include "singletonBase.h"

// 싱글톤을 상속받은 아이들은 static으로 만들어지기 때문에
// 일반 클래스인 게임노드를 사용하려고 하면 터진다

// 클래스 전방 선언
class gameNode;

// sceneManager 클래스
class sceneManager : public singletonBase <sceneManager>
{
private:
	// 맵 관련
	typedef map<string, gameNode*> mSceneList;					// 맵으로 만든 씬 목록
	typedef map<string, gameNode*>::iterator miSceneList;		// 맵으로 만든 씬 목록의 반복자

	// 클래스 관련
	mSceneList _mSceneList;										// 각각의 씬(화면)들을 담아둘 맵
	gameNode* _currentScene;									// 현재 씬

public:
	// 초기화 처리
	HRESULT init();

	// 해제 처리
	void release();

	// 계산식 처리
	void update();

	// 화면 출력 처리
	void render();

	// 씬 추가
	gameNode* addScene(string sceneName, gameNode* scene);

	// 씬 로드
	HRESULT loadScene(string sceneName);

	// 생성자, 소멸자
	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

