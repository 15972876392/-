#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>//按键监控
#include<iostream>
using namespace std;
#define SNAKESIZE 50
struct Food
{
	int x;
	int y;
}food;
typedef Food OneSnakeNode;
struct Snake
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;
	int speed;
}snake;
struct StrMapXywh
{
	int x;
	int y;
	int width;
	int height;
}stPos;
char key = 'w';
char lastkey = 'w';
int eatFlag = 0;
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO myConsole; //光标结构体
	myConsole.dwSize = 1;			//光标百分比厚度
	myConsole.bVisible = FALSE;  //代表光标不可见
	HANDLE myhand = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前输出光标的句柄
	SetConsoleCursorInfo(myhand, &myConsole);
}

bool IsGoBack(char lastkey, char key);
void DrawMap();
void IsEatFood();
void KeyDown();
bool IsSnakeStatus();
bool IsGoodFood(Food food);
char BigToSmall(char key);
void PrintSnake();
void CreatOneFood();
void InitSnake();
void PrintSnakeStatus();
int main()
{
	stPos = {10, 5, 40, 20};
	HideCursor();
	DrawMap();
	InitSnake();
	while (1)
	{
		IsEatFood();
		Sleep(snake.speed);
		KeyDown();
		if (!IsSnakeStatus() || snake.len == 50)
		{
			break;
		}
	}
	gotoxy((stPos.width + stPos.x) / 2, (stPos.height + stPos.y) / 2);
	printf("gameover");
	system("pause");
	return 0;
}

void PrintSnake()
{
	for (int i = 0; i <= snake.len - 1; ++i)
	{
		gotoxy(snake.x[i], snake.y[i]);
		printf("*");
	}
	
}

void CreatOneFood()
{
	while (1)
	{
		srand((int)time(0));
		food.x = rand() % (stPos.width - 1) + 1 + stPos.x;
		food.y = rand() % (stPos.height - 1) + 1 + stPos.y;
		if (IsGoodFood(food))
		{
			break;
		}
	}
	gotoxy(food.x, food.y);
	printf("#");
}
void DrawMap()
{
	for (int i = stPos.x; i <= stPos.x + stPos.width; ++i)
	{
		//打印纵坐标为y,从横坐标为x起长度为width的一条横向地图线
		gotoxy(i, stPos.y);
		printf("@");
		//打印纵坐标为y+height,从横坐标为x起长度为width的一条横向地图线
		gotoxy(i, stPos.height + stPos.y);
		printf("@");
	}
	for (int j = stPos.y; j <= stPos.y + stPos.height; ++j)
	{
		//打印横坐标为x,从纵坐标为y起长度为height的一条纵向地图线
		gotoxy(stPos.x, j);
		printf("@");
		//打印横坐标为x+width,从纵坐标为y起长度为height的一条纵向地图线
		gotoxy(stPos.x + stPos.width, j);
		printf("@");
	}
}
void InitSnake()
{
	snake.len = 3;
	snake.speed = 500;
	snake.x[0] = stPos.width / 2 + stPos.x;
	snake.y[0] = stPos.height / 2 + stPos.y;
	for (size_t i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1] + 1;
	}
	PrintSnake();
	CreatOneFood();

}
bool IsGoodFood(Food food)
{
	for (int i = 0; i <= snake.len - 1; ++i)
	{
		if (snake.x[i] == food.x && snake.y[i] == food.y)
		{
			return false;
		}
	}
	return true;
}
void IsEatFood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		eatFlag = 1;
		++snake.len;
		switch (key)
		{
		case 'w':
			--snake.y[0];
			break;
		case 's':
			++snake.y[0];
			break;
		case 'a':
			--snake.x[0];
			break;
		case 'd':
			++snake.x[0];
			break;
		default:
			break;
		}
		for (int i = snake.len - 1; i >= 2; --i)
		{
			snake.x[i] = snake.x[i - 1];
			snake.y[i] = snake.y[i - 1];
		}
		snake.x[1] = food.x;
		snake.y[1] = food.y;
	}
	if (eatFlag)
	{
		CreatOneFood();
		eatFlag = 0;
	}
}

//判断蛇的运动方向和此次按键方向是否相反
bool IsGoBack(char lastkey, char key)
{
	if (lastkey == 'w' && key == 's')
	{
		return true;
	}
	if (lastkey == 'a' && key == 'd')
	{
		return true;
	}
	if (lastkey == 's' && key == 'w')
	{
		return true;
	}
	if (lastkey == 'd' && key == 'a')
	{
		return true;
	}
	return false;
}

//将按键大小写均默认小写
char BigToSmall(char key) 
{
	switch (key)
	{
	case 'w':
	case 'W':
		key = 'w';
		break;
	case 's':
	case 'S':
		key = 's';
		break;
	case 'a':
	case 'A':
		key = 'a';
		break;
	case 'd':
	case 'D':
		key = 'd';
		break;
	case 'p':
	case 'P':
		key = 'p';
		break;
	default:
		break;
	}
	return key;
}

//按键操作
void KeyDown()
{
	lastkey = key;
	if (_kbhit())
	{
		fflush(stdin);
		key = _getch();
	}
	key = BigToSmall(key);
	if (key == 'p')
	{
		for (int i = 0; i <= snake.len - 1; ++i)
		{
			gotoxy(60, 5 + i);
			printf("蛇第%d节x坐标%dy坐标%d", i + 1, snake.x[i], snake.y[i]);
		}
		cin.get();
		key = lastkey;
	}
	if (IsGoBack(lastkey, key))
	{
		OneSnakeNode temp;
		int len = snake.len / 2;
		int templen;
		for (int i = 0; i < len; ++i)
		{
			temp.x = snake.x[i];
			temp.y = snake.y[i];
			templen = snake.len - 1 - i;
			snake.x[i] = snake.x[templen];
			snake.y[i] = snake.y[templen];
			snake.x[templen] = temp.x;
			snake.y[templen] = temp.y;
		}
	}
	gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
	printf(" ");
	for (int i = snake.len - 1; i > 0; --i)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	switch (key)
	{
	case 'w':
		--snake.y[0];
		break;
	case 's':
		++snake.y[0];
		break;
	case 'a':
		--snake.x[0];
		break;
	case 'd':
		++snake.x[0];
		break;
	default:
		break;
	}
	PrintSnake();
}

//判断蛇与自身相撞或者与强相撞
bool IsSnakeStatus()
{
	if (snake.x[0] == stPos.x || snake.x[0] == stPos.x + stPos.width
		|| snake.y[0] == stPos.y || snake.y[0] == stPos.y + stPos.height)
	{
		return false;
	}
	for (int i = 1; i <= snake.len - 1; ++i)
	{
		if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
		{
			return false;
		}
	}
	return true;
}
