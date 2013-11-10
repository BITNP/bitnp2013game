
#include "sudokuDraw.h"

extern int cursorX;
extern int cursorY;
extern int pad[9][9];
extern int padConstFlag[9][9];
extern int padAnswer[9][9];
extern GameState gameState; 
extern int runningTime;
extern int timeAgo;
extern int timeNow;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


//�������ּ�ʱ����
void NumberKeyPress(int ascii_code)
{
	int i = cursorY;
	int j = cursorX;
	int numTap = ascii_code - '0';
	if (padConstFlag[i][j] == 0 && gameState == Running)
	{
		int BlockCode = (i/3)*3+(j/3);//���������������(iPad, jPad)�任��С����ı��BlockCode.
		if (!CheckNumberExistInBlock(pad,BlockCode, numTap) &&
			!CheckNumberExistInColum(pad,j,numTap) &&
			!CheckNumberExistInRow(pad,i,numTap))
		{
			pad[i][j] = numTap;
			SetColor(blue);
			WriteNumberAt(cursorX,cursorY,numTap);
			if (CheckFinished(pad))
			{
				gameState = Win;
				CursorGotoXYReal(50,1);
				printf("�����ˣ�              ");
				/*if (highScores[level] > runningTime)
				{
					WriteHighScore(level,runningTime);
					sprintf(buffer,"�¼�¼��");
					SetTextColor(hdc,RGB(0,0,255));
					TextOut(hdc,560,310,buffer,strlen(buffer));
				}*/
							
			}
		}
	}
	else if (gameState == ComputerPlay)//��������ڵ��Խ���
	{
		SetColor(magenta);//��ΪƷ��ɫ
		int BlockCode = (i/3)*3+(j/3);//���������������(iPad, jPad)�任��С����ı��BlockCode.
		if (!CheckNumberExistInBlock(pad,BlockCode, numTap) &&
			!CheckNumberExistInColum(pad,j,numTap) &&
			!CheckNumberExistInRow(pad,i,numTap))//�ж������Ƿ��������ȥ
		{
			pad[i][j] = numTap;//����ȥ
			padConstFlag[i][j] = 1;//�����λ����Ϊ�̶�
			WriteNumberAt(cursorX,cursorY,numTap);
		}
	}
	else if (gameState == ComputerPlayEnd )
		return;
}

//������ʾ�𰸼�ʱ����
void AnswerKeyPress()
{
	if (gameState == Running)
	{
		gameState = AnswerShow;
		ShowAnswer(pad,padConstFlag,padAnswer);
		CursorGotoXY(cursorX,cursorY);
	}
}

//�������¿�ʼ��ʱ����
void RestartKeyPress()
{
	if (gameState == Running)
	{
		gameState = Pause;
		if (QuestionMessageShowFixPosition("�������¿�ʼ��    ","����y��ʾ�ǣ��������ʾ��",red) == 0)
		{
			gameState = Running;
			return;
		}

	}
	CursorGotoXYReal(45,1);
	printf("                           ");
	runningTime = 0;
	DrawTime(Running,0);//sudokuDraw.h�еĺ���������ʱ�䣬���ݲ���״̬gameState,��ʱ��0
	InitialAndDrawGame(pad,padAnswer,padConstFlag);
	gameState = Running;
	timeAgo = GetTime();//��¼ʱ��
}

//���µ��Խ��⣨c���Ĵ�������ʾ������Խ���
void ComputerPlayKeyPress()
{
	if (gameState == Running)//����������˹����⣬ѯ���Ƿ�Ҫ������Ϸ
	{
		gameState = Pause;
		if (QuestionMessageShowFixPosition("������ǰ�֣�    ","����y��ʾ�ǣ��������ʾ��",red) == 0)
		{
			gameState = Running;
			return;
		}
	}
	gameState = ComputerPlay;
	runningTime = 0;
	ComputerPlayInitialize(pad,padConstFlag);//���Խ����ʼ��
	DrawNumbers(pad,padAnswer,padConstFlag);//�����֣���ΪȫΪ0������ʵ����������������ϵ����֣�
	DrawTime(gameState,0);//��ʾ��ʼʱ��
	CursorGotoXYReal(45,1);
	SetColor(blue);
	printf("���س�����ʼ�������");
	CursorGotoXY(cursorX,cursorY);//������λ
}

//�����ڵ��Խ���״̬�����»س���������ʾ��ʼ����
//���Կ�ʼ���⣬������ʾ����
void ComputerPlayEnterPress()
{
	gameState = ComputerPlayEnd;
	runningTime = ComputerPlaySodoku(pad,padConstFlag,padAnswer);
	ShowComputerPlayAnswer(padConstFlag,padAnswer,gameState,runningTime);
}

