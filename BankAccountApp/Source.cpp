#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#define size 100
using namespace std;

struct Account {
	string fullName;
	int type;
	int number;
	float balance;
	time_t lastChange;
};

string types[]{ "срочный", "льготный", "брокерский", "бюджетный", "накопительный", "лицевой", "инвестиционный" };

int accountNumber = 0;
int currentSize = 0;
struct Account clients[size];
struct Account emptyClient;

void addClient(string fullName, int type) {
	clients[currentSize].fullName = fullName;
	clients[currentSize].type = type;
	clients[currentSize].number = ++accountNumber;
	clients[currentSize].balance = 0;
	clients[currentSize].lastChange = time(0);
	currentSize++;
}

void deleteClient(int number) {
	for (int i = 0; i < currentSize; i++) {
		if (clients[i].number == number) {
			for (int j = i; j < currentSize; j++) {
				clients[j].fullName = clients[j + 1].fullName;
				clients[j].type = clients[j + 1].type;
				clients[j].number = clients[j + 1].number;
				clients[j].balance = clients[j + 1].balance;
				clients[j].lastChange = clients[j + 1].lastChange;

			}
			currentSize--;
			break;
		}
	}
}

void getClientInfo(int number) {
	cout << "[Счет №" << clients[number].number << "]:" << endl;
	cout << "\tФИО: " << clients[number].fullName << endl;
	cout << "\tТип счета: " << types[clients[number].type] << endl;
	cout << "\tБаланс счета: " << fixed << setprecision(2) << clients[number].balance << " рублей" << endl;
	cout << "\tПоследнее изменение: " << ctime(&clients[number].lastChange);

}

void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа по теме Структуры | Хорев Кирилл гр.219/4" << endl << endl;

	string firstNames[10]{ "Михаил", "Александр",  "Константин",  "Петр",  "Дмитрий",  "Владимир",  "Кирилл",  "Егор",  "Борис",  "Семён", };
	string lastNames[10]{ "Петров", "Сидоров",  "Лебедев",  "Соколов",  "Виноградов",  "Иванов",  "Вавилов",  "Смирнов",  "Павлов",  "Морозов", };
	for (int i = 0; i < 10; i++) {
		string name = firstNames[rand() % 10] + " " + lastNames[rand() % 10];
		addClient(name, rand() % 4);
		clients[i].balance = (rand() % 50000) + (double)(rand() % 99) / 100;
	}

	int select = 0;

	string inputFullName = ""; int inputType = 0; int inputNumber = 0;
	float inputRange1; float inputRange2;
	do {
		cout << "[Меню действий]:" << endl;
		cout << "\t1) Добавить нового клиента" << endl;
		cout << "\t2) Получить информацию о всех клиентах" << endl;
		cout << "\t3) Удаление клиентов" << endl;
		cout << "\t4) Поиск клиентов" << endl;
		cout << "\t5) Выход из программы" << endl;

		cout << "Выберите действие - "; cin >> select; cout << endl;

		switch (select) {
		case 1:
			cout << "Введите ФИО клиента - ";
			cin >> inputFullName;
			cout << "Введите тип счета (";
			for (int i = 0; i < (sizeof(types) / sizeof(string)); i++) {
				cout << i << " - " << types[i];
				if ((i + 1) == (sizeof(types) / sizeof(string))) {
					cout << ") - ";
				}
				else {
					cout << ", ";
				}
			}
			cin >> inputType;
			addClient(inputFullName, inputType);
			break;
		case 2:
			for (int i = 0; i < currentSize; i++) {
				getClientInfo(i);
			}
			break;
		case 3:
			cout << "[Удаление клиентов]:" << endl;
			cout << "\t1) Удаление клиента по номеру счета" << endl;
			cout << "\t2) Удаление всех клиентов" << endl;
			cout << "Выберите действие - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "Введите № счета клиента - "; cin >> inputNumber;
				deleteClient(inputNumber);
				break;
			case 2:
				for (int i = 0; i < currentSize; i++) {
					clients[i] = emptyClient;
					currentSize = 0;
				}
				break;
			default:
				cout << "Значение должно быть в диапазоне 1-2" << endl;
			}
			break;
		case 4:
			cout << "[Поиск клиентов]" << endl;
			cout << "\t1) По номеру счета" << endl;
			cout << "\t2) По диапазону суммы" << endl;
			cout << "Выберите действие - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "Введите номер счета клиента - "; cin >> inputNumber;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].number == inputNumber) {
						getClientInfo(i);
					}
				}
				break;
			case 2:
				cout << "Введите первое число диапазона - "; cin >> inputRange1;
				cout << "Введите второе число диапазона - "; cin >> inputRange2;

				cout << "[Счета клиентов с балансом в диапазоне (" << inputRange1 << " - " << inputRange2 << ")]:" << endl;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].balance >= inputRange1 && clients[i].balance <= inputRange2) {
						cout << "\t(Счет №" << clients[i].number << ")" << " Баланс счета: " << fixed << setprecision(2) << clients[i].balance << " рублей" << endl;
					}
				}
				break;
			default:
				cout << "Значение должно быть в диапазоне 1-5" << endl;
			}
			break;
		case 5:
			break;
		default:
			cout << "Значение должно быть в диапазоне 1-5" << endl;
		}
		cout << endl; system("pause"); cout << endl;
	} while (select != 5);
}