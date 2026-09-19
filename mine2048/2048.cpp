#include <iostream>
#include <ctime>
#include <graphics.h>
using namespace std;

IMAGE bgImg;

enum
{
	CONTINUE,
	WIN,
	LOSE
};
void printMap(int map[][4], int score)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "得分：" << score << std::endl;
}
//左划
void compressLeft(int row[])
{
	int temp[4] = { 0 };
	int k = 0;
	for (int j = 0; j < 4; j++)
	{
		if (row[j] != 0)
		{
			temp[k] = row[j];
			k++;
		}
	}
	for (int j = 0; j < 4; j++)
	{
		row[j] = temp[j];
	}
}
void mergeLeft(int row[], int& score)
{
	for (int j = 0; j < 3; j++)
	{
		if (row[j] == row[j + 1] && row[j] != 0)
		{
			row[j] *= 2;
			score += row[j];
			row[j + 1] = 0;
			j++;
		}
	}
}
void moveLeft(int map[][4], int& score)
{
	for (int i = 0; i < 4; i++)
	{
		compressLeft(map[i]);
		mergeLeft(map[i], score);
		compressLeft(map[i]);
	}
}
//右划
void compressRight(int row[])
{
	int temp[4] = { 0 };
	int k = 3;
	for (int j = 3; j >= 0; j--)
	{
		if (row[j] != 0)
		{
			temp[k] = row[j];
			k--;
		}
	}
	for (int j = 0; j < 4; j++)
	{
		row[j] = temp[j];
	}
}
void mergeRight(int row[], int& score)
{
	for (int j = 3; j > 0; j--)
	{
		if (row[j] == row[j - 1] && row[j] != 0)
		{
			row[j] *= 2;
			score += row[j];
			row[j - 1] = 0;
			j--;
		}
	}
}
void moveRight(int map[][4], int& score)
{
	for (int i = 0; i < 4; i++)
	{
		compressRight(map[i]);
		mergeRight(map[i], score);
		compressRight(map[i]);
	}
}
//数组转置
void transpose(int map[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			swap(map[i][j], map[j][i]);
		}
	}
}
//上划
void moveUp(int map[][4], int& score)
{
	transpose(map);
	moveLeft(map, score);
	transpose(map);
}
//下划
void moveDown(int map[][4], int& score)
{
	transpose(map);
	moveRight(map, score);
	transpose(map);
}
void randomAdd(int map[][4])
{
	int count = 0;
	int empty[16][2];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				empty[count][0] = i;
				empty[count][1] = j;
				count++;
			}
		}
	}
	if (count == 0) return;
	int selected = rand() % count;
	int r = empty[selected][0];
	int c = empty[selected][1];
	int num;
	if (rand() % 10 < 9)
	{
		num = 2;
	}
	else
	{
		num = 4;
	}
	map[r][c] = num;
}
bool isSame(int a[][4], int b[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
bool canMove(int map[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				return true;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (map[i][j] == map[i][j + 1])
			{
				return true;
			}
			if (map[j][i] == map[j + 1][i])
			{
				return true;
			}
		}
	}
	return false;
}
void restart(int map[][4], int& score)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	randomAdd(map);
	randomAdd(map);
}
bool hasWon(int map[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 2048)
			{
				return true;
			}
		}
	}
	return false;
}
void copyMap(int source[][4], int target[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			target[i][j] = source[i][j];
		}
	}
}
void move(int map[][4], int& score, char key)
{
	if (key == 'a')
	{
		moveLeft(map, score);
	}
	else if (key == 'd')
	{
		moveRight(map, score);
	}
	else if (key == 'w')
	{
		moveUp(map, score);
	}
	else if (key == 's')
	{
		moveDown(map, score);
	}
}
int playMove(int map[][4], int& score, char key)
{
	int oldMap[4][4];
	copyMap(map, oldMap);
	move(map, score, key);
	if (!isSame(map, oldMap))
	{
		randomAdd(map);
	}
	if (hasWon(map))
	{
		return WIN;
	}
	if (!canMove(map))
	{
		return LOSE;
	}
	return CONTINUE;
}
void drawMap(int map[][4], int score)
{
	BeginBatchDraw();
	//putimage(0, 0, &bgImg); // 贴背景图片

	settextstyle(36, 0, L"黑体");
	setbkmode(TRANSPARENT);
	settextcolor(RGB(30, 90, 200)); //数字字体颜色，蓝色
	wchar_t scoreStr[30];
	swprintf_s(scoreStr, 30, L"Score: %d", score);
	outtextxy(40, 10, scoreStr);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = 40 + j * 120;
			int y = 60 + i * 120;
			int fillColor;
			if (map[i][j] == 0)
				fillColor = RGB(255, 224, 234); //空白格子浅粉
			else if (map[i][j] == 2) fillColor = RGB(180, 215, 255);
			else if (map[i][j] == 4) fillColor = RGB(145, 195, 255);
			else if (map[i][j] == 8) fillColor = RGB(110, 175, 255);
			else if (map[i][j] == 16) fillColor = RGB(80, 150, 245);
			else if (map[i][j] == 32) fillColor = RGB(55, 125, 230);
			else if (map[i][j] == 64) fillColor = RGB(35, 100, 210);
			else if (map[i][j] == 128) fillColor = RGB(20, 80, 185);
			else if (map[i][j] == 256) fillColor = RGB(12, 60, 160);
			else if (map[i][j] == 512) fillColor = RGB(8, 45, 135);
			else if (map[i][j] == 1024) fillColor = RGB(5, 30, 110);
			else if (map[i][j] == 2048) fillColor = RGB(0, 15, 85);

			setfillcolor(fillColor);
			fillrectangle(x, y, x + 100, y + 100);
			rectangle(x, y, x + 100, y + 100);

			if (map[i][j] != 0)
			{
				wchar_t buf[20];
				swprintf_s(buf, 20, L"%d", map[i][j]);
				outtextxy(x + 35, y + 35, buf);
			}
		}
	}
	FlushBatchDraw();
}





