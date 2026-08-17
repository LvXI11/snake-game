#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>

#define WIDTH 22
#define HEIGHT 22

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
void snake_move(Snake* s);
int main(void) {
	printf("贪吃蛇准备中....\n"); 
	Snake s;
	s.len = 3;
	s.body[0].x = 10; s.body[0].y = 10;
	s.body[1].x = 9; s.body[1].y = 10;
	s.body[2].x = 8; s.body[2].y = 10;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			char ch = ' ';
			bool on_snake = false;
			for (int i = 0; i < s.len; i++) {
				if (s.body[i].x == x && s.body[i].y == y) {
					on_snake = true;
					break;
				}
			}
			if (on_snake)ch = '*';
			if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)ch = '#';
			printf("%c", ch);
		}
		printf("\n");
	}
	
	return 0;
}

void snake_move(Snake* s) {
	Point new_head = s->body[0];
	switch (s->dir) {
	case 0:new_head.y--; break;
	case 1:new_head.y++; break;
	case 2:new_head.x--; break;
	case 3:new_head.x++; break;
	}
	for (int i = s->len - 1; i > 0; i--) {
		s->body[i] = s->body[i - 1];
	}
	s->body[0] = new_head;
}