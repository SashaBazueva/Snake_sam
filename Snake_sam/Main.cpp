#include <iostream>
#include <windows.h>

const short WIDTH = 16;
const short HIGHT = 10;
const short MAX_SNAKE_LEN = (WIDTH - 3) * (HIGHT - 2);

const short LEFT = 0;
const short UP = 1;
const short RIGHT = 2;
const short DOWN = 3;


bool isRunning = true;	//Главная логическая переменная 

char map[] = {
	"###############\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"#             #\n"
	"###############\n"
};

//SNAKE
short snakeLen = 1;
char snakeHead = '0';
char snakeBody = 'O';

short snakeDir = UP;

int snakeX[MAX_SNAKE_LEN] = { WIDTH / 2 };
int snakeY[MAX_SNAKE_LEN] = { HIGHT / 2 };

int gotoxy(short x, short y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}
	

int main() {
	int time = clock();
	while (isRunning) {

		if (GetKeyState('A') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = LEFT;
			}
			else if (snakeDir != RIGHT) {
				snakeDir = LEFT;
			}
		}
		if (GetKeyState('W') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = UP;
			}
			else if (snakeDir != DOWN) {
				snakeDir = UP;
			}
		}
		if (GetKeyState('D') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = RIGHT;
			}
			else if (snakeDir != LEFT) {
				snakeDir = RIGHT;
			}
		}
		if (GetKeyState('S') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = DOWN;
			}
			else if (snakeDir != UP) {
				snakeDir = DOWN;
			}
		}

		if ((clock() - time) / CLOCKS_PER_SEC >= 1) {	
			time = clock();
			gotoxy(0, 0);
			std::cout << "~ length: " << snakeLen << std::endl;

			for (short i = snakeLen; i >= 0; --i) {
				snakeX[i + 1] = snakeX[i];
				snakeY[i + 1] = snakeY[i];
			}

			if (snakeDir == LEFT) snakeX[0]--;
			if (snakeDir == UP) snakeY[0]--;
			if (snakeDir == RIGHT) snakeX[0]++;
			if (snakeDir == DOWN) snakeY[0]++;
			
			for (short i = 0; i < snakeLen; i++) {
				if (i == 0) {
					map[snakeY[i] * WIDTH + snakeX[i]] = snakeHead;
					std::cout << "head is on " << snakeY[i] * WIDTH + snakeX[i] << std::endl;
					continue;
				}
				map[snakeY[i] * WIDTH + snakeX[i]] = snakeBody;
				std::cout << "element " << i << " is on " << snakeY[i] * WIDTH + snakeX[i] << std::endl;
			}

			std::cout << map;

			for (short i = 0; i < snakeLen; i++) {
				map[snakeY[i] * WIDTH + snakeX[i]] = ' ';
			}
			
			
		}

	}
	return 0;
}