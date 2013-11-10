
#include "process.h"
#include "sudokuGameLogic.h"

int pad[9][9];
int padConstFlag[9][9];
int padAnswer[9][9];
int cursorX = 0;
int cursorY = 0;
GameState gameState;
int runningTime = 0;
int timeAgo, timeNow;//������¼��һ�ε�ʱ�䣬�͵�ǰ��ʱ��




int main()
{
	system("color F0");//���ÿ���̨���ڵı�����ɫΪF����ɫ����������ɫΪ0����ɫ��
	int i,j;
	char keyType;//������Ű���ֵ
	DrawPad();//sudokuDraw.h�еĺ���������������������
	DrawTime(gameState,0);//sudokuDraw.h�еĺ���������ʱ�䣬���ݲ���״̬gameState,��ʱ��0
	InitialAndDrawGame(pad,padAnswer,padConstFlag);//sudokuDraw.h�еĺ�������ʼ����Ϸ�����ҽ���ʼ�����������Ϸ���ȥ
	gameState = Running;//����Ϸ״̬��ΪRunning
	timeAgo = GetTime();//��¼ʱ��
	_beginthread(KeyCheckThread,0,NULL);//����һ���̣߳�ר��������ȡ���̶�����KeyCheckThread����sudokuGameLogic.h�еĺ����������������Ǹ�ʽҪ�󣬿��Բ���
	while(1)
	{
		GameRun();//��Ϸ���ܣ���������sudokuGameLogic.h�еĺ������ô���ͳ��ȫ�ִ�������
	}
	return 0;

}