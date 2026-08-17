#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

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
Point food;
int score=0;

void snake_move(Snake* s);
Dir get_dir(Dir current);
void spawn_food(Snake* s);

int main(void) {
	printf("贪吃蛇准备中....\n"); 
	Snake s;
	s.len = 3;
	s.body[0].x = 10; s.body[0].y = 10;
	s.body[1].x = 9; s.body[1].y = 10;
	s.body[2].x = 8; s.body[2].y = 10;
	s.dir = RIGHT;
	spawn_food(&s);
	while (1) {
		s.dir = get_dir(s.dir);
		snake_move(&s);
		system("cls");
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				char ch = ' ';

				if (x == food.x && y == food.y)ch = '0';

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
		printf("得分：%d", score);
		Sleep(400);
	}
	
	return 0;
}

void snake_move(Snake* s) {
	Point new_head = s->body[0];
	switch (s->dir) {
	case UP:new_head.y--; break;
	case DOWN:new_head.y++; break;
	case LEFT:new_head.x--; break;
	case RIGHT:new_head.x++; break;
	}
	bool ate=false;
	if (new_head.x == food.x && new_head.y == food.y)ate = true;
	if (ate) {
		s->len++;
		score++;
		spawn_food(s);
	}
	for (int i = s->len - 1; i > 0; i--) {
		s->body[i] = s->body[i - 1];
	}
	s->body[0] = new_head;
}

Dir get_dir(Dir current) {
	Dir new=current;
	if (_kbhit()) {
		int key = _getch();

		if (key == 224 || key == 0) {
			key = _getch();
			switch (key) {
			case 72:new=UP; break;
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
void spawn_food(Snake *s) {
	srand((unsigned)time(NULL));
	Point p;
	p.x = rand() % 20 + 1;
	p.y = rand() % 20 + 1;
	int i = s->len;
	do {
		if (s->body[i].x == p.x && s->body[i].y == p.y) {

		}
	} while ();
}