#include <Windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;


int main()
{
	void SetPurple();
	void SetWhite();
	int theNumber;
	int bound;
	int lastTimes = 5;
	srand(time(0));
	SetPurple();
	cout << "��Ҫ�¶�����ڵ����֣�";
	SetWhite();
	cin >> bound;
	theNumber = rand() % bound;
	int guessNumber;
	cout << "������һ��С��"<< bound <<"������";
	while (1)
	{
		if (lastTimes  > 0)
			lastTimes--;
		else
		{
			cout << "gameover!!!!" << endl;
			break;
		}
		SetWhite();
		cin >> guessNumber;
		SetPurple();
		if (guessNumber == theNumber)
		{
			cout << "��¶��ˣ�\n";
			break;
		}
		else if (guessNumber < theNumber)
		{
			cout << "��С��\n";
		}
		else if (guessNumber > theNumber)
		{
			cout << "�´���\n";
		}
		cout << "ʣ��µĴ���Ϊ��" << lastTimes <<endl;
	}
	return 0;
}


void SetPurple()
{
	WORD color;
	color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		color);
}

void SetWhite()
{
	WORD color;
	color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		color);
}