#include "common.h"
#include "screenOut.h"
#include "gameData.h"
#include "struct.h"

int stageLevel = 1;
int playerHealth = 10;
int money = FIRST_MONEY;
int prevPlayerHealth = 0;
int prevMoney = 0;
int cursX = 0;
int cursY = 0;
int prevShape = BLANK;
int plantArr[MAX_CURSOR_X][MAX_CURSOR_Y];
int plantIdxArr[MAX_CURSOR_X][MAX_CURSOR_Y];
int choicePlant = CURSOR;
int numOfPlant = 0;
int numOfBullet = 0;
int numOfEnemy = 0;
int enemySummonDelay = ENEMY_SUMMON_DELAY;
int enemySummonTimer = 0;
int summonInStage = 0;

PLANT* plant[MAX_PLANT_NUM];
ENEMY* enemy[MAX_ENEMY_NUM];
BULLET* bullet[MAX_BULLET_NUM];

void InitPlantAndIdxArr(void)
{
	int i, j;
	for (i = 0; i < MAX_CURSOR_Y; i++)
	{
		for (j = 0; j < MAX_CURSOR_X; j++)
		{
			plantArr[j][i] = BLANK;
			plantIdxArr[j][i] = -1;
		}
	}
}

void ShiftLeft(void)
{
	if (cursX > 0)
	{
		PrintToXY(prevShape, cursX, cursY);
		cursX--;
		prevShape = plantArr[cursX][cursY];
		PrintToXY(choicePlant, cursX, cursY);
	}
}

void ShiftRight(void)
{
	if (cursX < MAX_CURSOR_X - 1)
	{
		PrintToXY(prevShape, cursX, cursY);
		cursX++;
		prevShape = plantArr[cursX][cursY];
		PrintToXY(choicePlant, cursX, cursY);
	}
}

void ShiftUp(void)
{
	if (cursY > 0)
	{
		PrintToXY(prevShape, cursX, cursY);
		cursY--;
		prevShape = plantArr[cursX][cursY];
		PrintToXY(choicePlant, cursX, cursY);
	}
}

void ShiftDown(void)
{
	if (cursY < MAX_CURSOR_Y - 1)
	{
		PrintToXY(prevShape, cursX, cursY);
		cursY++;
		prevShape = plantArr[cursX][cursY];
		PrintToXY(choicePlant, cursX, cursY);
	}
}

void SetPlantState(void)
{
	if (choicePlant == PLANT_A)
	{
		plant[numOfPlant]->Health = A_HEALTH;
		plant[numOfPlant]->AttDelay = A_ATT_DELAY;
		plant[numOfPlant]->AttTimer = 0;
		plant[numOfPlant]->Power = A_POWER;
		plant[numOfPlant]->ShootMode = A_SHOOT_MODE;
	}

	if (choicePlant == PLANT_S)
	{
		plant[numOfPlant]->Health = S_HEALTH;
		plant[numOfPlant]->AttDelay = S_ATT_DELAY;
		plant[numOfPlant]->AttTimer = 0;
		plant[numOfPlant]->Power = S_POWER;
		plant[numOfPlant]->ShootMode = S_SHOOT_MODE;
	}

	if (choicePlant == PLANT_D)
	{
		plant[numOfPlant]->Health = D_HEALTH;
		plant[numOfPlant]->AttDelay = D_ATT_DELAY;
		plant[numOfPlant]->AttTimer = 0;
		plant[numOfPlant]->Power = D_POWER;
		plant[numOfPlant]->ShootMode = D_SHOOT_MODE;
	}

	if (choicePlant == PLANT_F)
	{
		plant[numOfPlant]->Health = F_HEALTH;
		plant[numOfPlant]->AttDelay = F_ATT_DELAY;
		plant[numOfPlant]->AttTimer = 0;
		plant[numOfPlant]->Power = F_POWER;
		plant[numOfPlant]->ShootMode = F_SHOOT_MODE;
	}

	numOfPlant++;
}

void DeletePlant(int x, int y)
{
	int i;
	int idx = plantIdxArr[x][y];
	free(plant[idx]);
	for (i = idx; i < numOfPlant - 1; i++)
	{
		plant[i] = plant[i + 1];
	}
	plant[numOfPlant - 1] = NULL;
	numOfPlant--;
	plantIdxArr[x][y] = -1;
}

