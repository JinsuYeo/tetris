#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

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
};


//hide cursor
void hideCursor() {
	//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void goToXy(int x, int y) {
	COORD P;
}




int main(void) {


	return 0;
}