int main()
{
	initgraph(600, 700);
	//loadimage(&bgImg, L"bg.jpg", 600, 700);

	srand((unsigned)time(NULL));
	int map[4][4] = { 0 };
	int score = 0;
	while (true)
	{
		restart(map, score);
		bool gameOver = false;
		bool quit = false;
		bool win = false;
		while (!gameOver)
		{
			drawMap(map, score);
			ExMessage msg;
			getmessage(&msg);
			if (msg.message == WM_KEYDOWN)
			{
				char key = 0;
				if (msg.vkcode == 0x57) key = 'w';
				else if (msg.vkcode == 0x41) key = 'a';
				else if (msg.vkcode == 0x53) key = 's';
				else if (msg.vkcode == 0x44) key = 'd';
				else if (msg.vkcode == 0x51) key = 'q';
				if (key == 'q')
				{
					quit = true;
					break;
				}
				if (key == 'a' || key == 'd' || key == 'w' || key == 's')
				{
					int result = playMove(map, score, key);
					if (result == WIN)
					{
						win = true;
						gameOver = true;
					}
					else if (result == LOSE)
					{
						gameOver = true;
					}
				}
			}
		}
		if (quit) break;
		drawMap(map, score);
		wchar_t tip[50];
		if (win)
		{
			swprintf_s(tip, 50, L"YOU WIN! R重开 Q退出");
		}
		else
		{
			swprintf_s(tip, 50, L"GAME OVER! R重开 Q退出");
		}
		outtextxy(40, 550, tip);
		ExMessage msg;
		getmessage(&msg);
		char choice = 0;
		if (msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == 0x52) choice = 'r';
			else if (msg.vkcode == 0x51) choice = 'q';
		}
		if (choice == 'q')
		{
			break;
		}
	}
	closegraph();
	return 0;
}

