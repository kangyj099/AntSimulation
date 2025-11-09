import console;
import common;
import gameManager;
import inputManager;

int main()
{
	// 콘솔 세팅
	ConsoleSetting(Constants::c_SCREEN_width, Constants::c_SCREEN_height, "개미 시뮬레이션    ☏kang.yj099@gmail.com    ☎010-2098-5556");
	CursorSetting(0, false);
	OffQuickEditMode();

	GameManager gameManager;
	gameManager.Init();

	bool isRun = true;
	do
	{
		InputManager::GetInstance(). SwapQueues();
		isRun = GameManager::GetInstance().Update();
		GameManager::GetInstance().Draw();

		SwapScreenBuffer();
		
	} while (isRun);
}

