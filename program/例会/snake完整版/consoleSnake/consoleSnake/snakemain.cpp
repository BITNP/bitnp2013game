#include "conio.h"
#include "stdio.h"
#include "windows.h"
#include "vector"
#include "time.h"
using namespace std;

//����һ��struct����������Ϣ
typedef struct iPoint
{
	int x;
	int y;
} Point;

//�궨�����������ĸ������ļ�ֵ
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define WIDTH 40
#define HEIGHT 25

void CheckKeyPress(char key);
void SetCursorTo(int x, int y);
void DrawSnake();
void DrawEraser();
void DrawStar(int x, int y);
void MoveSnake();
void Init();
void Update();
void Draw();
void GenerateFood();
void DrawFood();
void DrawBorder();

bool			isRun = true;
char			keyPress;
int				cursorX = 0, cursorY = 0;
vector<Point>	snake;
vector<Point>	eraser;
int				dx, dy;
Point			food;

int main()
{
	Init();	//�Զ���ĳ�ʼ������

	while (1)
	{
		if (!isRun)
			break;
		Update();		//ˢ��
		Draw();			//��Ⱦ
		Sleep(100);		//˯���룬��ֹ�������й��졣Ҳ������������Ϸ�ٶ�
	}
	return 0;
}

//��ʼ������
void Init()
{
	DrawBorder();
	//��ʼ��̰����
	Point tempPoint;
	tempPoint.x = 10;
	tempPoint.y = 10;
	snake.push_back(tempPoint);

	tempPoint.x = 11;
	tempPoint.y = 10;
	snake.push_back(tempPoint);

	tempPoint.x = 12;
	tempPoint.y = 10;
	snake.push_back(tempPoint);

	//��ʼ��������Ϣ
	dx = 1;
	dy = 0;
	GenerateFood();
	//��ʼ�������������
	srand(time(0));
}

void Update()
{
	if (kbhit())
	{	
		keyPress = getch();
		CheckKeyPress(keyPress);
	}
	eraser.clear();	//���eraser��
	MoveSnake();	//�ƶ���
}

void Draw()
{
	DrawEraser();	//�����Ӧ��ʾ��ͼ��
	DrawFood();		//��ʳ��
	DrawSnake();	//����
}

//��ⰴ��
void CheckKeyPress(char key)
{
	switch (key)
	{
	case 'q':
		{
			isRun = false;
		}break;
	case ' ':
		{
			DrawStar(cursorX,cursorY);
		}break;
	case UP:
		{
			dx = 0;
			dy = -1;
		}break;
	case DOWN:
		{
			dx = 0;
			dy = 1;
		}break;
	case LEFT:
		{
			dx = -1;
			dy = 0;
		}break;
	case RIGHT:
		{
			dx = 1;
			dy = 0;
		}break;
	}
}

//���ù���λ��
void SetCursorTo(int x, int y)
{
	COORD coord = {x*2,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	//������λ�ñ�����ȫ�ֱ�����
	cursorX = x;
	cursorY = y;
}

//��һ������
void DrawStar(int x, int y)
{
	SetCursorTo(x,y);	//�����������Ҫ����λ��
	printf("*");		//��ӡ��һ��*
}

//��һ��@
void DrawAt(int x, int y)
{
	SetCursorTo(x,y);	//�����������Ҫ����λ��
	printf("@");		//��ӡ��һ��*
}

//��һ��char
void DrawChar(int x, int y, char c)
{
	SetCursorTo(x,y);	//�����������Ҫ����λ��
	printf("%c",c);		//��ӡ��һ��*
}

//��һ���ո�� �� ��Ϊ���(x,y)����ͼ��
void DrawBlank(int x, int y)
{
	SetCursorTo(x,y);
	printf(" ");
}

//����
void DrawSnake()
{
	int length = snake.size();		//��ȡ�ߵĳ���
	int i;
	for (i = 0; i < length; i++)	//�����ߵ�ÿһ�ڵ㲢��ӡһ���Ǻ�
	{
		DrawStar(snake[i].x, snake[i].y);
	}
}

//��Ҫ����Ĳ���
//ÿ�θ��������Ҫɾ����ͼ�ξͱ�����Eraser������ɾ��
void DrawEraser()
{
	int length = eraser.size();
	int i;
	for (i = 0; i < length; i++)
	{
		DrawBlank(eraser[i].x, eraser[i].y);
	}
};

bool CheckEat()
{
	if (snake.back().x == food.x && snake.back().y == food.y)
		return true;
	else
		return false;
}

bool HitBorder()
{
	if (snake.back().x == 0 || snake.back().x == WIDTH-1 ||
		snake.back().y == 0 || snake.back().y == HEIGHT-1)
		return true;
	else
		return false;
}

//�ƶ���
void MoveSnake()
{
	Point tempPoint;	//����һ����ʱPoint
	tempPoint.x = snake.back().x + dx;	//�������xΪ��ͷ������һ��λ�õ�x
	tempPoint.y = snake.back().y + dy;	//ͬ������y
	snake.push_back(tempPoint);			//������ڵ�ŵ���vector������棬��Ϊͷ��
	if (HitBorder())
	{
		isRun = false;
	}
	if (CheckEat())
	{
		GenerateFood();
	}
	else
	{
		vector<Point>::iterator first = snake.begin();	//����һ������������ȡvector�ĵ�һ��Ԫ�أ�Ҳ���ߵ�β��
		tempPoint.x = first->x;
		tempPoint.y = first->y;
		eraser.push_back(tempPoint);	//��β���ڵ㱣����Ҫ����λ�õ�vector��
		snake.erase(first);				//���ߵ�β���ڵ�ɾ��
	}
}

void GenerateFood()
{
	food.x = 1 + rand() % (WIDTH-2) ;
	food.y = 1 + rand() % (HEIGHT-2);
}

void DrawFood()
{
	DrawAt(food.x, food.y);
}

void DrawBorder()
{
	for (int i = 0; i < WIDTH; i++)
	{
		DrawChar(i, 0, '-');
		DrawChar(i, HEIGHT-1, '-');
	}
	for (int i = 0; i < HEIGHT-1; i++)
	{
		DrawChar(0, i, '|');
		DrawChar(WIDTH-1, i, '|');
	}
}