void UpGradePlant(int upgradePlant)
{
	DeletePlant(cursX, cursY);
	plant[numOfPlant] = (PLANT*)malloc(sizeof(PLANT));
	plant[numOfPlant]->x = cursX;
	plant[numOfPlant]->y = cursY;
	plantIdxArr[cursX][cursY] = numOfPlant;
	if (upgradePlant == PLANT_A)
	{
		plantArr[cursX][cursY] = PLANT_UP_A;
		prevShape = PLANT_UP_A;
		plant[numOfPlant]->Health = UP_A_HEALTH;
		plant[numOfPlant]->AttDelay = UP_A_ATT_DELAY;
		plant[numOfPlant]->Power = UP_A_POWER;
		plant[numOfPlant]->ShootMode = UP_A_SHOOT_MODE;
		PrintToXY(PLANT_UP_A, cursX, cursY);
	}

	if (upgradePlant == PLANT_S)
	{
		plantArr[cursX][cursY] = PLANT_UP_S;
		prevShape = PLANT_UP_S;
		plant[numOfPlant]->Health = UP_S_HEALTH;
		plant[numOfPlant]->AttDelay = UP_S_ATT_DELAY;
		plant[numOfPlant]->Power = UP_S_POWER;
		plant[numOfPlant]->ShootMode = UP_S_SHOOT_MODE;
		PrintToXY(PLANT_UP_S, cursX, cursY);
	}

	if (upgradePlant == PLANT_D)
	{
		plantArr[cursX][cursY] = PLANT_UP_D;
		prevShape = PLANT_UP_D;
		plant[numOfPlant]->Health = UP_D_HEALTH;
		plant[numOfPlant]->AttDelay = UP_D_ATT_DELAY;
		plant[numOfPlant]->Power = UP_D_POWER;
		plant[numOfPlant]->ShootMode = UP_D_SHOOT_MODE;
		PrintToXY(PLANT_UP_D, cursX, cursY);
	}

	if (upgradePlant == PLANT_F)
	{
		plantArr[cursX][cursY] = PLANT_UP_F;
		prevShape = PLANT_UP_F;
		plant[numOfPlant]->Health = UP_F_HEALTH;
		plant[numOfPlant]->AttDelay = UP_F_ATT_DELAY;
		plant[numOfPlant]->Power = UP_F_POWER;
		plant[numOfPlant]->ShootMode = UP_F_SHOOT_MODE;
		PrintToXY(PLANT_UP_F, cursX, cursY);
	}
	numOfPlant++;
}

void SellPlant(sellPlant)
{
	DeletePlant(cursX, cursY);
	prevShape = BLANK;
	PrintToXY(BLANK, cursX, cursY);
	plantArr[cursX][cursY] = BLANK;
	if (sellPlant == PLANT_A)
		money += COST_A / 2;
	
	if (sellPlant == PLANT_S)
		money += COST_S / 2;

	if (sellPlant == PLANT_D)
		money += COST_D / 2;

	if (sellPlant == PLANT_F)
		money += COST_F / 2;
	
	if (sellPlant == PLANT_UP_A)
		money += COST_UP_A / 2;

	if (sellPlant == PLANT_UP_S)
		money += COST_UP_S / 2;

	if (sellPlant == PLANT_UP_D)
		money += COST_UP_D / 2;

	if (sellPlant == PLANT_UP_F)
		money += COST_UP_F / 2;
}

