#include "snake.h"
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
extern Point food;
extern int score;
extern HANDLE h_out;
bool snake_move(Snake* s) {
	Point new_head = s->body[0];  // 先复制蛇头坐标，作为新头的基础
	switch (s->dir) {             // 根据方向修改新头坐标
	case UP:new_head.y--; break;  // 上：y减1（屏幕y向上是负方向）
	case DOWN:new_head.y++; break; // 下：y加1
	case LEFT:new_head.x--; break; // 左：x减1
	case RIGHT:new_head.x++; break;// 右：x加1
	}
	if (collision_test(s, new_head)) // 检查新头是否会撞墙/撞自己
		return false;              // 撞了就返回假，本次不移动
	bool ate = false;                // 先假设没吃到食物
	if (new_head.x == food.x && new_head.y == food.y)ate = true; // 新头在食物上=吃到
	if (ate) {                     // 如果吃到了
		s->len++;                  // 蛇变长一节（移动循环会多保留一格）
		score++;                   // 得分加1
		spawn_food(s);             // 重新生成一个新食物
	}
	for (int i = s->len - 1; i > 0; i--) { // 从尾巴向头逐个移动
		s->body[i] = s->body[i - 1];  // 每一节顶到前一节的位置
	}
	s->body[0] = new_head;         // 新蛇头放回第0格
	return true;                   // 安全走完，返回真
}

void gotoxy(int x, int y) {       // 光标定位函数
	COORD pos;                     // 定义一个坐标结构体
	pos.X = (SHORT)x;              // 填入横坐标X
	pos.Y = (SHORT)y;              // 填入纵坐标Y
	SetConsoleCursorPosition(h_out, pos); // 把光标移到该位置
}

void hide_cursor(void) {          // 隐藏光标函数
	CONSOLE_CURSOR_INFO info;      // 定义光标信息结构体
	info.dwSize = 1;               // 光标占的格数（1~100）
	info.bVisible = FALSE;         // 可见性设为假=隐藏
	SetConsoleCursorInfo(h_out, &info); // 应用设置
}

Dir get_dir(Dir current) {
	Dir new = current;
	if (_kbhit()) {
		int key = _getch();

		if (key == 224 || key == 0) {
			key = _getch();
			switch (key) {
			case 72:new = UP; break;
			case 80:new = DOWN; break;
			case 75:new = LEFT; break;
			case 77:new = RIGHT; break;
			}
		}
		else {
			switch (key) {
			case 'w':case 'W':new = UP; break;
			case 's':case 'S':new = DOWN; break;
			case 'a':case 'A':new = LEFT; break;
			case 'd':case 'D':new = RIGHT; break;
			}
		}
		if ((current == LEFT && new == RIGHT) ||
			(current == RIGHT && new == LEFT) ||
			(current == UP && new == DOWN) ||
			(current == DOWN && new == UP))
			return current;
		return new;
	}
	return  current;
}
void spawn_food(Snake* s) {
	Point p;
	bool on_food;
	do {
		p.x = rand() % 20 + 1;
		p.y = rand() % 20 + 1;
		on_food = false;
		for (int i = 0; i < s->len; i++) {
			if (p.x == s->body[i].x && p.y == s->body[i].y) {
				on_food = true;
				break;
			}
		}
	} while (on_food);
	food = p;
}

bool collision_test(Snake* s, Point new_head) {
	if (new_head.x < 1 || new_head.x>20 ||
		new_head.y < 1 || new_head.y>20)
		return true;
	for (int i = 1; i < s->len; i++) {
		if (new_head.x == s->body[i].x && new_head.y == s->body[i].y) {
			return true;
		}
	}
	return false;
}