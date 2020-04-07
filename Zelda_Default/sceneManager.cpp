#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

// �ʱ�ȭ (init)
HRESULT sceneManager::init()
{
	return S_OK;
}

// ���� (release)
void sceneManager::release()
{
	// �������� ���
	// miSceneList iter = _mSceneList.begin();
	// for (; iter != _mSceneList.end();)
	// {
	//	if (iter->second != NULL)
	//	{
	//		//���⼭ ����
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

	// C++ ���� ����
	int a;
	float b;

	// for (auto scene in _mSceneList) (������ ��� �Ұ�)
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
}

// ������Ʈ (update)
void sceneManager::update()
{
	// ���� ���� �����ϸ� �ش��ϴ� ���� ������Ʈ
	if (_currentScene) _currentScene->update();
}

// ���� (render)
void sceneManager::render()
{
	// ���� ���� �����ϸ� �ش��ϴ� ���� ����
	if (_currentScene) _currentScene->render();
}

// �� �߰�
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	// ���� ������ NULL ����
	if (!scene) return NULL;

	// ���� ������ �ʿ� ���
	_mSceneList.insert(make_pair(sceneName, scene));
	//_mSceneList.insert(pair<string, gameNode*>(sceneName, scene));

	return scene;
}

// �� �ε�
HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	// ã�� ������ ��� E_FAIL ����
	if (find == _mSceneList.end()) return E_FAIL;

	// �ٲٷ��� ���� ���� ���� ���� ��� E_FAIL ����
	if (find->second == _currentScene) return E_FAIL;

	// ������ ���� ��� ���� ���� ó��
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}