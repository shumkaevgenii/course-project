#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Notebook {
	string Name;
	string Surname;
	string Patronymic;
	string Address;
	string PhoneNumber;
	string DateOfBirth;
	string Specification;

	Notebook(string Surname,
		string Name,
		string Patronymic,
		string Address,
		string PhoneNumber,
		string DateOfBirth,
		string Specification) {
		this->Surname = Surname;
		this->Name = Name;
		this->Patronymic = Patronymic;
		this->Address = Address;
		this->DateOfBirth = DateOfBirth;
		this->PhoneNumber = PhoneNumber;
		this->Specification = Specification;
	}

	void Show() {
		cout << "���: " << Surname << " " << Name << " " << Patronymic << endl;
		cout << "�����: " << Address << endl;
		cout << "����� ��������: " << PhoneNumber << endl;
		cout << "���� ��������: " << DateOfBirth << endl;
		cout << "��������: " << Specification << endl;
		cout << "__________________________________________" << endl;
	}
};

vector <Notebook> book;

void Pop_by_Name()
{
	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();

	system("cls");
	cout << "                  �������� ��������� �������\n \n";
	cout << "������� ��� �������,������� ������ �������:" << endl;

	int total = 0;

	string str;
	cin >> str;
	do {
		if (!strncmp(str.c_str(), p->Name.c_str(), strlen(str.c_str()))) total++;
	} while ((++p) < end);

	cout << "������� " << total << " �������� � ������ " << str << "\n" << endl;

	p = book.begin();

	do {
		if (!strncmp(str.c_str(), p->Name.c_str(), strlen(str.c_str())))
		{
			p->Show();
			cout << "������ ������� " << p->Name << " �� ���� ������\n" << "1-��\n2-���" << endl;
			char state;
			state = _getch();
			if (state == '1') {
				p = book.erase(p);
				end = book.end();
				Sleep(200); cout << "-";
				Sleep(1000); cout << "\n   -";
				Sleep(1000); cout << "\n        -" << "\n          " << "������ ������"; _getch(); system("cls");
			}
		}
	} while ((++p) < end);

	system("cls");
}

void Show_everyone()
{
	system("cls");
	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();
	cout << "                 ��� ������� �������� ������\n \n";
	do {
		p->Show();
	} while ((++p) < end);
	cout << "����� � ���� " << book.size() << " �������.\n" << endl;
}

void New_human() {
	system("cls");

	string Name;
	string Surname;
	string Patronymic;
	string Address;
	string PhoneNumber;
	string DateOfBirth;
	string Specification;
	cout << "                   ���������� ������ �������\n \n";
	cout << "������� ���: "; cin >> Surname >> Name >> Patronymic;
	cout << "������� �����: "; cin >> Address;
	cout << "������� ���� ��������: "; cin >> DateOfBirth;
	cout << "������� ����� ��������: "; cin >> PhoneNumber;
	cout << "������� ��������: "; cin >> Specification;

	book.push_back(Notebook(Surname, Name, Patronymic, Address, DateOfBirth, PhoneNumber, Specification));

	system("cls");
}

void Init()
{
	ifstream in("Notebook.txt");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string Name;
	string Surname;
	string Patronymic;
	string Address;
	string PhoneNumber;
	string DateOfBirth;
	string Specification;

	while (!in.eof())
	{
		getline(in, Surname);
		getline(in, Name);
		getline(in, Patronymic);
		getline(in, Address);
		getline(in, PhoneNumber);
		getline(in, DateOfBirth);
		getline(in, Specification);

		book.push_back(Notebook(Surname, Name, Patronymic, Address, DateOfBirth, PhoneNumber, Specification));
	}

	in.close();
}

void Close()
{
	ofstream out("Notebook.txt");

	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();

	//����� �������� �� ��������� � ��������� ����
	do
	{
		out << p->Surname << endl;
		out << p->Name << endl;
		out << p->Patronymic << endl;
		out << p->Address << endl;
		out << p->PhoneNumber << endl;
		out << p->DateOfBirth << endl;
		out << p->Specification << endl;
	} while (++p < end);

	out.close();
	system("cls");
	//exit(0);
}

void Search_by_Surname()
{
	system("cls");
	string str;
	cout << "                       ����� �� �������\n \n";
	cout << "������� �������: ";
	cin >> str;

	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();

	//���������� ��� ��������: ��� �� ������ ���� ���� �������.
	bool check = false;

	//����� ����������
	do
	{
		if (!strncmp(str.c_str(), p->Surname.c_str(), strlen(str.c_str())))
		{
			p->Show();
			check = true;
		}
	} while (++p < end);

	//���� ���������� �� �������:
	if (!check) cout << "���������� �� �������..\n";
	_getch();
	system("cls");
}

void Author() {
	system("cls");
	printf_s("\n \n \n \n \n \n \n             ______________________________________\n");

	printf_s("            |�������� ������ �� ����������������   | \n \n");

	printf_s("            |�������������: ������� �.�.           |\n \n");

	printf_s("            |�������� ������ : ����� �.�           |\n \n");

	printf_s("            |������:���-183                        |\n");

	printf_s("             ______________________________________ \n \n");

	_getch();

	system("cls");
}

void DataBase()
{
	Init();
	cout << "\n \n                        ���� �������� ������\n \n";
	while (true) {
		cout << "               1-�������� ����� ������ � �������� ������: \n \n" << endl <<
			"               2-����� ������� �� �������: \n \n" << endl <<
			"               3-�������� ��������� �������: \n \n" << endl <<
			"               4-���������� ������: \n \n" << endl <<
			"               5-����� ���� ��������: \n \n" << endl <<
			"               6-�����: \n \n" << endl;


		char state;
		state = _getch();

		switch (state) {
		case '1':New_human(); break;
		case '2':Search_by_Surname(); break;
		case '3':Pop_by_Name(); break;
		case '4':Close(); break;
		case '5':Show_everyone(); break;
		case '6':system("cls"); return;
		default:system("cls");
		}
	}
}