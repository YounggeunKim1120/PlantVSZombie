#ifndef __STRUCT_H_
#define __STRUCT_H_


typedef struct _PLANT {
	int x;
	int y;
	int AttDelay;
	int AttTimer;
	int Power;
	int Health;
	int ShootMode;
} PLANT;

typedef struct _ENEMY {
	int x;
	int y;
	int Money;
	int MovDelay;
	int MovTimer;
	int Power;
	int Health;
} ENEMY;

typedef struct _BULLET {
	int x;
	int y;
	int MovDelay;
	int MovTimer;
	int Power;
	int BulletMode;
} BULLET;
#endif 