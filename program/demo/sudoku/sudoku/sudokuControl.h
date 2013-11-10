#include <stdio.h>
#include "windows.h"
#include <math.h>
#include "conio.h"
#include "time.h"

extern int cursorX;
extern int cursorY;

//�����������̶��ı�����������������ƽ�Ƶ���
int const offsetX = 5, offsetY = 2;

//������һ����ɫ����
enum Color {red,green,blue,cryn,magenta,yellow,white,black,darkCryn,darkGreen,gray};


//�趨�����������ϵ�µ�����
void CursorGotoXY(int x, int y)
{
	//Initialize the coordinates
	COORD coord = {x*4+offsetX+2, y*2+offsetY+1};//����һ�����꣬ƽ��ԭ��󣬽���x,y��ͨ��x*4+offsetX+2��y*2+offsetY+1�任Ϊ������ϵ�µ�����
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//һ���趨����λ�õĺ���

	cursorX = x;//������λ�ñ�������
	cursorY = y;
	
}

//�趨�����ƽ�ƺ��ԭʼ����ϵ�µ�����
void CursorGotoXYReal(int x, int y)
{
	//Initialize the coordinates
	COORD coord = {x+offsetX, y+offsetY};//û�б任���ֻ꣬�ǽ�����ԭ��ƽ��
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//�趨�����δƽ��ԭʼ����ϵ�µ�����
void CursorGotoXYRealWithoutOffest(int x, int y)
{
	//Initialize the coordinates
	COORD coord = {x, y};//û�б任���ֻ꣬�ǽ�����ԭ��ƽ��
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//�趨������ɫ
//����color����Color�е�һ��
void SetColor(Color color)
{
	WORD colorA;//����һ��WORD���͵ı���������ɫ�Ĵ��룬���ǹ涨�ĸ�ʽ
	//colorA��ֵ���������漸��ֵ��һ�ֻ��߼��֣�ǰ��ɫ�������ֵ���ɫ
	//FOREGROUND_RED��ǰ��ɫ_��ɫ
	//FOREGROUND_BLUE��ǰ��ɫ_��ɫ
	//FOREGROUND_GREEN��ǰ��ɫ_��ɫ
	//FOREGROUND_INTENSITY:����ʹ��ʱ��ɫ������ɫһͬʹ���Ǽ�����ɫ
	//��ɫ�� 0 
	//�⼸�ֲ��������� | ������ʹ�ò�����ͬ��ɫ��������Ϲ����Բ����������n����ɫ�������ѧûѧ�á�����������������ж����˼�����ɫ
	switch (color)
	{
	case black:{colorA = 0;}break;//��ɫ
	case red:{colorA = FOREGROUND_INTENSITY | FOREGROUND_RED;}break;//����ɫ
	case blue:{colorA = FOREGROUND_INTENSITY |FOREGROUND_BLUE;}break;//����ɫ
	case green:{colorA = FOREGROUND_INTENSITY |FOREGROUND_GREEN;}break;//����ɫ
	case darkGreen:{colorA = FOREGROUND_GREEN;}break;//��ɫ
	case cryn:{colorA = FOREGROUND_INTENSITY |FOREGROUND_BLUE | FOREGROUND_GREEN;}break;//��ɫ
	case darkCryn:{colorA = FOREGROUND_BLUE | FOREGROUND_GREEN;}break;
	case magenta:{colorA = FOREGROUND_INTENSITY |FOREGROUND_BLUE| FOREGROUND_RED;}break;//Ʒ��
	case yellow:{colorA = FOREGROUND_INTENSITY | FOREGROUND_RED| FOREGROUND_GREEN;}break;//����ɫ
	case white:{colorA = FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY;}break;//�������ټ�ǿΪ��ɫ
	case gray:{colorA = FOREGROUND_INTENSITY;}break;
	default:colorA = FOREGROUND_INTENSITY;
			break;
	}
	//ǰ���BACKGROUND_XXX�Ǳ���ɫ�������ֵĵ�ɫ�����ｫ����ɫ��Ϊ��ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY|BACKGROUND_BLUE| BACKGROUND_GREEN|BACKGROUND_RED | colorA);
}

//write the (int)number at position(x,y).x+ to right, y+ to down��������ϵ�У�
void WriteNumberAt( int x, int y,int number)
{
	CursorGotoXY(x,y);
	printf("%d",number);
}

//��������ϵ�е�(x,y)������д�ַ�c
void WriteCharAt( int x, int y,char c)
{
	CursorGotoXY(x,y);
	printf("%c",c);
}

//���ַ�c����ֱ�ߣ�ֱ�ߴ�ƽ�ƺ�����ϵ��(x1,y1)��(x2,y2)��DDA�㷨�����ο��������ͼ��ѧ������
void Line(int x1, int y1, int x2, int y2, char c)
{
	double dx,dy,x,y,length;
	int i;
	if (abs(x2-x1) > abs(y2-y1))
		length = abs(x2-x1);
	else
		length = abs(y2-y1);
	dx = (x2-x1) / length;
	dy = (y2-y1) / length;
	x =x1;y = y1;
	for (i = 0; i <= length; i++)
	{
		CursorGotoXYReal(x,y);
		printf("%c",c);
		x += dx;
		y += dy;
	}

}

//���ַ�c����ֱ�ߣ�ֱ�ߴ�δƽ������ϵ��(x1,y1)��(x2,y2)��DDA�㷨�����ο��������ͼ��ѧ������
void LineWithoutOffset(int x1, int y1, int x2, int y2, char c)
{
	double dx,dy,x,y,length;
	int i;
	if (abs(x2-x1) > abs(y2-y1))
		length = abs(x2-x1);
	else
		length = abs(y2-y1);
	dx = (x2-x1) / length;
	dy = (y2-y1) / length;
	x =x1;y = y1;
	for (i = 0; i <= length; i++)
	{
		CursorGotoXYRealWithoutOffest(x,y);
		printf("%c",c);
		x += dx;
		y += dy;
	}

}

//��ȡϵͳ��ǰʱ�䣬���ص�����1970��1��1������������������������.1970����ϵͳ�涨��
int GetTime()
{
	time_t t;//����ʱ���ʽ�ı���t����ʵ���Ǹ�����
	time(&t);//��ȡ��ǰʱ�䣬����t
	return t;//��ʽת��Ϊint�ͷ���
}

//�ڹ̶�λ����ʾһ�����е�ѯ����䡣s1Ϊ��һ��Ҫ��ʾ���ַ�����s2Ϊ�ڶ���Ҫ��ʾ���ַ�����colorΪҪ��ʾ����ɫ
int QuestionMessageShowFixPosition(char s1[],char s2[], Color color)
{
	int state;//�����洢״̬
	SetColor(color);
	CursorGotoXYReal(50,1);
	printf(s1);
	CursorGotoXYReal(45,2);
	printf(s2);
	char yesno = getch();//��ȡһ���ַ�
	if (yesno != 'y' && yesno != 'Y')//�������Ĳ���y����ʾ��
	{
		state = 0;
	}
	else
		state = 1;
	CursorGotoXYReal(50,1);//�⼸�仰�������ղ���ʾ�Ļ�������
	printf("                       ");
	CursorGotoXYReal(45,2);
	printf("                            ");
	return state;
}

