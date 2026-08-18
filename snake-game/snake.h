#pragma once
#define WIDTH 22
#define HEIGHT 22
#include<stdbool.h>
typedef struct {
	int x;
	int y;
}Point;

typedef enum {
	UP, DOWN, LEFT, RIGHT
}Dir;

#define MAXLEN 400

typedef struct {
	Point body[MAXLEN];
	int len;
	Dir dir;
}Snake;
#ifndef SNAKE_H
#define SNAKE_H
bool snake_move(Snake* s);     // 移动蛇，返回是否安全
Dir get_dir(Dir current);      // 读取方向键
void spawn_food(Snake* s);     // 生成食物
bool collision_test(Snake* s, Point new_head); // 碰撞检测
void gotoxy(int x, int y);     // 光标定位到坐标(x,y)
void hide_cursor(void);        // 隐藏光标
#endif 