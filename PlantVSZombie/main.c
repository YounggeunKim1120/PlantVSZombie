#include "common.h"
#include "gameData.h"
#include "keyProcess.h"
#include "gameFunc.h"
#include "screenOut.h"

int main(void)
{
	srand(time(NULL));

	InitPlantAndIdxArr();

	SetGameBoard();

	RemoveCursor();

	Goto(0, 0);

	PrintToXY(CURSOR, 0, 0);

	PrintPlayerState();

	while (1)
	{
		ProcessKeyInput();
		ProcessCheck();
	}
}