#include <iostream>
#include <Windows.h>
using std::cin;
using std::cout;
//using namespace std;

const char separator[] = "------------------------------------------------------------------------------------------------------------------------";

struct ListNode 
{
	int data = 0;
	ListNode* next = nullptr;
	ListNode* prev = nullptr;
};

void launch() 
{
	char commands[] = "1a) Формирование двусвязного списка размерности N, со случайными числами от 0 до 99, где N вводит пользователь\n1b) Формирование двухсвязного списка размерности N, где пользователь вводит в консоль элементы списка, N определяется автоматически\n2g) Получить элемент списка по индексу или по значению\n2i) Вставить элемент в список\n2r) Удалить элемент из списка по индексу или по значению\n2s) Поменять местами элементы списка по индексам\nc) Вывести список комманд\ne) Выйти из программы\n";

	char command = 'c';

	do {
		if (command == 'e') {
			cout << "Программа завершена по воле пользователя\n";
			break;
		}
		
		else if (command == 'c') {
			cout << commands;
		}

		else if (command == '1') {
			cin >> command;
			if (command == 'a') {
				cout << "Correct\n";
			}
		}

		cout << separator << '\n';
		cout << "Введите комманду: ";
		cin >> command;
		cout << '\n';

	} while (true);
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	launch();

	return 0;
}