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
		cout << "ФИО: " << Surname << " " << Name << " " << Patronymic << endl;
		cout << "Адрес: " << Address << endl;
		cout << "Номер телефона: " << PhoneNumber << endl;
		cout << "Дата рождения: " << DateOfBirth << endl;
		cout << "Описание: " << Specification << endl;
		cout << "__________________________________________" << endl;
	}
};

vector <Notebook> book;

void Pop_by_Name()
{
	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();

	system("cls");
	cout << "                  Удаление заданного объекта\n \n";
	cout << "Введите имя объекта,который хотите удалить:" << endl;

	int total = 0;

	string str;
	cin >> str;
	do {
		if (!strncmp(str.c_str(), p->Name.c_str(), strlen(str.c_str()))) total++;
	} while ((++p) < end);

	cout << "Найдено " << total << " объектов с именем " << str << "\n" << endl;

	p = book.begin();

	do {
		if (!strncmp(str.c_str(), p->Name.c_str(), strlen(str.c_str())))
		{
			p->Show();
			cout << "Хотите удалить " << p->Name << " из базы данных\n" << "1-Да\n2-Нет" << endl;
			char state;
			state = _getch();
			if (state == '1') {
				p = book.erase(p);
				end = book.end();
				Sleep(200); cout << "-";
				Sleep(1000); cout << "\n   -";
				Sleep(1000); cout << "\n        -" << "\n          " << "Объект удален"; _getch(); system("cls");
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
	cout << "                 Все объекты записной книжки\n \n";
	do {
		p->Show();
	} while ((++p) < end);
	cout << "Всего в базе " << book.size() << " человек.\n" << endl;
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
	cout << "                   Добавление нового объекта\n \n";
	cout << "Введите ФИО: "; cin >> Surname >> Name >> Patronymic;
	cout << "Введите адрес: "; cin >> Address;
	cout << "Введите дату рождения: "; cin >> DateOfBirth;
	cout << "Введите номер телефона: "; cin >> PhoneNumber;
	cout << "Введите описание: "; cin >> Specification;

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

	//Вывод каталога из программы в очищенную базу
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
	cout << "                       Поиск по фамилии\n \n";
	cout << "Введите фамилию: ";
	cin >> str;

	vector<Notebook>::iterator p = book.begin();
	vector<Notebook>::iterator end = book.end();

	//Переменная для проверки: был ли найден хоть один элемент.
	bool check = false;

	//Вывод Совпадений
	do
	{
		if (!strncmp(str.c_str(), p->Surname.c_str(), strlen(str.c_str())))
		{
			p->Show();
			check = true;
		}
	} while (++p < end);

	//Если совпадений не найдено:
	if (!check) cout << "Совпадений не найдено..\n";
	_getch();
	system("cls");
}

void Author() {
	system("cls");
	printf_s("\n \n \n \n \n \n \n             ______________________________________\n");

	printf_s("            |КУРСОВАЯ РАБОТА ПО ПРОГРАММИРОВАНИЮ   | \n \n");

	printf_s("            |Преподователь: Шафеева О.П.           |\n \n");

	printf_s("            |Выполнил работу : Шумка Е.А           |\n \n");

	printf_s("            |Группа:ИВТ-183                        |\n");

	printf_s("             ______________________________________ \n \n");

	_getch();

	system("cls");
}

void DataBase()
{
	Init();
	cout << "\n \n                        Меню записной книжки\n \n";
	while (true) {
		cout << "               1-Добавить новый объект в записную книжку: \n \n" << endl <<
			"               2-Поиск объекта по фимилии: \n \n" << endl <<
			"               3-Удаление заданного объекта: \n \n" << endl <<
			"               4-Сохранение данных: \n \n" << endl <<
			"               5-Вывод всех объектов: \n \n" << endl <<
			"               6-Выход: \n \n" << endl;


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