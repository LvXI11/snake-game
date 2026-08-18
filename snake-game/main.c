#include<stdio.h>
#include<Windows.h>
#include "snake.h"
#include<stdlib.h>
#include<time.h>
HANDLE h_out;
int score = 0;
Point food;
int main(void) {
	h_out = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄，供光标定位使用
	SetConsoleOutputCP(65001);               // 设置输出代码页为UTF-8，解决中文乱码
	hide_cursor();                           // 隐藏闪烁的光标
	printf("贪吃蛇准备中....\n"); 
	srand((unsigned)time(NULL));             // 播种随机数，食物位置不重复
	Snake s;
	s.len = 3;
	s.body[0].x = 10; s.body[0].y = 10;
	s.body[1].x = 9; s.body[1].y = 10;
	s.body[2].x = 8; s.body[2].y = 10;
	s.dir = RIGHT;
	spawn_food(&s);
	while (1) {
		s.dir = get_dir(s.dir);
		if (!snake_move(&s)) {
			system("cls");
			printf("\n====================\n");
			printf("     GAME OVER        \n");
			printf("     得分：%d           ", score);
			printf("\n====================\n");
			system("pause");
			break;
		}
		gotoxy(0, 0);        // 光标回到左上角，覆盖重画整屏（替代清屏，不闪烁）
		for (int y = 0; y < HEIGHT; y++) {   // 外层循环：逐行画
			for (int x = 0; x < WIDTH; x++) { // 内层循环：逐列画
				char ch = ' ';                // 默认这个格子是空格

				if (x == food.x && y == food.y)ch = '0'; // 是食物就标成0

				bool on_snake = false;        // 先假设不在蛇身上
				for (int i = 0; i < s.len; i++) { // 遍历蛇身找匹配
					if (s.body[i].x == x && s.body[i].y == y) { // 格子坐标==蛇身坐标
						on_snake = true;      // 找到了，标记
						break;                // 找到就停，不用再查
					}
				}
				if (on_snake)ch = '*';        // 在蛇身上就画*
				if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)ch = '#'; // 边框画#
				printf("%c", ch);             // 输出这个格子的字符
			}
			printf("\n");                     // 一行画完，换行
		}
		gotoxy(0, HEIGHT);    // 光标移到边框下方一行
		printf("得分：%d", score); // 打印得分
		Sleep(300);           // 停顿0.3秒，控制游戏速度
	}
	
	return 0;
}

