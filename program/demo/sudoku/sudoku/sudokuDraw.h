#include "sudokuControl.h"
#include "sudokuLogic.h"

enum GameState {Running, AnswerShow,Win, ComputerPlay, ComputerPlayEnd,Pause};

//��pad[][]�е������������
void DrawNumbers(int pad[][9],int padAnswer[][9],int padConstFlag[][9])
{
	int i,j;
	SetColor(gray);//���û�ɫ
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (padConstFlag[i][j] != 0)//������ֵ�ǲ����޸ĵ�
			{
				WriteNumberAt(j,i,pad[i][j]);
			}
			else
			{
				WriteCharAt(j,i,' ');//��д���ո�
			}

		}
	}
	CursorGotoXY(0,0);//�ָ����굽(0,0)
}

//��ʼ����Ϸ������д����
void InitialAndDrawGame(int pad[][9],int padAnswer[][9],int padConstFlag[][9])
{
	int i,j;
	SetColor(gray);
	GameInitialize(pad,padAnswer,padConstFlag);
	DrawNumbers(pad,padAnswer,padConstFlag);
}

//����Ϸ���棬�������ӣ���򣬰������˵�������
void DrawPad()
{
	int i,j;
	SetColor(black);
	LineWithoutOffset(0,0,0,23,'#');
	LineWithoutOffset(78,0,78,23,'#');
	LineWithoutOffset(0,0,78,0,'#');
	LineWithoutOffset(0,23,78,23,'#');


	SetColor(darkCryn);//��Ϊ��ɫ
	for (i = 0; i < 9; i++)//����ϸ��
	{
		Line(4*i,0,4*i,18,'|');
	}
	for (i = 0; i < 9; i++)//����ϸ��
	{
		Line(0,2*i,36,2*i,'-');	
	}

	SetColor(black);//��Ϊ��ɫ
	Line(0,0,36,0,'*');//������Ĵ���
	Line(0,6,36,6,'*');
	Line(0,6*2,36,6*2,'*');
	Line(0,6*3,36,6*3,'*');

	Line(0,0,0,18,'*');//������Ĵ���
	Line(12,0,12,18,'*');
	Line(12*2,0,12*2,18,'*');
	Line(12*3,0,12*3,18,'*');
	
	//����
	SetColor(blue);
	CursorGotoXYRealWithoutOffest(31,0);
	printf("��    SUDOKU    ��");
	SetColor(red);
	CursorGotoXYRealWithoutOffest(66,0);
	printf("[Esc]:�˳�");

	//�����Ͳ˵�
	SetColor(gray);
	CursorGotoXYReal(45,10);
	printf("����������   �ƶ����");
	CursorGotoXYReal(45,12);
	printf("���ּ� :     ��д����");
	CursorGotoXYReal(45,14);
	printf("Backspace :  ɾ������");
	SetColor(darkGreen);
	CursorGotoXYReal(45,16);
	printf("[P] :        ��ͣ��Ϸ");
	CursorGotoXYReal(45,17);
	printf("[A] :        ��ʾ��");
	CursorGotoXYReal(45,18);
	printf("[R] :        �¿�����");
	CursorGotoXYReal(45,19);
	printf("[C] :        ���Խ��");
}

//��ʱ��
void DrawTime(GameState gameState, int runningTime)
{
	SetColor(black);//����Ϊ��ɫ
	CursorGotoXYReal(48,4);
	if (gameState == Running)//������˹�������,����ʾʱ����Ľ���ʱ��
	{
		printf("��ʱ��%dʱ%d��%d��    ",runningTime/3600,runningTime/60%60,runningTime%60);
	}
	else if (gameState == ComputerPlay || gameState == ComputerPlayEnd)//����ǻ�����������ʾ����Ļ�����ʱ
	{
		printf("��ʱ��%.3lf����     ",(double)runningTime/1000);
	}
	CursorGotoXY(cursorX,cursorY);
}

//��ʾ��
void ShowAnswer(int pad[][9],int padConstFlag[][9],int padAnswer[][9])
{
	SetColor(red);//��Ϊ��ɫ
	CursorGotoXYReal(50,1);
	printf("   ������      ");//д������
	int i,j;
	for (i = 0; i < 9; i++)//����Щû���������������ʾ����
	{
		for (j = 0; j < 9; j++)
		{
			if (padConstFlag[i][j] == 0)
			{
				if (pad[i][j] == 0)
				{
					WriteNumberAt(j,i,padAnswer[i][j]);
				}
			}
		}
	}
}

//��ʾ���Խ���Ľ��
void ShowComputerPlayAnswer(int padConstFlag[][9], int padAnswer[][9],GameState gameState,int  runningTime)
{
	int i,j;
	SetColor(blue);//����ɫ��д
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (padConstFlag[i][j] == 0)
			{
				WriteNumberAt(j,i,padAnswer[i][j]);
			}
		}
	}
	DrawTime(gameState,runningTime);//���Ұ���ʱ������
}

