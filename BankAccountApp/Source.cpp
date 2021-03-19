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

string types[]{ "�������", "��������", "����������", "���������", "�������������", "�������", "��������������" };

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
	cout << "[���� �" << clients[number].number << "]:" << endl;
	cout << "\t���: " << clients[number].fullName << endl;
	cout << "\t��� �����: " << types[clients[number].type] << endl;
	cout << "\t������ �����: " << fixed << setprecision(2) << clients[number].balance << " ������" << endl;
	cout << "\t��������� ���������: " << ctime(&clients[number].lastChange);

}

void main() {
	setlocale(LC_ALL, "Russian");
	cout << "������������ ������ �� ���� ��������� | ����� ������ ��.219/4" << endl << endl;

	string firstNames[10]{ "������", "���������",  "����������",  "����",  "�������",  "��������",  "������",  "����",  "�����",  "����", };
	string lastNames[10]{ "������", "�������",  "�������",  "�������",  "����������",  "������",  "�������",  "�������",  "������",  "�������", };
	for (int i = 0; i < 10; i++) {
		string name = firstNames[rand() % 10] + " " + lastNames[rand() % 10];
		addClient(name, rand() % 4);
		clients[i].balance = (rand() % 50000) + (double)(rand() % 99) / 100;
	}

	int select = 0;

	string inputFullName = ""; int inputType = 0; int inputNumber = 0;
	float inputRange1; float inputRange2;
	do {
		cout << "[���� ��������]:" << endl;
		cout << "\t1) �������� ������ �������" << endl;
		cout << "\t2) �������� ���������� � ���� ��������" << endl;
		cout << "\t3) �������� ��������" << endl;
		cout << "\t4) ����� ��������" << endl;
		cout << "\t5) ����� �� ���������" << endl;

		cout << "�������� �������� - "; cin >> select; cout << endl;

		switch (select) {
		case 1:
			cout << "������� ��� ������� - ";
			cin >> inputFullName;
			cout << "������� ��� ����� (";
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
			cout << "[�������� ��������]:" << endl;
			cout << "\t1) �������� ������� �� ������ �����" << endl;
			cout << "\t2) �������� ���� ��������" << endl;
			cout << "�������� �������� - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "������� � ����� ������� - "; cin >> inputNumber;
				deleteClient(inputNumber);
				break;
			case 2:
				for (int i = 0; i < currentSize; i++) {
					clients[i] = emptyClient;
					currentSize = 0;
				}
				break;
			default:
				cout << "�������� ������ ���� � ��������� 1-2" << endl;
			}
			break;
		case 4:
			cout << "[����� ��������]" << endl;
			cout << "\t1) �� ������ �����" << endl;
			cout << "\t2) �� ��������� �����" << endl;
			cout << "�������� �������� - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "������� ����� ����� ������� - "; cin >> inputNumber;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].number == inputNumber) {
						getClientInfo(i);
					}
				}
				break;
			case 2:
				cout << "������� ������ ����� ��������� - "; cin >> inputRange1;
				cout << "������� ������ ����� ��������� - "; cin >> inputRange2;

				cout << "[����� �������� � �������� � ��������� (" << inputRange1 << " - " << inputRange2 << ")]:" << endl;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].balance >= inputRange1 && clients[i].balance <= inputRange2) {
						cout << "\t(���� �" << clients[i].number << ")" << " ������ �����: " << fixed << setprecision(2) << clients[i].balance << " ������" << endl;
					}
				}
				break;
			default:
				cout << "�������� ������ ���� � ��������� 1-5" << endl;
			}
			break;
		case 5:
			break;
		default:
			cout << "�������� ������ ���� � ��������� 1-5" << endl;
		}
		cout << endl; system("pause"); cout << endl;
	} while (select != 5);
}