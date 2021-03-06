#include "stdafx.h"

//키보드 값
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27

#define W 25
#define H 4

#define BOARD_W 10 //보드 가로
#define BOARD_H 22 //보드 세로

#define randomize() srand((unsigned)time(NULL)) //난수 초기화
#define random(n) (rand() % (n))                //0~n까지의 난수 발생

enum { EASY, NORMAL, HARD };

int board[100][100]; //보드
int eventBoard[30][30];
const char *Tile[] = { "  ","■","□", "▣" }; //블럭 모양
static int ScoreBoard[6] = { 0, 7, 15, 23, 40, 70 };
int level, tot;
int Score, BlockNum;
int maxScore = 40, tmp = 0;
int check;
bool down = false;

int x, y, rotation, px, py; //블럭의 위치 변수
int randomBlock, randomBlock1;
//다음블럭, 지금나올블럭

struct Point {
	int x, y;
};

Point Block[][4][4] = {
	{ { 0,0,1,0,2,0,-1,0 },{ 0,0,0,1,0,-1,0,-2 },{ 0,0,1,0,2,0,-1,0 },{ 0,0,0,1,0,-1,0,-2 } },
	{ { 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 } },
	{ { 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 },{ 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 } },
	{ { 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 },{ 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 } },
	{ { 0,0,-1,0,1,0,-1,-1 },{ 0,0,0,-1,0,1,-1,1 },{ 0,0,-1,0,1,0,1,1 },{ 0,0,0,-1,0,1,1,-1 } },
	{ { 0,0,1,0,-1,0,1,-1 },{ 0,0,0,1,0,-1,-1,-1 },{ 0,0,1,0,-1,0,-1,1 },{ 0,0,0,-1,0,1,1,1 } },
	{ { 0,0,-1,0,1,0,0,1 },{ 0,0,0,-1,0,1,1,0 },{ 0,0,-1,0,1,0,0,-1 },{ 0,0,-1,0,0,-1,0,1 } },
	{ { 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 } },
	{ { 0,0,0,0,0,-1,1,0 },{ 0,0,0,0,-1,0,0,-1 },{ 0,0,0,0,0,1,-1,0 },{ 0,0,0,0,0,1,1,0 } },
}; //테트리스 블럭

void gotoxy(int x, int y); //gotoXY
void SetBoard();
void DrawNext();
void DrawBoard(); //보드그리기
void DrawBlock(BOOL Show); //블럭그리기
void DrawBlock1(BOOL Show);
BOOL ProcessKey(); //키보드 입력
void Set(); //블럭 랜덤 소환 값 및 위치 설정
int GetRound(int nx, int ny, int block, int rotation); //블럭 주변 검사
BOOL Down(); //블럭 내림
void Game(); //게임
void BlockFull(); //블럭이 다채워졌나
void GetLevel(); //게임 난이도
void DrawUI();
void DrawScore();
void preview();