void SetChoice(void)
{
	int upgradePlant = 0;
	int sellPlant = 0;
	if (choicePlant != CURSOR)
	{
		if (choicePlant >= PLANT_A && choicePlant <= PLANT_F)
		{
			if (plantArr[cursX][cursY] == BLANK)
			{
				if (choicePlant == PLANT_A)
					money -= COST_A;
				else if (choicePlant == PLANT_S)
					money -= COST_S;
				else if (choicePlant == PLANT_D)
					money -= COST_D;
				else if (choicePlant == PLANT_F)
					money -= COST_F;
				plantArr[cursX][cursY] = choicePlant;
				plantIdxArr[cursX][cursY] = numOfPlant;
				PrintToXY(choicePlant, cursX, cursY);
				prevShape = choicePlant;

				plant[numOfPlant] = (PLANT*)malloc(sizeof(PLANT));
				plant[numOfPlant]->x = cursX;
				plant[numOfPlant]->y = cursY;
				SetPlantState();
				choicePlant = CURSOR;
			}
		}
		if (choicePlant == UPGRADE)
		{
			upgradePlant = plantArr[cursX][cursY];
			if (upgradePlant == BLANK)
				return;
			else if (upgradePlant >= PLANT_A && upgradePlant <= PLANT_F)
			{
				if (upgradePlant == PLANT_A)
					if (money >= COST_UP_A)
					{
						UpGradePlant(upgradePlant);
						choicePlant = CURSOR;
						money -= COST_UP_A;
						return;
					}
				if (upgradePlant == PLANT_S)
					if (money >= COST_UP_S)
					{
						UpGradePlant(upgradePlant);
						choicePlant = CURSOR;
						money -= COST_UP_S;
						return;
					}
				if (upgradePlant == PLANT_D)
					if (money >= COST_UP_D)
					{
						UpGradePlant(upgradePlant);
						choicePlant = CURSOR;
						money -= COST_UP_D;
						return;
					}
				if (upgradePlant == PLANT_F)
					if (money >= COST_UP_F)
					{
						UpGradePlant(upgradePlant);
						choicePlant = CURSOR;
						money -= COST_UP_F;
						return;
					}
				choicePlant = CURSOR;
			}
		}
		if (choicePlant == SELL_PLANT)
		{
			sellPlant = plantArr[cursX][cursY];
			if (sellPlant == BLANK)
				return;
			else if (sellPlant >= PLANT_A && sellPlant <= PLANT_F)
			{
				SellPlant(sellPlant);
				choicePlant = CURSOR;
			}
		}
	}
}

void ChoicePlantA(void)
{
	if (money < COST_A)
		return;
	choicePlant = PLANT_A;
	PrintToXY(choicePlant, cursX, cursY);
}

void ChoicePlantS(void)
{
	if (money < COST_S)
		return;
	choicePlant = PLANT_S;
	PrintToXY(choicePlant, cursX, cursY);
}

void ChoicePlantD(void)
{
	if (money < COST_D)
		return;
	choicePlant = PLANT_D;
	PrintToXY(choicePlant, cursX, cursY);
}

void ChoicePlantF(void)
{
	if (money < COST_F)
		return;
	choicePlant = PLANT_F;
	PrintToXY(choicePlant, cursX, cursY);
}

void ChoiceUpGrade(void)
{
	choicePlant = UPGRADE;
	PrintToXY(choicePlant, cursX, cursY);
}

void ChoiceSell(void)
{
	choicePlant = SELL_PLANT;
	PrintToXY(choicePlant, cursX, cursY);
}

