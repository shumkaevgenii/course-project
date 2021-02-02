#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int Modulus(int iN, int iMod) {
	int iQ = (iN / iMod);
	return iN - (iQ*iMod);
}
char GetChar(int iGenerator, char cBase, int iRange) {
	return (cBase + Modulus(iGenerator, iRange));
}
void Intro()
{
	system("cls");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);

	char caRow[80];
	int j = 7;
	int k = 2;
	int l = 5;
	int m = 1;
	char c;
	while (true) {
		int i = 0;
		while (i < 80) {
			if (caRow[i] != ' ') {
				caRow[i] = GetChar(j + i * i, 33, 30);
				if (((i*i + k) % 71) == 0) {
					SetConsoleTextAttribute(hConsole, 7);
				}
				else {
					SetConsoleTextAttribute(hConsole, 2);
				}
			}
			std::cout << caRow[i];
			++i;
			SetConsoleTextAttribute(hConsole, 2);
		}
		j = (j + 31);
		k = (k + 17);
		l = (l + 47);
		m = (m + 67);
		c = _getch();
		if (c != ' ') {
			system("cls"); SetConsoleTextAttribute(hConsole, 7); return;
		}
		caRow[Modulus(j, 80)] = '-';
		caRow[Modulus(k, 80)] = ' ';
		caRow[Modulus(l, 80)] = '-';
		caRow[Modulus(m, 80)] = ' ';
		Sleep(20);
	}
}


