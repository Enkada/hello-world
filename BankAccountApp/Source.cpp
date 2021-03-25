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

string types[]{ "ñðî÷íûé", "ëüãîòíûé", "áðîêåðñêèé", "áþäæåòíûé", "íàêîïèòåëüíûé", "ëèöåâîé", "èíâåñòèöèîííûé" };

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
	cout << "[Ñ÷åò ¹" << clients[number].number << "]:" << endl;
	cout << "\tÔÈÎ: " << clients[number].fullName << endl;
	cout << "\tÒèï ñ÷åòà: " << types[clients[number].type] << endl;
	cout << "\tÁàëàíñ ñ÷åòà: " << fixed << setprecision(2) << clients[number].balance << " ðóáëåé" << endl;
	cout << "\tÏîñëåäíåå èçìåíåíèå: " << ctime(&clients[number].lastChange);

}

void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Ëàáîðàòîðíàÿ ðàáîòà ïî òåìå Ñòðóêòóðû | Õîðåâ Êèðèëë ãð.219/4" << endl << endl;

	string firstNames[10]{ "Ìèõàèë", "Àëåêñàíäð",  "Êîíñòàíòèí",  "Ïåòð",  "Äìèòðèé",  "Âëàäèìèð",  "Êèðèëë",  "Åãîð",  "Áîðèñ",  "Ñåì¸í", };
	string lastNames[10]{ "Ïåòðîâ", "Ñèäîðîâ",  "Ëåáåäåâ",  "Ñîêîëîâ",  "Âèíîãðàäîâ",  "Èâàíîâ",  "Âàâèëîâ",  "Ñìèðíîâ",  "Ïàâëîâ",  "Ìîðîçîâ", };
	for (int i = 0; i < 10; i++) {
		string name = firstNames[rand() % 10] + " " + lastNames[rand() % 10];
		addClient(name, rand() % 4);
		clients[i].balance = (rand() % 55000) + (double)(rand() % 99) / 100;
	}

	int select = 0;

	string inputFullName = ""; int inputType = 0; int inputNumber = 0;
	float inputRange1; float inputRange2;
	do {
		cout << "[Ìåíþ äåéñòâèé]:" << endl;
		cout << "\t1) Äîáàâèòü íîâîãî êëèåíòà" << endl;
		cout << "\t2) Ïîëó÷èòü èíôîðìàöèþ î âñåõ êëèåíòàõ" << endl;
		cout << "\t3) Óäàëåíèå êëèåíòîâ" << endl;
		cout << "\t4) Ïîèñê êëèåíòîâ" << endl;
		cout << "\t5) Âûõîä èç ïðîãðàììû" << endl;

		cout << "Âûáåðèòå äåéñòâèå - "; cin >> select; cout << endl;

		switch (select) {
		case 1:
			cout << "Ââåäèòå ÔÈÎ êëèåíòà - ";
			cin >> inputFullName;
			cout << "Ââåäèòå òèï ñ÷åòà (";
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
			cout << "[Óäàëåíèå êëèåíòîâ]:" << endl;
			cout << "\t1) Óäàëåíèå êëèåíòà ïî íîìåðó ñ÷åòà" << endl;
			cout << "\t2) Óäàëåíèå âñåõ êëèåíòîâ" << endl;
			cout << "Âûáåðèòå äåéñòâèå - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "Ââåäèòå ¹ ñ÷åòà êëèåíòà - "; cin >> inputNumber;
				deleteClient(inputNumber);
				break;
			case 2:
				for (int i = 0; i < currentSize; i++) {
					clients[i] = emptyClient;
					currentSize = 0;
				}
				break;
			default:
				cout << "Çíà÷åíèå äîëæíî áûòü â äèàïàçîíå 1-2" << endl;
			}
			break;
		case 4:
			cout << "[Ïîèñê êëèåíòîâ]" << endl;
			cout << "\t1) Ïî íîìåðó ñ÷åòà" << endl;
			cout << "\t2) Ïî äèàïàçîíó ñóììû" << endl;
			cout << "Âûáåðèòå äåéñòâèå - "; cin >> select; cout << endl;

			switch (select) {
			case 1:
				cout << "Ââåäèòå íîìåð ñ÷åòà êëèåíòà - "; cin >> inputNumber;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].number == inputNumber) {
						getClientInfo(i);
					}
				}
				break;
			case 2:
				cout << "Ââåäèòå ïåðâîå ÷èñëî äèàïàçîíà - "; cin >> inputRange1;
				cout << "Ââåäèòå âòîðîå ÷èñëî äèàïàçîíà - "; cin >> inputRange2;

				cout << "[Ñ÷åòà êëèåíòîâ ñ áàëàíñîì â äèàïàçîíå (" << inputRange1 << " - " << inputRange2 << ")]:" << endl;
				for (int i = 0; i < currentSize; i++) {
					if (clients[i].balance >= inputRange1 && clients[i].balance <= inputRange2) {
						cout << "\t(Ñ÷åò ¹" << clients[i].number << ")" << " Áàëàíñ ñ÷åòà: " << fixed << setprecision(2) << clients[i].balance << " ðóáëåé" << endl;
					}
				}
				break;
			default:
				cout << "Çíà÷åíèå äîëæíî áûòü â äèàïàçîíå 1-5" << endl;
			}
			break;
		case 5:
			break;
		default:
			cout << "Çíà÷åíèå äîëæíî áûòü â äèàïàçîíå 1-5" << endl;
		}
		cout << endl; system("pause"); cout << endl;
	} while (select != 5);
}
