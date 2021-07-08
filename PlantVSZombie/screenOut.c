#include "common.h"
#include "gameData.h"
#include "keyProcess.h"

void SetGameBoard(void)
{
	int i, j;
	for (i = 1; i < COL_LEN; i += 2)
	{
		Goto(0, i);
		for (j = 0; j < ROW_LEN; j++)
		{
			printf("¦¬");
		}
	}
}

void PrintToXY(int PLANT, int x, int y)
{
	Goto(2 * x, 2 * y);
	switch (PLANT) {
	case PLANT_UP_A :
		printf("¢»");
		break;
	case PLANT_UP_S :
		printf("¡Þ");
		break;
	case PLANT_UP_D:
		printf("¢½");
		break;
	case PLANT_UP_F:
		printf("¢¿");
		break;
	case PLANT_A:
		printf("¢¼");
		break;
	case PLANT_S:
		printf("¡ß");
		break;
	case PLANT_D:
		printf("¢¾");
		break;
	case PLANT_F:
		printf("¢À");
		break;
	case P_BULLET:
		printf("£ª");
		break;
	case P_BOMB:
		printf("¢Í");
		break;
	case P_LINE:
		printf("¡í");
		break;
	case ENEMY1:
		printf("¨ç");
		break;
	case ENEMY2:
		printf("¨è");
		break;
	case ENEMY3:
		printf("¨é");
		break;
	case ENEMY4:
		printf("¨ê");
		break;
	case ENEMY5:
		printf("¨ë");
		break;
	case UPGRADE :
		printf("¡è");
		break;
	case SELL_PLANT :
		printf("£¤");
		break;
	case CURSOR :
		printf("¡Ø");
		break;
	case BLANK :
		printf("  ");
		break;
	}
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}