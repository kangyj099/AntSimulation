import console;
import common;
import gameManager;

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
		isRun = gameManager.Update();
		gameManager.Draw();

		SwapScreenBuffer();
		
	} while (isRun);
}