void CheckShootPlantBullet(void)
{
	int i;
	for (i = 0; i < numOfPlant; i++)
	{
		if (plant[i]->AttDelay <= plant[i]->AttTimer)
		{
			if (plant[i]->ShootMode == A_SHOOT_MODE)
			{
				bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
				bullet[numOfBullet]->x = plant[i]->x + 1;
				bullet[numOfBullet]->y = plant[i]->y;
				bullet[numOfBullet]->MovDelay = BULLET_MOV_DELAY;
				bullet[numOfBullet]->MovTimer = 0;
				bullet[numOfBullet]->Power = plant[i]->Power;
				bullet[numOfBullet]->BulletMode = BULLET_ONE_HIT_MODE;
				plant[i]->AttTimer = 0;
				PrintToXY(P_BULLET, bullet[numOfBullet]->x, bullet[numOfBullet]->y);
				numOfBullet++;
			} 
			else if (plant[i]->ShootMode == S_SHOOT_MODE)
			{
				bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
				bullet[numOfBullet]->x = plant[i]->x + 1;
				bullet[numOfBullet]->y = plant[i]->y;
				bullet[numOfBullet]->MovDelay = BULLET_MOV_DELAY;
				bullet[numOfBullet]->MovTimer = 0;
				bullet[numOfBullet]->Power = plant[i]->Power;
				bullet[numOfBullet]->BulletMode = BULLET_ONE_HIT_MODE;
				plant[i]->AttTimer = S1_ATT_TIMER;
				plant[i]->ShootMode = S1_SHOOT_MODE;
				PrintToXY(P_BULLET, bullet[numOfBullet]->x, bullet[numOfBullet]->y);
				numOfBullet++;
			}
			else if (plant[i]->ShootMode == S1_SHOOT_MODE)
			{
				int tempTimer1;
				bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
				bullet[numOfBullet]->x = plant[i]->x + 1;
				bullet[numOfBullet]->y = plant[i]->y;
				bullet[numOfBullet]->MovDelay = BULLET_MOV_DELAY;
				bullet[numOfBullet]->MovTimer = 0;
				bullet[numOfBullet]->Power = plant[i]->Power;
				bullet[numOfBullet]->BulletMode = BULLET_ONE_HIT_MODE;
				plant[i]->AttTimer = S2_ATT_TIMER;
				plant[i]->ShootMode = S2_SHOOT_MODE;
				PrintToXY(P_BULLET, bullet[numOfBullet]->x, bullet[numOfBullet]->y);
				numOfBullet++;
			}
			else if (plant[i]->ShootMode == S2_SHOOT_MODE)
			{
				int tempTimer1;
				bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
				bullet[numOfBullet]->x = plant[i]->x + 1;
				bullet[numOfBullet]->y = plant[i]->y;
				bullet[numOfBullet]->MovDelay = BULLET_MOV_DELAY;
				bullet[numOfBullet]->MovTimer = 0;
				bullet[numOfBullet]->Power = plant[i]->Power;
				bullet[numOfBullet]->BulletMode = BULLET_ONE_HIT_MODE;
				plant[i]->AttTimer = 0;
				plant[i]->ShootMode = S_SHOOT_MODE;
				PrintToXY(P_BULLET, bullet[numOfBullet]->x, bullet[numOfBullet]->y);
				numOfBullet++;
			}
			else if (plant[i]->ShootMode == D_SHOOT_MODE)
			{
				int j;
				for (j = 0; j < 3; j++)
				{
					bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
					bullet[numOfBullet]->x = -10 + j;
					bullet[numOfBullet]->y = plant[i]->y;
					bullet[numOfBullet]->MovDelay = BULLET_MOV_DELAY;
					bullet[numOfBullet]->MovTimer = 0;
					bullet[numOfBullet]->Power = plant[i]->Power;
					bullet[numOfBullet]->BulletMode = BULLET_BOMB_HIT_MODE;
					numOfBullet++;
				}
				plant[i]->AttTimer = 0;
			}
			else if (plant[i]->ShootMode == F_SHOOT_MODE)
			{
				bullet[numOfBullet] = (BULLET*)malloc(sizeof(BULLET));
				bullet[numOfBullet]->x = plant[i]->x + 1;
				bullet[numOfBullet]->y = plant[i]->y;
				bullet[numOfBullet]->MovDelay = LINE_BULLET_MOV_DELAY;
				bullet[numOfBullet]->MovTimer = 0;
				bullet[numOfBullet]->Power = plant[i]->Power;
				bullet[numOfBullet]->BulletMode = BULLET_LINE_HIT_MODE;
				plant[i]->AttTimer = 0;
				PrintToXY(P_LINE, bullet[numOfBullet]->x, bullet[numOfBullet]->y);
				numOfBullet++;
			}
		}
	}
}

void DeleteBullet(int idx)
{
	int i;
	free(bullet[idx]);
	for (i = idx; i < numOfBullet - 1; i++)
	{
		bullet[i] = bullet[i + 1];
	}
	bullet[numOfBullet - 1] = NULL;
	numOfBullet--;
}

void CheckMovPlantBullet(void)
{
	int i;
	int bulletPrevShape = 0;
	for (i = 0; i < numOfBullet; i++)
	{
		if (bullet[i]->MovTimer >= bullet[i]->MovDelay)
		{
			if (bullet[i]->BulletMode == BULLET_ONE_HIT_MODE)
			{
				if (bullet[i]->x < MAX_CURSOR_X - 1)
				{
					PrintToXY(plantArr[bullet[i]->x][bullet[i]->y], bullet[i]->x, bullet[i]->y);
					bullet[i]->x++;
					PrintToXY(P_BULLET, bullet[i]->x, bullet[i]->y);
					bullet[i]->MovTimer = 0;
				}
				else if (bullet[i]->x >= MAX_CURSOR_X - 1)
				{
					PrintToXY(plantArr[bullet[i]->x][bullet[i]->y], bullet[i]->x, bullet[i]->y);
					DeleteBullet(i);
					i--;
				}
			}
			else if (bullet[i]->BulletMode == BULLET_LINE_HIT_MODE)
			{
				if (bullet[i]->x < MAX_CURSOR_X - 1)
				{
					PrintToXY(plantArr[bullet[i]->x][bullet[i]->y], bullet[i]->x, bullet[i]->y);
					bullet[i]->x++;
					PrintToXY(P_LINE, bullet[i]->x, bullet[i]->y);
					bullet[i]->MovTimer = 0;
				}
				else if (bullet[i]->x >= MAX_CURSOR_X - 1)
				{
					PrintToXY(plantArr[bullet[i]->x][bullet[i]->y], bullet[i]->x, bullet[i]->y);
					DeleteBullet(i);
					i--;
				}
			}
			else if (bullet[i]->BulletMode == BULLET_BOMB_HIT_MODE)
			{
				bullet[i]->x += 10 + BOMB_RANGE;
				PrintToXY(P_BOMB, bullet[i]->x, bullet[i]->y);
				bullet[i]->MovTimer = 0;
				bullet[i]->BulletMode = BULLET_BOMB_HIT_MODE_NEXT;
			}
			else if (bullet[i]->BulletMode == BULLET_BOMB_HIT_MODE_NEXT)
			{
				PrintToXY(plantArr[bullet[i]->x][bullet[i]->y], bullet[i]->x, bullet[i]->y);
				DeleteBullet(i);
				i--;
			}
		}
	}
}

