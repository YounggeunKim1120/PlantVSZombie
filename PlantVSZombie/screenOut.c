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
			printf("��");
		}
	}
}

void PrintToXY(int PLANT, int x, int y)
{
	Goto(2 * x, 2 * y);
	switch (PLANT) {
	case PLANT_UP_A :
		printf("��");
		break;
	case PLANT_UP_S :
		printf("��");
		break;
	case PLANT_UP_D:
		printf("��");
		break;
	case PLANT_UP_F:
		printf("��");
		break;
	case PLANT_A:
		printf("��");
		break;
	case PLANT_S:
		printf("��");
		break;
	case PLANT_D:
		printf("��");
		break;
	case PLANT_F:
		printf("��");
		break;
	case P_BULLET:
		printf("��");
		break;
	case P_BOMB:
		printf("��");
		break;
	case P_LINE:
		printf("��");
		break;
	case ENEMY1:
		printf("��");
		break;
	case ENEMY2:
		printf("��");
		break;
	case ENEMY3:
		printf("��");
		break;
	case ENEMY4:
		printf("��");
		break;
	case ENEMY5:
		printf("��");
		break;
	case UPGRADE :
		printf("��");
		break;
	case SELL_PLANT :
		printf("��");
		break;
	case CURSOR :
		printf("��");
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