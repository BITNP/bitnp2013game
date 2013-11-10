#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//���number�ڵ�ǰ����û���ظ���
int CheckNumberExistInColum(int pad[][9], int colum, int number)
{
	int iRow,i;
	for (iRow = 0; iRow < 9; iRow++)
	{
		if (number == pad[iRow][colum])
		{
			return 1;
		}
	}
	return 0;
}

//���number�ڵ�ǰ����û���ظ���
int CheckNumberExistInRow(int pad[][9],int row, int number)
{
	int iColum,i;
	for (iColum = 0; iColum < 9; iColum++)
	{
		if (number == pad[row][iColum])
		{
			return 1;
		}
	}
	return 0;
}

//���number�ڵ�ǰ������û���ظ���
//С����ı��BlockCode
//�������ң������������α��Ϊ0,1,2,3,4,5,6,7,8
int CheckNumberExistInBlock(int pad[][9],int BlockCode,int number)
{
	int i,j;
	int iBlock = BlockCode / 3,
		jBlock = BlockCode % 3;
	for (i = iBlock * 3; i < iBlock * 3 + 3; i++)
	{
		for (j = jBlock * 3; j < jBlock * 3 + 3; j++)
		{
			if (number == pad[i][j])
			{
				return 1;
			}
		}
	}
	return 0;
}

//�ݹ���⣬������ŵ�pad[][]��
int TryAndPut(int pad[][9],int i, int j)
{
	int numberTry;
	for (numberTry = 1; numberTry <= 9; numberTry++)
	{
		if (i > 8 || j > 8)
		{
			return 1;
		}
		int BlockCode = (i/3)*3+(j/3);//���������������(iPad, jPad)�任��С����ı��BlockCode.
		if (!CheckNumberExistInBlock(pad,BlockCode, numberTry) &&
			!CheckNumberExistInColum(pad,j,numberTry) &&
			!CheckNumberExistInRow(pad,i,numberTry) )
		{
			pad[i][j] = numberTry;
			if (j < 8)
			{
				if (TryAndPut(pad,i,j+1))
				{
					return 1;
				}
			}
			else
			{
				if (i < 8)
				{
					if (TryAndPut(pad,i+1,0))
					{
						return 1;
					}
				}
				else
					return 1;
			}
			pad[i][j] = 0;
		}
	}
	return 0;
}

//��pad[][]���Ź���
void CreateSodukuPad(int pad[][9])
{
	srand(time(0));
	int temp[100];
	int nineNumberCreater[100], i,j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			pad[i][j] = 0;
		}
	}
	for (i = 0; i < 9; i++)
	{
		nineNumberCreater[i] = i+1;
	}
	//��nineNumberCreater������1~9���ֵ�˳�����
	for (i = 0; i < 9; i++)
	{
		int randPos = rand() % 9;
		int tempSwap = nineNumberCreater[i];
		nineNumberCreater[i] = nineNumberCreater[randPos];
		nineNumberCreater[randPos] = tempSwap;
	}

	//������˳����������һ����
	for (i = 0; i < 9; i++)
	{
		pad[0][i] = nineNumberCreater[i];
	}
	TryAndPut(pad,1,0);//�ݹ齫padʣ�µ�2��9������
}

//��pad[][]��blankSize���ա���δ�ڵĿյ�λ����padConstFlag��¼���������ҽ��ڿ�֮ǰ��������padAnswer���������Ա���ʾ��֮��
void SetSodokuPuzzle(int pad[][9],int padAnswer[][9],int padConstFlag[][9],int BlankSize)
{
	int i,j,k;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
		{
			padConstFlag[i][j] = 1;
			padAnswer[i][j] = pad[i][j];
		}
	i = rand() % 9;
	j = rand() % 9;
	for (k = 0; k < BlankSize; k++)
	{
		while (pad[i][j] == 0)
		{
			i = rand() % 9;
			j = rand() % 9;
		}
		pad[i][j] = 0;
		padConstFlag[i][j] = 0;
	}
}


//��ʼ����Ϸ������pad[][��ʼ����Ȼ���ڿ�����
void GameInitialize(int pad[][9],int padAnswer[][9],int padConstFlag[][9])
{
	CreateSodukuPad(pad);
	int blankSize;
	/*switch (level)
	{
	case Crazy :{blankSize = 65;}break;
	case Difficult :{blankSize = 50;}break;
	case Normal :{blankSize = 35;}break;
	case Easy :{blankSize = 20;}break;
	case Relax :{blankSize = 10;}break;
	}*/
	blankSize = 30+ rand() % 3;
	SetSodokuPuzzle(pad,padAnswer,padConstFlag,30);
}

//����Ƿ��Ѱѿ����������������
int CheckFinished(int pad[][9])
{
	int i,j;
	for (i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if (pad[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

//����������õĵݹ�
int TryAndPutComputerPlay(int pad[][9],int blankPosi[],int blankPosj[],int blankCount,int k)
{
	int numberTry;
	for (numberTry = 1; numberTry <= 9; numberTry++)
	{
		if (k >= blankCount)
			return 1;
		int BlockCode = (blankPosi[k]/3)*3+(blankPosj[k]/3);//���������������(iPad, jPad)�任��С����ı��BlockCode.
		if (!CheckNumberExistInBlock(pad,BlockCode, numberTry) &&
			!CheckNumberExistInColum(pad,blankPosj[k],numberTry) &&
			!CheckNumberExistInRow(pad,blankPosi[k],numberTry) )
		{
			pad[blankPosi[k]][blankPosj[k]] = numberTry;
			if (TryAndPutComputerPlay(pad,blankPosi,blankPosj,blankCount,k+1))
			{
				return 1;
			}
			pad[blankPosi[k]][blankPosj[k]] = 0;
		}
	}
	return 0;
}

//��ʼ���������ʱ�õ���pad[][]��padConstFlag[][]������ʼ��Ϊ0
void ComputerPlayInitialize(int pad[][9], int padConstFlag[][9])
{
	int i,j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			pad[i][j] = 0;
			padConstFlag[i][j] = 0;
		}
	}
}

//���Լ���������ʼ���������ؼ����ʱ�䣬��λ��ms
int ComputerPlaySodoku(int pad[][9],int padConstFlag[][9], int padAnswer[][9])
{
	LARGE_INTEGER nFreq, t1,t2;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

	int i,j,blankCount = 0;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (pad[i][j] != 0)
			{
				padConstFlag[i][j] = 1;
			}
		}
	}

	//����ɨ�����������δ��д��������꣬��Ϊһ������blankPos[]
	int blankPosi[81],blankPosj[81];
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (pad[i][j] == 0)
			{
				blankPosi[blankCount] = i;
				blankPosj[blankCount] = j;
				blankCount++;
			}
		}
	}
	TryAndPutComputerPlay(pad,blankPosi,blankPosj,blankCount,0);
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			padAnswer[i][j] = pad[i][j];
		}
	}
	QueryPerformanceCounter(&t2);
	int dt = ((double)t2.QuadPart - (double)t1.QuadPart) * 1000000 / (double)nFreq.QuadPart;
	return dt;
}