int main()
{	
	Game();

	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void DrawScore()
{ 
	gotoxy(82, 17); printf("   SCORE : %d 점   ", Score);
	gotoxy(82, 18);	printf("   BLOCK : %d 개   ", BlockNum);
}

void GetLevel()
{
	gotoxy(75, 20);
	printf("1. Easy");
	gotoxy(75, 21);
	printf("2. Normal");
	gotoxy(75, 22);
	printf("3. Hard");
	gotoxy(75, 23);
	scanf("%d", &tot);
	level = tot - 1;
	system("cls");
}

void SetBoard()
{
	randomize();
	
	for (int i = 0; i < BOARD_W + 2; i++)
		for (int j = 0; j < BOARD_H + 2; j++)
			board[i][j] = (j == 0 || j == BOARD_H + 1 || i == 0 || i == BOARD_W + 1) ? 3 : 0;

	if(level == NORMAL)
		for(int i=1; i < BOARD_W +1; i++)
			for (int j = 20; j < BOARD_H + 1; j++)
			{
				int ta = random(3);
				if (ta == 1)
					board[i][j] = 1;
			}

	if(level == HARD)
		for (int i = 1; i < BOARD_W + 1; i++)
			for (int j = 15; j < BOARD_H + 1; j++)
			{
				int ta = random(3);
				if (ta == 1 || ta == 2)
					board[i][j] = 1;
			}
}

//보드 그리기
void DrawBoard()
{	
		for (int i = 0; i < BOARD_W + 2; i++)
		{
			for (int j = 0; j < BOARD_H + 2; j++)
			{
				gotoxy(W + i * 2, H + j);
				puts(Tile[board[i][j]]);
			}
		}
		
}

void DrawUI()
{
	gotoxy(82, 11); printf("  ---------Key--------  ");
	gotoxy(82, 12); printf("   이동 : LEFT, RIGHT   ");
	gotoxy(82, 13); printf("        회전 : UP       ");
	gotoxy(82, 14); printf("      내리기 : DOWN     ");
	gotoxy(82, 15); printf(" 한 번에 내리기 : SPACE ");

	if (level == NORMAL)
	{
		gotoxy(82, 20); printf("블럭이 내려가다 변함!");
		gotoxy(82, 21); printf("NORMAL 모드는 블럭 개수가");
		gotoxy(82, 22); printf("40개 이상일 시 종료됩니다.");
	}
	if (level == HARD)
	{
		gotoxy(82, 20); printf("블럭이 내려가다 변함!");
		gotoxy(82, 21); printf("HARD 모드는 블럭 개수가");
		gotoxy(82, 22); printf("25개 이상일 시 종료됩니다.");
	}
}

//블럭 그리기
void DrawBlock(BOOL Show)
{
	int a = random(230);

	for (int i = 0; i < 4; i++)
	{
		if (a == 1 && level > 0 && down == false)
		{
			randomBlock = random(sizeof(Block) / sizeof(Block[0]));
			DrawBoard();
		}
		gotoxy(W + (Block[randomBlock][rotation][i].x + x) * 2, H + Block[randomBlock][rotation][i].y + y);
		puts(Tile[Show ? 1 : 0]);
	}
}

void DrawBlock1(BOOL Show)
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(W + (Block[randomBlock][rotation][i].x + px) * 2, H + Block[randomBlock][rotation][i].y + py);
		puts(Tile[Show ? 2 : 0]);
	}
	tmp++;
}

BOOL ProcessKey()
{
	int ch, mRotation;

	if (_kbhit()) {
		ch = _getch();
		if (ch == 0xE0 || ch == 0)
		{
			ch = _getch();
			switch (ch)
			{
			case LEFT:
				if (GetRound(x - 1, y, randomBlock, rotation) == 0) {
					DrawBlock(false);
					DrawBlock1(false);
					x--;
					preview();
					DrawBlock(true);
				}
				break;
			case RIGHT:
				if (GetRound(x + 1, y, randomBlock, rotation) == 0) {
					DrawBlock(false);
					DrawBlock1(false);
					x++;
					preview();
					DrawBlock(true);
				}
				break;
			case UP:
				mRotation = (rotation == 3 ? 0 : rotation + 1);
				if (GetRound(x, y, randomBlock, mRotation) == 0) {
					DrawBlock(false);
					DrawBlock1(false);
					rotation = mRotation;
					preview();
					DrawBlock(true);
				}
				break;
			case DOWN:
				if (Down()) {
					return true;
				}
				break;
			}
		}
		else
		{
			switch (ch)
			{
			case ' ':
				while (Down() == false) { down = true; }
				down = false;
				return true;
			}
		}
	}
	return false;
}

void Set()
{
	randomize();
	randomBlock = random(sizeof(Block) / sizeof(Block[0]));
	randomBlock = randomBlock1;
	randomBlock1 = random(sizeof(Block) / sizeof(Block[0]));
	x = BOARD_W / 2, y = 3, rotation = 0;
}

