#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define MAP_SIZE_W 10
#define MAP_SIZE_H 20
#define HALF_W 15
#define HALF_H 10
#define EXIT 100

#define WALL 5
#define EMPTY 0
#define BLOCK 1

#define UP 72
#define LEFT 75
#define RIGHRT 77
#define SPACE 32
#define ESC 27
#define DOWN 80

typedef char MData;

typedef struct _currentLocation {
	int x;
	int y;
} Location;


//hide cursor
void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

//move cursor
void goToXy(int x, int y) {
	COORD P;
	P.X = 2 * x;
	P.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), P);
}

//get keyboard input
int getKeyDown() {
	if (_kbhit()) return _getch();
	else return -1;
}

//////////////////////////////////////////////////////////////////////
void drawWall(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 11);

	for (h = 0; h <= MAP_SIZE_H + 1; h++) {
		for (w = 0; w <= MAP_SIZE_W + 1; w++) {
			goToXy(w + 1, h + 1);
			if (h == 0 || w == 0 || h == MAP_SIZE_H + 1 || w == MAP_SIZE_W + 1)
				printf("¡á");
		}
		printf("\n");
	}
	goToXy(HALF_W, 1);
	SetConsoleTextAttribute(hand, 14);
	printf("<NEXT>");
	SetConsoleTextAttribute(hand, 11);

	for (h = 2; h <= 7; h++) {
		for (w = HALF_W; w <= HALF_W + 5; w++) {
			goToXy(w, h);
			if (h == 2 || w == HALF_W || h == 7 || w == HALF_W + 5)
				printf("¡á");
		}
	}
	goToXy(HALF_W, HALF_H + 1);
	printf("BEST : ");
	goToXy(HALF_W, HALF_H + 2);
	printf("SCORE : ");
	goToXy(HALF_W, MAP_SIZE_H + 2);
	printf("<Exit : 't' / Pause : 'p'>");
	SetConsoleTextAttribute(hand, 7);
}

int drawFrontMenu() {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int keyInput;
	goToXy(1, 2);
	SetConsoleTextAttribute(hand, 11);
	printf("=====================================================");
	goToXy(1, 3);
	SetConsoleTextAttribute(hand, 14);
	printf("=================== T E T R I S =====================");
	SetConsoleTextAttribute(hand, 11);
	goToXy(1, 4);
	printf("=====================================================\n");

	SetConsoleTextAttribute(hand, 14);
	goToXy(2, 6);
	printf("Left : ¡ç \n");
	goToXy(2, 7);
	printf("Right : ¡æ \n");
	goToXy(2, 8);
	printf("Rotation : ¡è \n");
	goToXy(2, 9);
	printf("Down: space \n");
	goToXy(2, 10);
	printf("Exit: 't' \n");

	SetConsoleTextAttribute(hand, 14);
	goToXy(15, 20);
	printf(" >> Made by BlockDMask.");
	goToXy(15, 21);
	printf(" >> BlockDMask@gmail.com");

	while (1) {
		keyInput = getKeyDown();
		if (keyInput == 's' || keyInput == 'S') break;
		if (keyInput == 't' || keyInput == 'T') break;

		goToXy(7, 15);
		SetConsoleTextAttribute(hand, 11);
		printf(" === press 's' to start ===");
		SetConsoleTextAttribute(hand, 7);
		Sleep(1000 / 2);
		goToXy(7, 15);
		printf("                            ");
		Sleep(1000 / 2);
	}

	return keyInput;
}

void drawMap(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (h = 0; h < MAP_SIZE_H; h++) {
		for (w = 0; w < MAP_SIZE_W; w++) {
			goToXy(w + 2, h + 2);
			if (map[h][w] == EMPTY) {
				printf("¡¤");
			}
			else if (map[h][w] == BLOCK) {
				SetConsoleTextAttribute(hand, 14);
				printf("¡á");
				SetConsoleTextAttribute(hand, 7);
			}
		}
		printf("\n");
	}
}

