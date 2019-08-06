// diapozon.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// структура диапазона, тут состояние доски, положение пробела, 
//предыдущее положение пробела, и номер в списке от которого пошло
struct Dia {
	char s[3][3];
	int SpaceY;
	int SpaceX;
	int NX;
	int NY;
	int last;
};

//вектор структур
vector <Dia> nextStates;

int main()
{
	unsigned int start_time = clock();
	
	Dia firstState;

	//начальное положение
	firstState.s[0][0] = 'd';
	firstState.s[0][1] = 'i';
	firstState.s[0][2] = 'a';
	firstState.s[1][0] = 'p';
	firstState.s[1][1] = 'a';
	firstState.s[1][2] = 'z';
	firstState.s[2][0] = 'o';
	firstState.s[2][1] = 'n';
	firstState.s[2][2] = ' ';

	firstState.SpaceX = 2;
	firstState.SpaceY = 2;
	firstState.NX = 3;
	firstState.NY = 3;	
	firstState.last = 0;

	Dia lastState;

	//нужное в итоге положение
	lastState.s[0][0] = 'a';
	lastState.s[0][1] = 'a';
	lastState.s[0][2] = 'i';
	lastState.s[1][0] = 'z';
	lastState.s[1][1] = 'd';
	lastState.s[1][2] = 'p';
	lastState.s[2][0] = ' ';
	lastState.s[2][1] = 'n';
	lastState.s[2][2] = 'o';

	nextStates.push_back(firstState);	
	int k = 0;
	int k5 = 0;

	while (nextStates.empty()!=true) 
	{
		Dia CurState = nextStates[k];
		bool t = true;
		/*for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << CurState.s[i][j];
			cout << endl;
		}
		cout << endl;*/
		//_getch();
		// проверка является ли текущий элемент curstate последним
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (CurState.s[i][j] != lastState.s[i][j])
					t = false;
		//если мы дошли до нужного раскручиваем цепочку назад, печатая до начального
		if (t == true)
		{
			cout << clock() - start_time << "msec" << endl;
			cout << "perfect" << endl;
			_getch();
			while (true)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
						cout << CurState.s[i][j];
					cout << endl;
				}
				cout << endl;	
				if (CurState.last == 0)
				{
					
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
							cout << firstState.s[i][j];
						cout << endl;
					}
					cout << k5 << endl;
					_getch();				
					exit(0);
				}
				CurState = nextStates[CurState.last];				
				//_getch();	
				k5++;
			}	
		}
		//иначе вписываем в вектор новые элементы которые соответствуют условиям
		//смещение вниз (1 проверка - что это не 1 ряд. 2 и 3 - что не пришли ли мы сверху)
		if ((CurState.SpaceX > 0) & ((CurState.SpaceX - 1 != CurState.NX) || (CurState.SpaceY != CurState.NY)))
		{
			//создаем и заполняем все поля структуры нового элемента
			Dia newStateLeft;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					newStateLeft.s[i][j] = CurState.s[i][j];
			//меняем местами пробел и элемент, двигаем пробел
			char tmp = newStateLeft.s[CurState.SpaceX - 1][CurState.SpaceY];
			newStateLeft.s[CurState.SpaceX - 1][CurState.SpaceY] = ' ';
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY] = tmp;
			newStateLeft.last = k;
			newStateLeft.SpaceX = CurState.SpaceX - 1;
			newStateLeft.SpaceY = CurState.SpaceY; 
			newStateLeft.NX = CurState.SpaceX;
			newStateLeft.NY = CurState.SpaceY;
			//закидываем его в конец очереди
			nextStates.push_back(newStateLeft);
			
			/*cout << "Xc=" << CurState.SpaceX << " ";
			cout << "Yc=" << CurState.SpaceY << endl; 
			cout << "Xn=" << newStateLeft.SpaceX << " ";
			cout << "Yn=" << newStateLeft.SpaceY << endl;					
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					cout << newStateLeft.s[i][j];
				cout << "\n";
			}
			_getch();*/
		}
		//смещаем пробел вверх
		if ((CurState.SpaceX < 2) & ((CurState.SpaceX + 1 != CurState.NX) || (CurState.SpaceY != CurState.NY)))
		{
			Dia newStateLeft;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					newStateLeft.s[i][j] = CurState.s[i][j];

			char tmp = newStateLeft.s[CurState.SpaceX + 1][CurState.SpaceY];
			newStateLeft.s[CurState.SpaceX + 1][CurState.SpaceY] = ' ';
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY] = tmp;

			newStateLeft.last = k;
			newStateLeft.SpaceX = CurState.SpaceX + 1;
			newStateLeft.SpaceY = CurState.SpaceY;
			newStateLeft.NX = CurState.SpaceX;
			newStateLeft.NY = CurState.SpaceY;
			nextStates.push_back(newStateLeft);
		}
		
		//смещаем пробел вправо
		if ((CurState.SpaceY < 2) & ((CurState.SpaceX != CurState.NX) || (CurState.SpaceY + 1 != CurState.NY)))
		{
			Dia newStateLeft;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					newStateLeft.s[i][j] = CurState.s[i][j];

			char tmp = newStateLeft.s[CurState.SpaceX][CurState.SpaceY + 1];
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY + 1] = ' ';
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY] = tmp;

			newStateLeft.last = k;
			newStateLeft.SpaceX = CurState.SpaceX;
			newStateLeft.SpaceY = CurState.SpaceY + 1;
			newStateLeft.NX = CurState.SpaceX;
			newStateLeft.NY = CurState.SpaceY;
			nextStates.push_back(newStateLeft);
		}
		
		//влево
		if ((CurState.SpaceY > 0) & ((CurState.SpaceX != CurState.NX) || (CurState.SpaceY - 1 != CurState.NY)))
		{
			Dia newStateLeft;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					newStateLeft.s[i][j] = CurState.s[i][j];

			char tmp = newStateLeft.s[CurState.SpaceX][CurState.SpaceY - 1];
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY - 1] = ' ';
			newStateLeft.s[CurState.SpaceX][CurState.SpaceY] = tmp;

			newStateLeft.last = k;
			newStateLeft.SpaceX = CurState.SpaceX;
			newStateLeft.SpaceY = CurState.SpaceY - 1;
			newStateLeft.NX = CurState.SpaceX;
			newStateLeft.NY = CurState.SpaceY;
			nextStates.push_back(newStateLeft);
		}
		k++;
	}
	_getch();
}