//�����ݶ���p������
void PauseKeyPress()
{
	if (gameState == Running)
	{
		gameState = Pause;
		CursorGotoXYReal(54,1);
		SetColor(blue);
		printf("��ͣ");
	}
	else if (gameState == Pause)
	{
		gameState = Running;
		CursorGotoXYReal(54,1);
		printf("    ");
	}
	CursorGotoXY(cursorX,cursorY);
}

//����ɾ����ʱ��ɾ������Լ�д������
void DeletePress()
{
	if (padConstFlag[cursorY][cursorX] == 0 && gameState == Running)
	{
		pad[cursorY][cursorX] = 0;
		WriteCharAt(cursorX,cursorY,' ');
	}
	else if (gameState == ComputerPlay)
	{
		pad[cursorY][cursorX] = 0;
		padConstFlag[cursorY][cursorX] = 0;
		WriteCharAt(cursorX,cursorY,' ');
	}
	else if (gameState == ComputerPlayEnd )
		return;
}

//�����ʱ��;�ʱ����ȣ���û�г���1���ӡ��еĻ���ʱ+1�벢��ʾ
void TimeCheck()
{
	if (gameState == Running)
	{
		timeNow = GetTime();//��¼��ʱ��
		if (timeNow - timeAgo >= 1)
		{
			timeAgo = timeNow;
			runningTime++;
			DrawTime(gameState,runningTime);
		}
	}
	else if (gameState == Pause)
	{
		timeNow = GetTime();
		timeAgo = timeNow;
	}
}

//�����������ĸ����
void KeyCheck(char key)
{
	switch (key)
	{
	//case 'P':{PauseKeyPress();}break;
	case 'p'://pause
		{
			PauseKeyPress();
		}break;
	//case 'A':{}
	case 'a'://answer
		{
			AnswerKeyPress();
		}break;
	//case 'R':{}
	case 'r'://restart
		{
			RestartKeyPress();
		}break;
	//case 'C':{}
	case 'c'://computerPlay
		{
			ComputerPlayKeyPress();
		}break;
	default:
		{
			if (key >= '1' && key <= '9')
				NumberKeyPress(key);
		}break;
	}
	
}

//��ⷽ�����������Ӧ
void DirectionKeyCheck(char key)
{
	switch (key)
	{
	case UP://���Ϸ����
		{
			if (cursorY-1 >= 0)//���û�������߲���Խ��Ļ��㽫��������ƶ�һ��
				CursorGotoXY(cursorX,cursorY-1);
		}break;
	case DOWN:
		{
			if (cursorY+1 < 9)
				CursorGotoXY(cursorX,cursorY+1);
		}break;
	case LEFT:
		{
			if (cursorX-1 >= 0)
				CursorGotoXY(cursorX-1,cursorY);
		}break;
	case RIGHT:
		{
			if (cursorX+1 < 9)
				CursorGotoXY(cursorX+1,cursorY);
		}break;
	case VK_ESCAPE://�˳����������ϵ�Esc
		{
			exit(0);
		}break;
	case VK_RETURN://�س���������ȷ����ʼ���Խ���
		{
			if (gameState == ComputerPlay)//������ڴ��ڵ��Խ׽��⣬��ô��ʼ
			{
				gameState = ComputerPlayEnd;
				ComputerPlayEnterPress();//������
			}
		}break;
	case VK_BACK://ɾ����
		{
			DeletePress();
		}break;
	}
	
}

//���ڼ����̵��̴߳�����������dummy����ʱ����д��Ҳ��֪��ʲô��˼��
void KeyCheckThread(void *dummy)
{
	char keyType;
	while(1)
	{
		keyType = getch();//��ȡ����
		DirectionKeyCheck(keyType);//sudokuGameLogic.h�еĺ������ж��Ƿ��Ƿ��򰴼�
		KeyCheck(keyType);//sudokuGameLogic.h�еĺ������ж��Ƿ������ּ�������ĸ��
		keyType = getch();//�ٻ��һ�Ρ���Ϊ�������Ҫ��ȡ���Ρ���Ϊ�˲�Ӱ�����ּ�����ĸ�������������������жϺ���������һ��
		KeyCheck(keyType);
		DirectionKeyCheck(keyType);
	}
}

//��Ϸѭ����ʼ������
void GameRun()
{
	Sleep(10);//������ͣ10ms����Ҫ�Ƿ�ֹ�������й���
	TimeCheck();//sudokuGameLogic.h�еĺ����������ʱ��;�ʱ����ȣ���û�г���1���ӡ��еĻ���ʱ+1�벢��ʾ
}