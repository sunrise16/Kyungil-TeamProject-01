#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

// 초기화 (init)
HRESULT sceneManager::init()
{
	// 초기화 종료
	return S_OK;
}

// 해제 (release)
void sceneManager::release()
{
	// 정석적인 방법
	// miSceneList iter = _mSceneList.begin();
	// for (; iter != _mSceneList.end();)
	// {
	//	if (iter->second != NULL)
	//	{
	//		//여기서 삭제
	//		if (iter->second == _currentScene) iter->second->release();
	//		SAFE_DELETE(iter->second);
	//		iter = _mSceneList.erase(iter);
	//	}
	//	else
	//	{
	//		++iter;
	//	}
	// }
	// _mSceneList.clear();

	// C++ 고급 문법
	int a;
	float b;

	// for (auto scene in _mSceneList) (지금은 사용 불가)
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
}

// 업데이트 (update)
void sceneManager::update()
{
	// 현재 씬이 존재하면 해당하는 씬을 업데이트
	if (_currentScene) _currentScene->update();
}

// 렌더 (render)
void sceneManager::render()
{
	// 현재 씬이 존재하면 해당하는 씬을 렌더
	if (_currentScene) _currentScene->render();
}

// 씬 추가
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	// 씬이 없으면 NULL 리턴
	if (!scene) return NULL;

	// 씬이 있으면 맵에 담기
	_mSceneList.insert(make_pair(sceneName, scene));
	//_mSceneList.insert(pair<string, gameNode*>(sceneName, scene));

	return scene;
}

// 씬 로드
HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	// 찾지 못했을 경우 E_FAIL 리턴
	if (find == _mSceneList.end()) return E_FAIL;

	// 바꾸려는 씬과 현재 씬이 같을 경우 E_FAIL 리턴
	if (find->second == _currentScene) return E_FAIL;

	// 문제가 없을 경우 씬을 변경 처리
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
