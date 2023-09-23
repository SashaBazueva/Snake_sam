#include <iostream>
#include <windows.h>

const short WIDTH = 16;
const short HIGHT = 10;
const short MAX_SNAKE_LEN = (WIDTH - 3) * (HIGHT - 2);

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

int snakeX[MAX_SNAKE_LEN] = { WIDTH / 2 };
int snakeY[MAX_SNAKE_LEN] = { HIGHT / 2 };

int gotoxy(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}
	

int main() {
	int time = clock();
	while (isRunning) {

		if ((clock() - time) / CLOCKS_PER_SEC >= 1) {	
			time = clock();
			gotoxy(0, 0);
			std::cout << "~ length: " << snakeLen << std::endl;

			for (short i = 0; i < snakeLen; i++){
				map[snakeY[i] * WIDTH + snakeX[i]] = snakeHead;
			}

			std::cout << map;
		}

	}
	return 0;
}