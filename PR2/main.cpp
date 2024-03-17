#include <iostream>
#include <chrono>
#include <time.h>
#include <Windows.h>
using std::cin;
using std::cout;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::ratio;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
//using namespace std;

time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
nanoseconds result;

const char separator[] = "------------------------------------------------------------------------------------------------------------------------";

struct ListNode 
{
	int data = 0;
	ListNode* next = nullptr;
	ListNode* prev = nullptr;
};

ListNode* list = new ListNode;

ListNode* createList(ListNode* curr) 
{
	if ((cin.get() != '\n') && ((cin.unget()) >> curr->data)) {
		ListNode* next = new ListNode;
		next->prev = curr;
		curr->next = createList(next);
		return curr;
	}
	else {
		delete curr;
		return nullptr;
	}
}

void showList(ListNode* curr) 
{
	cout << "Элементы списка: ";
	while (curr != nullptr) {
		cout << curr->data << ' ';
		curr = curr->next;
	}
	cout << '\n';
}

void checkForNumbers() 
{
	char a = cin.get();
	while (a < '0' || a > '9') {
		//cout << "Следует вводить числа: ";
		cin >> a;
	}
	cin.unget();
}

void launch() 
{
	start = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);

	char commands[] = "1a) Формирование двусвязного списка размерности N, со случайными числами от 0 до 99, где N вводит пользователь\n1b) Формирование двухсвязного списка размерности N, где пользователь вводит в консоль элементы списка, N определяется автоматически\n2g) Получить элемент списка по индексу или по значению\n2i) Вставить элемент в список\n2r) Удалить элемент из списка по индексу или по значению\n2s) Поменять местами элементы списка по индексам\ns) Вывести элементы списка\nc) Вывести список комманд\ne) Выйти из программы\n";

	char command = 'c';

	do {
		if (command == 'e') {
			cout << "Программа завершена по воле пользователя\n";
			break;
		}
		
		else if (command == 'c') {
			cout << commands;
		}

		else if (command == 's') {
			showList(list);
		}

		else if (command == '1') {
			cin >> command;
			if (command == 'a') {
				if (list->next != nullptr) {
					ListNode* curr = list;
					while (curr->next != nullptr) {
						curr = curr->next;
					}
					while (curr != list) {
						curr = curr->prev;
						delete curr->next;
					}
					list->data = 0;
				}

				cout << "Введите размер списка: ";
				int N;
				cin >> N;
				
				if (N > 0) {
					ListNode* curr = list;
					while (N--) {
						curr->data = rand() % 100;
						curr->next = new ListNode;
						curr->next->prev = curr;
						curr = curr->next;
					}
					curr->prev->next = nullptr;
					delete curr;
				}
			}

			else if (command == 'b') {
				if (list->next != nullptr) {
					ListNode* curr = list;
					while (curr->next != nullptr) {
						curr = curr->next;
					}
					while (curr != list) {
						curr = curr->prev;
						delete curr->next;
					}
					list->data = 0;
				}

				cout << "Введите элементы: ";
				checkForNumbers();
				createList(list);
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