#include <iostream>
#include <chrono>
#include <time.h>
#include <Windows.h>

using std::cin;
using std::cout;
using std::swap;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::ratio;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;
//using namespace std;

time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
nanoseconds result;

int arraySize = 16;
int arrayEnd = 0;
const char separator[] = "------------------------------------------------------------------------------------------------------------------------";

struct ListNode 
{
	int data = NULL;
	ListNode* next = nullptr;
	ListNode* prev = nullptr;
};

ListNode* list = new ListNode;
int* array = new int[arraySize];

int* expandArray(int* array) 
{
	int* tmp = array;
	array = new int[arraySize * 2];
	for (int i = 0; i < arraySize; i++) {
		*(array+i) = *(tmp+i);
	}
	arraySize *= 2;
	delete[] tmp;
	return array;
}

int* fillArray(int* array) 
{
	int a;
	int i = 0;
	while ((cin.get() != '\n') && ((cin.unget()) >> a)) {
		if ((i + 1) == arraySize) {
			array = expandArray(array);
		}
		*(array + i) = a;
		i++;
	}
	arrayEnd = i;
	
	return array;
}

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

void showArray(int* array) 
{
	cout << "Элементы динмас: ";
	for (int i = 0; i < arrayEnd; i++) {
		cout << *(array + i) << ' ';
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

void clearList(ListNode* list) 
{
	ListNode* curr = list;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	while (curr != list) {
		curr = curr->prev;
		delete curr->next;
	}
	list->data = NULL;
}

int getLength(ListNode* curr) 
{
	int res = 0;
	while (curr != nullptr) {
		curr = curr->next;
		res++;
	}
	return res;
}

float getValue(ListNode* curr, int index) 
{
	int i = 0;
	while (curr != nullptr) {
		if (i == index) {
			return curr->data;
		}
		curr = curr->next;
		i++;
	}
	return 0.5;
}

int getIndex(ListNode* curr, int value) 
{
	int i = 0;
	while (curr != nullptr) {
		if (curr->data == value) {
			return i;
		}
		curr = curr->next;
		i++;
	}
	return -1;
}

bool insertValue(ListNode* curr, int index, int value) 
{
	if (index < getLength(curr) && index >= 0) {
		ListNode* listNode = new ListNode;
		int i = 0;
		while (i < (index-1)) {
			curr = curr->next;
			i++;
		}
		if (index == 0) {
			int tmp = curr->data;
			curr->data = value;
			listNode->data = tmp;
		}
		else {
			listNode->data = value;
		}
		listNode->next = curr->next;
		listNode->prev = curr;
		curr->next->prev = listNode;
		curr->next = listNode;
		return 1;
	}
	else if (getLength(curr) == index) {
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		ListNode* listNode = new ListNode;
		listNode->data = value;
		listNode->prev = curr;
		curr->next = listNode;
		return 1;
	}
	else {
		return 0;
	}
}

int* insertValueArray(int* array, int value, int index) 
{
	int* tmp = array;
	arrayEnd++;
	if (arrayEnd > arraySize) {
		arraySize *= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (index == i) {
			*(array + i) = value;
			j--;
		}
		else {
			*(array + i) = *(tmp + j);
		}
	}
	delete[] tmp;

	return array;
}

float removeByIndex(ListNode* curr, int index) 
{
	if (getLength(curr) > index && index >= 0) {
		if (getLength(curr) == 1 && index == 0) {
			int res = curr->data;
			curr->data = 0;
			return res;
		}
		else if (index == 0) {
			int res = curr->data;
			curr->data = curr->next->data;
			if (curr->next->next != nullptr) {
				curr->next->next->prev = curr;
			}
			ListNode* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
			return res;
		}
		else {
			int i = 0;
			while (i < index) {
				curr = curr->next;
				i++;
			}
			if (curr->prev != nullptr) {
				curr->prev->next = curr->next;
			}
			if (curr->next != nullptr) {
				curr->next->prev = curr->prev;
			}
			int res = curr->data;
			delete curr;
			return res;
		}
	}
	else {
		return 0.5;
	}
}

int removeByValue(ListNode* curr, int value) 
{
	int i = 0;
	while (curr != nullptr && curr->data != value) {
		curr = curr->next;
		i++;
	}
	if (curr != nullptr) {
		if (getLength(curr) == 1 && i == 0) {
			int res = curr->data;
			curr->data = 0;
			return i;
		}
		else if (i == 0) {
			int res = curr->data;
			curr->data = curr->next->data;
			if (curr->next->next != nullptr) {
				curr->next->next->prev = curr;
			}
			ListNode* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
			return i;
		}
		else {
			if (curr->prev != nullptr) {
				curr->prev->next = curr->next;
			}
			if (curr->next != nullptr) {
				curr->next->prev = curr->prev;
			}
			int res = curr->data;
			delete curr;
			return i;
		}
	}
	else {
		return -1;
	}
}

int* removeByIndexArray(int* array, int index) 
{
	int* tmp = array;
	arrayEnd--;
	if (arrayEnd < arraySize / 2) {
		arraySize /= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (index == i) {
			j++;
		}
		*(array + i) = *(tmp + j);
	}
	delete[] tmp;

	return array;
}

int* removeByValueArray(int* array, int value) {
	int* tmp = array;
	arrayEnd--;
	if (arrayEnd < arraySize / 2) {
		arraySize /= 2;
	}
	array = new int[arraySize];

	for (int i = 0, j = 0; i < arrayEnd; i++, j++) {
		if (value == *(tmp+i)) {
			j++;
		}
		*(array + i) = *(tmp + j);
	}
	delete[] tmp;

	return array;
}

bool swapElements(ListNode* curr, int i, int j) 
{
	if (i > j) {
		swap(i, j);
	}

	if (getLength(curr) > i && getLength(curr) > j && i >= 0 && j >= 0 && i != j) {
		int count = 0;
		while (count < i) {
			curr = curr->next;
			count++;
		}
		ListNode* second = curr;
		while (count < j) {
			second = second->next;
			count++;
		}

		if (i == 0) {
			swap(curr->data, second->data);
		}

		else if (abs(i - j) == 1) {
			ListNode* firstPrev = curr->prev;

			curr->prev = second;
			curr->next = second->next;
			if (second->next != nullptr) {
				second->next->prev = curr;
			}
			second->next = curr;
			second->prev = firstPrev;
			if (firstPrev != nullptr) {
				firstPrev->next = second;
			}
		}

		else {
			ListNode* firstPrev = curr->prev;
			ListNode* firstNext = curr->next;

			curr->prev = second->prev;
			curr->next = second->next;
			if (second->prev != nullptr) {
				second->prev->next = curr;
			}
			if (second->next != nullptr) {
				second->next->prev = curr;
			}

			second->prev = firstPrev;
			second->next = firstNext;
			if (firstPrev != nullptr) {
				firstPrev->next = second;
			}
			if (firstNext != nullptr) {
				firstNext->prev = second;
			}
		}

		return 1;
	}

	return 0;
}

void launch() 
{
	start = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);

	char commands[] = "1a) Формирование двусвязного списка размерности N, со случайными числами от 0 до 99, где N вводит пользователь\n1b) Формирование двухсвязного списка размерности N, где пользователь вводит в консоль элементы списка, N определяется автоматически\n2g) Получить элемент списка по индексу или по значению\n2i) Вставить элемент в список\n2d) Удалить элемент из списка по индексу или по значению\n2s) Поменять местами элементы списка по индексам\ns) Вывести элементы списка\nc) Вывести список комманд\ne) Выйти из программы\n";

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
			showArray(array);
		}

		// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33

		else if (command == '1') {
			cin >> command;
			if (command == 'a') {
				if (list->data != NULL) {
					clearList(list);
				}

				cout << "Введите размер списка: ";
				int N;
				cin >> N;
				
				if (N > 0) {
					srand(time(NULL));
					start = steady_clock::now();
					ListNode* curr = list;
					while (N--) {
						curr->data = rand() % 100;
						curr->next = new ListNode;
						curr->next->prev = curr;
						curr = curr->next;
					}
					curr->prev->next = nullptr;
					delete curr;
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);
					cout << "Время на создание двухсвязного списка: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

					start = steady_clock::now();
					int i = 0;
					curr = list;
					while (curr != nullptr) {
						if ((i + 1) == arraySize) {
							array = expandArray(array);
						}
						*(array + i) = curr->data;
						curr = curr->next;
						i++;
					}
					arrayEnd = i;
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);
					cout << "Время на создание динамического массива: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
				}

				else {
					cout << "Список не должен быть пустым!!!\n";
				}
			}

			else if (command == 'b') {
				if (list->data != NULL) {
					clearList(list);
				}

				cout << "Введите элементы списка: ";
				checkForNumbers();
				start = steady_clock::now();
				createList(list);
				end = steady_clock::now();

				result = duration_cast<nanoseconds>(end - start);
				cout << "Время на создание двухсвязного списка: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

				cout << "Введите элементы динамического массива: ";
				checkForNumbers();
				start = steady_clock::now();
				array = fillArray(array);
				end = steady_clock::now();

				result = duration_cast<nanoseconds>(end - start);
				cout << "Время на создание динамического массива: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

			}
		}

		else if (command == '2') {
			cin >> command;
			if (command == 'g') {
				cout << "По индексу или по значению(i, v): ";
				cin >> command;
				if (command == 'i') {
					cout << "Введите индекс значения в с списке: ";
					int index;
					float res;
					cin >> index;
					start = steady_clock::now();
					res = getValue(list, index);
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == 0.5) {
						cout << "Введённый индекс выходит за рамки списка!!!\n";
					}
					else {
						cout << "На позиции " << index << " находится значение " << res << '\n';
					}

					cout << "Время на получение элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

					start = steady_clock::now();
					if (index >= 0 && index < arrayEnd) {
						res = array[index];
					}
					else {
						res = -1;
					}
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == -1) {
						cout << "Введённый индекс выходит за рамки динамического массива!!!\n";
					}
					else {
						cout << "На позиции " << index << " находится значение " << res << '\n';
					}

					cout << "Время на получение элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
				}

				else if (command == 'v') 
				{
					cout << "Введите значение в списке: ";
					int value, res;
					cin >> value;
					start = steady_clock::now();
					res = getIndex(list, value);
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == -1) {
						cout << "Введённое значение отсутствует в списке!!!\n";
					}
					else {
						cout << "Элемент со значением " << value << " находится на позиции " << res << '\n';
					}

					cout << "Время на получение индекса: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

					start = steady_clock::now();
					res = -1;
					for (int i = 0; i < arrayEnd; i++) {
						if (*(array + i) == value) {
							res = i;
							break;
						}
					}
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == -1) {
						cout << "Введённое значение отсутствует в динамическом массиве!!!\n";
					}
					else {
						cout << "Элемент со значением " << value << " находится на позиции " << res << '\n';
					}

					cout << "Время на получение индекса: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
				}
			}

			else if (command == 'i') {
				cout << "Введите позицию для нового элемента: ";
				int index, value;
				bool res;
				cin >> index;
				cout << "Введите значение элемента: ";
				cin >> value;

				start = steady_clock::now();
				res = insertValue(list, index, value);
				end = steady_clock::now();
				result = duration_cast<nanoseconds>(end - start);

				if (!res) {
					cout << "Вставка не произведена потому что данная позицая удалена от ближайшего элемента больше чем на 1, либо позиция отрицательна\n";
				}
				else {
					cout << "Вставка была произведена, вставленный элемент на позиции " << index << '\n';
				}

				cout << "Время на вставку элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

				start = steady_clock::now();
				if (index >= 0 && index < (arrayEnd+1)) {
					array = insertValueArray(array, value, index);
					res = true;
				}
				else {
					res = false;
				}
				end = steady_clock::now();
				result = duration_cast<nanoseconds>(end - start);

				if (!res) {
					cout << "Вставка не произведена потому что данная позицая удалена от ближайшего элемента больше чем на 1, либо позиция отрицательна\n";
				}
				else {
					cout << "Вставка была произведена, вставленный элемент на позиции " << index << '\n';
				}

				cout << "Время на вставку элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
			}

			else if (command == 'd') {
				cout << "По индексу или по значению(i, v): ";
				cin >> command;
				if (command == 'i') {
					cout << "Введите индекс значения в с списке: ";
					int index;
					float res;
					cin >> index;
					start = steady_clock::now();
					res = removeByIndex(list, index);
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == 0.5) {
						cout << "Введённый индекс выходит за рамки списка!!!\n";
					}
					else {
						cout << "С позиции " << index << " был удалён элемент со значением "<< res << '\n';
					}

					cout << "Время на удаление элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

					res = false;
					int value;
					start = steady_clock::now();
					if (index >= 0 && index < arrayEnd) {
						value = *(array+index);
						array = removeByIndexArray(array, index);
						res = true;
					}
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);
					
					if (!res) {
						cout << "Введённый индекс выходит за рамки динамического массива!!!\n";
					}
					else {
						cout << "С позиции " << index << " был удалён элемент со значением " << value << '\n';
					}

					cout << "Время на удаление элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
				}

				else if (command == 'v')
				{
					cout << "Введите значение в списке: ";
					int value, res;
					cin >> value;
					start = steady_clock::now();
					res = removeByValue(list, value);
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == -1) {
						cout << "Введённое значение отсутствует в списке!!!\n";
					}
					else {
						cout << "Элемент со значением " << value << " был удалён с позиции " << res << '\n';
					}

					cout << "Время на удаление элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

					start = steady_clock::now();
					array = removeByValueArray(array, value);
					end = steady_clock::now();
					result = duration_cast<nanoseconds>(end - start);

					if (res == -1) {
						cout << "Введённое значение отсутствует в динамическом массиве!!!\n";
					}
					else {
						cout << "Элемент со значением " << value << " был удалён с позиции " << res << '\n';
					}

					cout << "Время на удаление элемента: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
				}
			}

			else if (command == 's') {
				cout << "Введите индексы элементов значения которых обменяются: ";
				int i, j;
				bool res;
				cin >> i >> j;
				start = steady_clock::now();
				res = swapElements(list, i, j);
				end = steady_clock::now();
				result = duration_cast<nanoseconds>(end - start);

				if (!res) {
					cout << "Введённые индексы выходят за рамки списка\n";
				}
				else {
					cout << "Элемента на позициях " << i << " и " << j << " поменялись местами\n";
				}

				cout << "Время на обмен элементов: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";

				start = steady_clock::now();
				if (res) {
					swap(*(array + i), *(array + j));
				}
				end = steady_clock::now();
				result = duration_cast<nanoseconds>(end - start);
				
				if (!res) {
					cout << "Введённые индексы выходят за рамки динамического массива\n";
				}
				else {
					cout << "Элемента на позициях " << i << " и " << j << " поменялись местами\n";
				}

				cout << "Время на обмен элементов: " << (result.count() / 1000000.0) << "ms(" << result.count() << "ns)\n";
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