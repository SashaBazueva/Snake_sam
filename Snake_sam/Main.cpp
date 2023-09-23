#include <iostream>
#include <windows.h>

const short WIDTH = 17;
const short HIGHT = 10;

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
			gotoxy(0, 0);
			std::cout << "~ length: " << snakeLen << std::endl;
			time = clock();
			std::cout << map;
		}

	}
	return 0;
}