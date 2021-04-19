#include <Dxlib.h>

bool SysInit(void)
{
	SetGraphMode(640, 480, 32);
	ChangeWindowMode(true);
	SetWindowText("1916025_寺崎大智");
	if (DxLib_Init() == -1) return false;

	return true;
}


// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{

	if (!SysInit())return 0;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

	}

	return 1;
}

