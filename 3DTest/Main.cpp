#include "Game.h"
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR cmd_str, int cmd_show) {
	Game game;
	game.Init();
	game.Start(cmd_show);

	return 0;
}
