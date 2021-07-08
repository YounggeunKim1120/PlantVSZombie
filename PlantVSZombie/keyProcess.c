#include "common.h"

#define SYS_DELAY 10

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32

void Goto(int x, int y)
{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ProcessKeyInput(void)
{
	int i;
	int key;


	if (_kbhit() != 0)
	{
		key = getch();
		if (key == 224 || key == 0)
		{
			key = _getch();

			switch (key)
			{
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				ShiftUp();
				break;
			case DOWN:
				ShiftDown();
				break;
			}
		}

		switch (key)
		{
		case SPACE:
			SetChoice();
			break;
		case 'q':
			ChoiceUpGrade();
			break;		
		case 'w':
			ChoiceSell();
			break;
		case 'a' :
			ChoicePlantA();
			break;
		case 's':
			ChoicePlantS();
			break;
		case 'd':
			ChoicePlantD();
			break;
		case 'f':
			ChoicePlantF();
			break;
		}
	}

	Sleep(SYS_DELAY);
}