import console;
import common;
import interface;
import inputManager;

int main()
{
	// 콘솔 세팅
	ConsoleSetting(Constants::c_SCREEN_width, Constants::c_SCREEN_height, "개미 시뮬레이션    ☏kang.yj099@gmail.com    ☎010-2098-5556");
	CursorSetting(0, false);
	OffQuickEditMode();

	// 게임 매니저 초기화
	IGameManager::GetInstance().Init();

	// 인풋 매니저 초기화
	InputManager::GetInstance().Init();

	bool isRun = true;
	do
	{
		InputManager::GetInstance().SwapQueues();
		isRun = IGameManager::GetInstance().Update();
		IGameManager::GetInstance().Draw();

		SwapScreenBuffer();
		
	} while (isRun);
}