int GetRound(int nx, int ny, int block, int rotation)
{
	int tmp = 0;

	for (int i = 0; i < 4; i++)
		tmp = max(tmp, board[nx + Block[block][rotation][i].x][ny + Block[block][rotation][i].y]);

	return tmp;
}

BOOL Down()
{
	if (GetRound(x, y + 1, randomBlock, rotation) != 0) {
		BlockFull();
		return true;
	}

	DrawBlock(false);
	y++;
	DrawBlock(true);

	return false;
}

void preview()
{
	px = x, py = y;
	while (1)
	{
		if (GetRound(px, py, randomBlock, rotation) == 0)
		{
			py++;
		}
		else
			break;
	}
	py--;
	DrawBlock1(true);
}

void Game()
{
	system("mode con:cols=170 lines=50");
	GetLevel();
	SetBoard();
	DrawBoard();
	DrawUI();
	
	int nFrame, nStay;
	if (tot == EASY)
		nFrame = 20;
	else if (tot == NORMAL)
		nFrame = 13;
	else
		nFrame = 8;
	
	Score = 0; BlockNum = 0;

	for(;;)
	{
		BlockNum++;
		Set();
		DrawNext();
		DrawBlock(true);
		preview();

		if (level == NORMAL && BlockNum > 40) break;
		if (level == HARD && BlockNum > 25) break;
		if (GetRound(x, y, randomBlock, rotation) != 0) break;
		if (check == 4) break;
		nStay = nFrame;

		for(;;)
		{
			if (--nStay == 0) {
				nStay = nFrame;
				if (Down()) break;
			}
			if (ProcessKey()) break;
			Sleep(50);
		}
	}
	system("cls");
	gotoxy(70, 20); printf("Game Over\n");
}
void BlockFull()
{
	int i, mx, my, ty;
	int count = 0;

	for (i = 0;i < 4; i++) {
		board[x + Block[randomBlock][rotation][i].x][y + Block[randomBlock][rotation][i].y] = 1;
	}

	for (my = 1; my < BOARD_H + 1; my++)
	{
		for (mx = 1; mx < BOARD_W + 1; mx++) 
		{
			if (board[mx][my] != 1) 
				break;
		}
		if (mx == BOARD_W + 1) {
			if (BlockNum >= 3)
				BlockNum -= 3;
			else
				BlockNum = 0;
			count++;
			for (ty = my; ty > 1; ty--) {
				for (mx = 1; mx < BOARD_W + 1; mx++) {
					board[mx][ty] = board[mx][ty - 1];
				}
			}
			DrawBoard();
			Sleep(400);
		}
	}
	Score += ScoreBoard[count];
	DrawScore();
		if (Score > maxScore)
		{

			int tot = 0;
			maxScore += 40;
			for (my = 1; my < BOARD_H + 1; my++)
			{
				for (mx = 1; mx < BOARD_W + 1; mx++)
				{
					if (board[mx][my] == 1)
					{
						for (ty = my - 1; ty <= BOARD_H; ty++) {
							for (mx = 1; mx < BOARD_W; mx++) {
								if (ty == BOARD_H)
									board[mx][ty] = board[mx][ty];
								else
									board[mx][ty] = board[mx][ty + 1];
							}
						}
						tot++;
					}
					if (tot == 1)
						break;
				}
				if (tot == 1)
					break;
			}
		
			DrawBoard();
			Sleep(400);
		}
}
void DrawNext()
{
	int nx, ny, i;
	for (nx = 82; nx <= 94; nx += 2)
	{
		for (ny = 4; ny <= 8; ny++)
		{
			gotoxy(nx, ny);
			puts(Tile[(nx == 82 || nx == 94 || ny == 4 || ny == 8) ? 2 : 0]);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		gotoxy(88 + (Block[randomBlock1][0][i].x) * 2, 6 + Block[randomBlock1][0][i].y);
		puts(Tile[1]);
	}
}