void DeleteEnemy(int idx)
{
	int i;
	free(enemy[idx]);
	for (i = idx; i < numOfEnemy - 1; i++)
	{
		enemy[i] = enemy[i + 1];
	}
	enemy[numOfEnemy - 1] = NULL;
	numOfEnemy--;
}

void CheckSummonEnemy(void)
{
	int i;
	int tempHealth;
	int tempY;
	if (enemySummonTimer >= enemySummonDelay)
	{
		summonInStage++;
		if (summonInStage>=10)
		{
			stageLevel++;
			if (stageLevel == 6)
			{
				Goto(8, 6);
				printf(" - GAME CLEAR -");
				while (1);
			}
			summonInStage = 0;
			enemySummonDelay -= (stageLevel - 1) * 100;
		}
		if (stageLevel <= 3)
			tempHealth = rand() % (stageLevel + 2) + 1;
		else
			tempHealth = rand() % 5 + 1;
		if (tempHealth == 1)
		{
			tempY = rand() % 6;
			for (i = 0; i < 3; i++)
			{
				enemy[numOfEnemy] = (ENEMY*)malloc(sizeof(ENEMY));
				enemy[numOfEnemy]->Health = tempHealth;
				enemy[numOfEnemy]->x = MAX_CURSOR_X - 3 + i;
				enemy[numOfEnemy]->y = tempY;
				enemy[numOfEnemy]->Power = GRADE1_ENEMY_POWER;
				enemy[numOfEnemy]->MovDelay = ENEMY_MOV_DELAY;
				enemy[numOfEnemy]->MovTimer = 0;
				enemy[numOfEnemy]->Money = 10;
				PrintToXY(ENEMY1, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
				numOfEnemy++;
			}
			enemySummonTimer = 0;
		}
		else if (tempHealth == 2)
		{
			enemy[numOfEnemy] = (ENEMY*)malloc(sizeof(ENEMY));
			enemy[numOfEnemy]->Health = tempHealth;
			enemy[numOfEnemy]->x = MAX_CURSOR_X - 1;
			enemy[numOfEnemy]->y = rand() % 6;
			enemy[numOfEnemy]->Power = GRADE2_ENEMY_POWER;
			enemy[numOfEnemy]->MovDelay = ENEMY2_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->Money = 20;
			PrintToXY(ENEMY2, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
			numOfEnemy++;
			enemySummonTimer = 0;
		}
		else if (tempHealth == 3)
		{
			enemy[numOfEnemy] = (ENEMY*)malloc(sizeof(ENEMY));
			enemy[numOfEnemy]->Health = tempHealth;
			enemy[numOfEnemy]->x = MAX_CURSOR_X - 1;
			enemy[numOfEnemy]->y = rand() % 6;
			enemy[numOfEnemy]->Power = GRADE3_ENEMY_POWER;
			enemy[numOfEnemy]->MovDelay = ENEMY_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->Money = 25;
			PrintToXY(ENEMY3, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
			numOfEnemy++;
			enemySummonTimer = 0;
		}
		else if (tempHealth == 4)
		{
			enemy[numOfEnemy] = (ENEMY*)malloc(sizeof(ENEMY));
			enemy[numOfEnemy]->Health = tempHealth;
			enemy[numOfEnemy]->x = MAX_CURSOR_X - 1;
			enemy[numOfEnemy]->y = rand() % 6;
			enemy[numOfEnemy]->Power = GRADE4_ENEMY_POWER;
			enemy[numOfEnemy]->MovDelay = ENEMY_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->Money = 35;
			PrintToXY(ENEMY4, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
			numOfEnemy++;
			enemySummonTimer = 0;
		}
		else if (tempHealth == 5)
		{
			enemy[numOfEnemy] = (ENEMY*)malloc(sizeof(ENEMY));
			enemy[numOfEnemy]->Health = tempHealth;
			enemy[numOfEnemy]->x = MAX_CURSOR_X - 1;
			enemy[numOfEnemy]->y = rand() % 6;
			enemy[numOfEnemy]->Power = GRADE5_ENEMY_POWER;
			enemy[numOfEnemy]->MovDelay = ENEMY_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->Money = 45;
			PrintToXY(ENEMY5, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
			numOfEnemy++;
			enemySummonTimer = 0;
		}
	}
}

void CheckMovEnemy(void)
{
	int i;
	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->MovTimer >= enemy[i]->MovDelay)
		{
			if (enemy[i]->x>0)
			{
				PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
				enemy[i]->x--;
				PrintToXY(ENEMY1 + enemy[i]->Health, enemy[i]->x, enemy[i]->y);
				enemy[i]->MovTimer = 0;
			}
			else if (enemy[i]->x == 0)
			{
				playerHealth -= enemy[i]->Power;
				PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
				DeleteEnemy(i);
			}
		}
	}
}

void CheckPlantBulletAndEnemyCollision(void)
{
	int i, j;
	for (i = 0; i < numOfEnemy; i++)
	{
		for (j = 0; j < numOfBullet; j++)
		{
			if (bullet[j]->BulletMode == BULLET_ONE_HIT_MODE)
			{
				if ((enemy[i]->x == bullet[j]->x) && (enemy[i]->y == bullet[j]->y))
				{
					enemy[i]->Health -= bullet[j]->Power;
					DeleteBullet(j);
					j--;
					if (enemy[i]->Health <= 0)
					{
						money += enemy[i]->Money;
						PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
						DeleteEnemy(i);
						i--;
						break;
					}
					PrintToXY(ENEMY1 + enemy[i]->Health - 1, enemy[i]->x, enemy[i]->y);
				}
			}
			else
			{
				if ((enemy[i]->x == bullet[j]->x) && (enemy[i]->y == bullet[j]->y))
				{
					enemy[i]->Health -= bullet[j]->Power;
					if (enemy[i]->Health <= 0)
					{
						money += enemy[i]->Money;
						PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
						DeleteEnemy(i);
						i--;
						break;
					}
				}
			}
		}
	}
}

void CheckPlantAndEnemyCollision(void)
{
	int i, j;
	for (i = 0; i < numOfEnemy; i++)
	{
		for (j = 0; j < numOfPlant; j++)
		{
			if ((enemy[i]->x == plant[j]->x) && (enemy[i]->y == plant[j]->y))
			{
				plant[j]->Health -= enemy[i]->Power;
				if (plant[j]->Health <= 0)
				{
					plantArr[plant[j]->x][plant[j]->y];
					PrintToXY(BLANK, plant[j]->x, plant[j]->y);
					DeletePlant(plant[j]->x, plant[j]->y);
					j--;
				}
			}
		}
	}
}

void UpTimer(void)
{
	int i;
	for (i = 0; i < numOfPlant; i++)
	{
		if (plant[i]->AttTimer <= plant[i]->AttDelay)
			plant[i]->AttTimer++;
	}
	for (i = 0; i < numOfBullet; i++)
	{
		if (bullet[i]->MovTimer <= bullet[i]->MovDelay)
			bullet[i]->MovTimer++;
	}
	if (enemySummonTimer <= enemySummonDelay)
		enemySummonTimer++;
	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->MovTimer <= enemy[i]->MovDelay)
			enemy[i]->MovTimer++;
	}
}

void PrintPlayerState(void)
{
	Goto(0, COL_LEN + 3);
	printf("StageLevel : %d\nHealth : %d\nMoney : %d", stageLevel, playerHealth, money);
}

void CheckPlayerStateChange(void)
{
	if (prevPlayerHealth != playerHealth || prevMoney != money)
		PrintPlayerState();
	if (playerHealth <= 0)
	{
		system("cls");
		Goto(8, 6);
		printf(" - GAME OVER - ");
		while (1);
	}
}

void ProcessCheck(void)
{
	CheckShootPlantBullet();
	CheckMovPlantBullet();
	CheckPlantBulletAndEnemyCollision();
	CheckPlantAndEnemyCollision();
	CheckSummonEnemy();
	CheckMovEnemy();
	UpTimer();
	CheckPlayerStateChange();
}