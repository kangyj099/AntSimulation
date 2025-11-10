module interfaces;

import gameManager;

IGameManager& IGameManager::GetInstance()
{
	// 싱글톤 인스턴스 반환
	return GameManager::Singleton::GetInstance();
}