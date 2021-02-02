
#include <iostream>
#include "Tanks.h"
#include "Intro.h" 
#include "DataBase.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);


	while (true) {
		cout << "\n                       �������� ������ \n \n" << endl;
		cout << "                       1-�� ������:\n \n" << endl <<
			"                       2-�������� ������:\n \n" << endl <<
			"                       3-�������: \n \n" << endl <<
			"                       4-��������: \n \n" << endl <<
			"                       5-�����:" << endl;

		char state;
		state = _getch();

		switch (state) {
		case '1':system("cls"); Author(); break;
		case '2':system("cls"); DataBase(); break;
		case '3':system("cls"); Game(); break;
		case '4':system("cls"); Intro(); break;
		case '5':exit(1);
		default:system("cls");
		}
	}
}



