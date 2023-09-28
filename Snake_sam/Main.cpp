#include <iostream>
#include <windows.h>
#include <conio.h>

const short WIDTH = 16;
const short HIGHT = 10;
const short MAX_SNAKE_LEN = (WIDTH - 3) * (HIGHT - 2);

//Управление(задаем направление в управлении для устремленного движения по направленному вектору)) )
const short LEFT = 0;
const short UP = 1;
const short RIGHT = 2;
const short DOWN = 3;

bool isRunning = true;	//Главная логическая переменная для игры

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
char snakeUp = '^';
char snakeLeft = '<';
char snakeDown = 'v';
char snakeRigth = '>';
char snakeHead = snakeUp;
char snakeBody = 'O';

short snakeDir = UP;

int snakeX[MAX_SNAKE_LEN] = { WIDTH / 2 };
int snakeY[MAX_SNAKE_LEN] = { HIGHT / 2 };
int snakePos[MAX_SNAKE_LEN] = {};

//FRUIT
char fruit = '*';
short fruitPos;
bool isFruitExist = false;

//Метод для переправления курсора по координатам X и Y
int gotoxy(short x, short y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}	

int main() {
	int time = clock();
	while (isRunning) {	//Главный цикл игры

		//Постоянная ассинхронная проверка на нажатие кнопок клавиатуры и изменение направления движения змейки
		if (GetKeyState('A') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = LEFT;
				snakeHead = snakeLeft;
			}
			else if (snakeDir != RIGHT) {
				snakeDir = LEFT;
				snakeHead = snakeLeft;
			}
		}
		if (GetKeyState('W') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = UP;
				snakeHead = snakeUp;
			}
			else if (snakeDir != DOWN) {
				snakeDir = UP;
				snakeHead = snakeUp;
			}
		}
		if (GetKeyState('D') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = RIGHT;
				snakeHead = snakeRigth;
			}
			else if (snakeDir != LEFT) {
				snakeDir = RIGHT;
				snakeHead = snakeRigth;
			}
		}
		if (GetKeyState('S') & 0x8000) {
			if (snakeLen == 1) {
				snakeDir = DOWN;
				snakeHead = snakeDown;
			}
			else if (snakeDir != UP) {
				snakeDir = DOWN;
				snakeHead = snakeDown;
			}
		}

		//Отрисовка карты через каждую секунду
		if ((clock() - time) / CLOCKS_PER_SEC >= 0.7) {	
			time = clock();
			gotoxy(0, 0);
			std::cout << "~ length: " << snakeLen << std::endl;

			//Координаты тела змейки
			for (short i = snakeLen; i >= 0; --i) {
				snakeX[i + 1] = snakeX[i];
				snakeY[i + 1] = snakeY[i];
			}

			//Перемещение змейки
			if (snakeDir == LEFT) snakeX[0]--;
			if (snakeDir == UP) snakeY[0]--;
			if (snakeDir == RIGHT) snakeX[0]++;
			if (snakeDir == DOWN) snakeY[0]++;

			//Создание фрукта
			if (!isFruitExist) {
				while (!isFruitExist) {
					bool isFree = true;
					fruitPos = (2 + rand() % (WIDTH - 5)) + (2 + rand() % (HIGHT - 4)) * WIDTH;
					for (short i = 0; i < snakeLen; i++) {
						if (fruitPos == snakeY[i] * WIDTH + snakeX[i]) {
							isFree = false;
						}
					}
					if(isFree)isFruitExist = true;
				}
			}

			//Логика поедания фрукта
			if (snakeY[0] * WIDTH + snakeX[0] == fruitPos) {
				snakeLen++;
				isFruitExist = false;
			}

			if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == WIDTH - 2 || snakeY[0] == HIGHT - 1) {
				isRunning = false;
			}
			for (short i = 1; i < snakeLen; i++) {
				if (snakeY[0] * WIDTH + snakeX[0] == snakeY[i] * WIDTH + snakeX[i]) isRunning = false;
			}

			//Отрисовка фрукта на карте
			map[fruitPos] = fruit;

			//Отрисовка змейки на карте
			for (short i = 0; i < snakeLen; i++) {
				if (i == 0) {
					map[snakeY[i] * WIDTH + snakeX[i]] = snakeHead;
					continue;
				}
				map[snakeY[i] * WIDTH + snakeX[i]] = snakeBody;
			}

			//Отрисовка карты
			std::cout << map;

			//Очищение карты
			for (short i = 0; i < snakeLen; i++) {
				map[snakeY[i] * WIDTH + snakeX[i]] = ' ';
			}
			
		}

	}

	gotoxy(2, HIGHT / 2);
	std::cout << "YOUR SCORE \n";
	gotoxy(5, HIGHT / 2 + 1);
	std::cout << "IS " << snakeLen << " !" << std::endl;
	gotoxy(0, HIGHT + 1);
	Sleep(30000);
	return 0;
}