//show next shap , score, time, best score.
void drawSubMap(int best, int score) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	goToXy(HALF_W + 4, HALF_H + 1);
	printf("%4d", best);
	goToXy(HALF_W + 4, HALF_H + 2);
	printf("%4d", score);
	SetConsoleTextAttribute(hand, 7);
}

void drawSubShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4]) { 
	int h, w;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (h = 3; h <= 6; h++) {
		for (w = HALF_W + 1; w <= HALF_W + 4; w++) {
			goToXy(w, h);
			printf(" ");
		}
	}

	for (h = 3; h <= 6; h++) {
		for (w = HALF_W + 1; w <= HALF_W + 4; w++) {
			if(shape[h-3][w - HALF_W - 1] == BLOCK) {
				goToXy(w, h);
				SetConsoleTextAttribute(hand, 14);
				printf("¡á");
				SetConsoleTextAttribute(hand, 7);
			}
		}
	}
}

void drawShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int shape[4][4], Location curLoc) {
	int h, w;

	for (h = 0; h < 4; h++) {
		for (w = 0; w < 4; w++) {
			if (shape[h][w] == BLOCK) {
				map[curLoc.y + h][curLoc.x + w] = BLOCK;
				//goToXy(curLoc.x + w + 2, curLoc.y + h + 2);
				printf("¡á");
			}
		}
	}
}

void startTime() {
	int i;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < 3; i++) {
		goToXy(2, 0);
		SetConsoleTextAttribute(hand, 14);
		printf("Start : %d sec", 3 - i);
		SetConsoleTextAttribute(hand, 7);
		Sleep(1000);
	}
	goToXy(2, 0);
	printf("                       ");
}

void mapInit(MData map[MAP_SIZE_H][MAP_SIZE_W]) {
	int h, w = 0;
	for (h = 0; h < MAP_SIZE_H; h++) {
		for (w = 0; w < MAP_SIZE_W; w++) {
			map[h][w] = EMPTY;
		}
	}
}

void locationInit(Location * curLoc) {
	curLoc->x = 3;
	curLoc->y = 0;
}

void copyBlock(int blockShape[4][4], int copy[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			blockShape[i][j] = copy[i][j];
		}
	}
}

void setBlock(int blockShape[4][4]) {
	int shape[7][4][4] = {
		{ {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} },
		{ {0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0} },
		{ {0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0} },
		{ {0,0,1,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0} },
		{ {0,1,0,0}, {0,1,1,0}, {0,0,1,0}, {0,0,0,0} },
		{ {0,0,0,0}, {0,1,0,0}, {0,1,1,1}, {0,0,0,0} },
		{ {0,0,0,0}, {0,1,1,1}, {0,1,0,0}, {0,0,0,0} },
	};

	srand((unsigned int)(time(NULL)));

	switch (rand() % 7) {
	case 0:
		copyBlock(blockShape, shape[0]);
		break;
	case 1:
		copyBlock(blockShape, shape[1]);
		break;
	case 2:
		copyBlock(blockShape, shape[2]);
		break;
	case 3:
		copyBlock(blockShape, shape[3]);
		break;
	case 4:
		copyBlock(blockShape, shape[4]);
		break;
	case 5:
		copyBlock(blockShape, shape[5]);
		break;
	case 6:
		copyBlock(blockShape, shape[6]);
		break;
	default : 
		break;
	}
}

//////////////////////////////////////////////////////////////////

void removeShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location* curLoc) {
	int h, w;
	for (h = 0; h < 4; h++) {
		for (w = 0; w < 4; w++) {
			if (blockShape[h][w] == BLOCK)
				map[curLoc->y + h][curLoc->x + w];
		}
	}
}

//int getShapeLeftLoc() {
//
//}









int main(void) {
	char map[MAP_SIZE_H][MAP_SIZE_W];

	drawFrontMenu();
	drawWall(map);

	return 0;
}