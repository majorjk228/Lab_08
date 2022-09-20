// Задание №8, Вариант 3.
// https://www.cyberforum.ru/cpp-beginners/thread1184533.html
// http://comp-science.narod.ru/Progr/file_c.htm
// сортировка бинарного файла си
// https://www.cyberforum.ru/c-beginners/thread2199180.html
// https://vscode.ru/task/sortirovka-massiva-struktur.html сортировка

#include <iostream>
#include <stdio.h>		// Для структуры предопределенного типа FILE
#include <windows.h>    // Библиотека для русской локализации
#include <conio.h>		// Для структуры предопределенного типа FILE
#include <fstream>		// Для создания файла

struct State
{
	char name[35];      // Название
	char capital[35];   // Столица
	int population;     // Численность населения
	float area;         // Занимаемая площадь
};

FILE* pf;	// Первый изначальный файл
FILE* pf2;	// Второй измененный файл
State a, Arr[20];


void form(int);	 // Объявляем методы(функции)
void sort(int); 
void output(int);
void del(int);
void create_new_file(int);
void add(int, int);

int main()
{
	SetConsoleCP(1251);         // Ввод с консоли в кодировке 1251 для русской локализации.
	SetConsoleOutputCP(1251);   // Вывод на консоль в кодировке 1251 для русской локализации.

	std::cout << "Блоковый ввод-вывод\n";

	int k, q;
	//формирование записей в файле
	std::cout << "\n\nВведите количество государств, о которых вы хотите внести сведения (Не более 20): ";
	std::cin >> k;
	// заполним файл
	form(k);
	//отсортируем
	sort(k);
	//form(k);
	//выведем сформированные данные
	create_new_file(k);
	output(k);
	//form(k);
	// 
	// Удалить элемент, номер вводится с клавиатуры.
	std::cout << "Задайте минимальную численность населения: \n";;
	del(k);
	k--;	// Уменьшаем кол-во блоков(структур)
	sort(k);
	//create_new_file(k);
	output(k);
	//output(k);
	// 
	//добавляем элемент после указанной фамилии
	std::cout << "Укажите элемент, после которого нужно внести новые сведения (Обратите внимание на общее количество элементов): ";
	std::cin >> q;
	add(k, q);
	k++; // Добавляем новый элемент в структуру
	output(k);
	create_new_file(k); //запишем в файл новые данные
	return 0;
}

void form(int k)
{
	//открытие файла
	if ((pf = fopen("test.dat", "wb")) == NULL) // Создаем двоичный файл для записи.
	{
		std::cout << "\nОшибка при открытии файла";
		exit(1);
	}
	// Формирование записей в файле
	std::cout << "\nВведите сведения о " << k << " государствах \n";
	for (int i = 0; i < k; i++)
	{
		std::cout << "Введите название государства: \n";
		std::cin >> a.name;
		std::cout << "Введите столицу: \n";
		std::cin >> a.capital;
		std::cout << "Введите численность населения: \n";
		std::cin >> a.population;
		std::cout << "Введите занимаемую площадь: \n";
		std::cin >> a.area;
		std::cout << "\n";
		fwrite(&a, sizeof(State), 1, pf); // Записываем прямо в структуру
		if (ferror(pf)) exit(1);
	}
	fclose(pf);
	//считывание информации с файла
	if ((pf = fopen("test.dat", "rb")) == NULL) exit(1); // Открываем двоичный файл для чтения.
	int j = 0;
	while (!feof(pf) && j < k) // СЧитываем бинарный файл до самого конца
	{
		fread(&Arr[j], sizeof(State), 1, pf);
		j++;
	}
	fclose(pf);
	return;
}

void sort(int k) // Функция сортирует структуру от меньшего к большему, сделано для того чтобы структуры корректно взаимозаменилсь между собой при удалении(В с++ нельзя явно удалить элементы массива, поэтому я делаю замещение к примеру 2 массива верного на 1 не верный и убираю 2 массив),
				 // и добавлении новых элементов
{
	State tmp;

	for (int i = k - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			// сравниваем элементы массива структур по сумме баллов студента
			if (Arr[j].population > Arr[j + 1].population)
			{
				tmp = Arr[j];
				Arr[j] = Arr[j + 1];
				Arr[j + 1] = tmp;
			}
		}
	}
}

void output(int k)	// Выводим данные с файла
{
	std::cout << "\nДанные о " << k << " Государствах\n";
	for (int i = 0; i < k; i++)
	{
		std::cout << "\nНазвание государства: " << Arr[i].name << "\n";
		std::cout << "Столица: " << Arr[i].capital << "\n";
		std::cout << "Численность населения: " << Arr[i].population << "\n";
		std::cout << "Занимаемая площадь: " << Arr[i].area << "\n";
		std::cout << "\n";
	}
	return;
}

void create_new_file(int k)	// Формируем новый измененный файл
{
	if ((pf2 = fopen("new_test.dat", "wb")) == NULL) // Создаем двоичный файл для записи.
	{
		std::cout << "\nОшибка при открытии файла";
		exit(1);
	}
	for (int i = 0; i < k; i++)
	{
		fwrite(&Arr[i], sizeof(State), 1, pf); // Записываем в созданную структуру, но заменив значения
		if (ferror(pf)) exit(1);
	}
	fclose(pf);
	//считывание информации с файла
	if ((pf = fopen("new_test.dat", "rb")) == NULL) exit(1); // Открываем двоичный файл для чтения.
	int j = 0;
	while (!feof(pf2) && j < k)
	{
		fread(&Arr[j], sizeof(State), 1, pf2);
		j++;
	}
	fclose(pf2);
	return;
}
// нормально отсортироваться
void del(int k)
{
	int u;
	std::cin >> u; // Переменная забирает значение из метода main из коносоли.
	for (int i = 0; i < k; i++)
	{
		if (Arr[i].population <= u)
		{
			strcpy(Arr[i].name, Arr[i + 1].name);
			strcpy(Arr[i].capital, Arr[i + 1].capital);
			Arr[i].population = Arr[i + 1].population;
			Arr[i].area = Arr[i + 1].area;
		}
	}
	return;
}

void add(int k, int q)
{
	// q - номер элемента
	if (q > k)
	{
		std::cout << "\nТакого элемента в списке нет";
	}
	else
	{
		for (int i = q; i > k; i--) // Заменяем удаленный элемент
		{
			strcpy(Arr[i].name, Arr[i - 1].name);
			strcpy(Arr[i].capital, Arr[i - 1].capital);
			Arr[i].population = Arr[i - 1].population;
			Arr[i].area = Arr[i - 1].area;
		}
		std::cout << "Введите название государства: \n";
		std::cin >> Arr[q].name;
		std::cout << "Введите столицу: \n";
		std::cin >> Arr[q].capital;
		std::cout << "Введите численность населения: \n";
		std::cin >> Arr[q].population;
		std::cout << "Введите занимаемую площадь: \n";
		std::cin >> Arr[q].area;
		std::cout << "\n";
	}
	return;
}

