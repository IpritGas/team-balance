// Balance.cpp : Defines the entry point for the console application.
// © Vladimir Savich

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void quick_sort(vector<int>& vrating, vector<int>& vid, int left, int right);

int main()
{
	// Запрос на получение тестовых данных.
	string test;
	cout << "Enter the test name: " << flush;
	cin >> test;

	string players_file = "task_1_data\\test_" + test + "\\players.txt";
	string teams_file = "task_1_data\\test_" + test + "\\teams.txt";

	// Открытие исходных файлов.
	ifstream players(players_file);
	if (!players.is_open())
		cout << "Could not open players.txt file!" << endl;

	ifstream teams(teams_file);
	if (!players.is_open())
		cout << "Could not open teams.txt file!" << endl;

	// Считывание данных из исходных файлов.
	int id, rating;

	vector<int> vplayers_rating;
	cout << "Creating players rating vector..." << endl;
	while (!players.eof())
	{
		players >> id >> rating;
		vplayers_rating.insert(vplayers_rating.end(), rating);
	}
	vplayers_rating.pop_back(); //отбрасывание последнего значения
	cout << "Players rating vector is created." << endl;

	players.close();

	vector<int> vteams_id, vteams_rating;
	cout << "Creating teams id and teams rating vectors..." << endl;
	while (!teams.eof())
	{
		teams >> id;
		vteams_id.insert(vteams_id.end(), id);
		rating = 0;
		for (int p = 1; p <= 15; p++)
		{
			teams >> id;
			rating += vplayers_rating[id]; //вычисление рейтинга команды
		}
		vteams_rating.insert(vteams_rating.end(), rating);
	}
	vteams_id.pop_back();
	vteams_rating.pop_back();
	cout << "Teams id and teams rating vectors are created." << endl;

	teams.close();

	// Сортировка данных.
	cout << "Sorting teams id vector..." << endl;
	int last = vteams_id.size() - 1; //индекс последнего элемента вектора
	quick_sort(vteams_rating, vteams_id, 0, last);
	cout << "Teams id vector is sorted." << endl;

	// Запись сортированных данных в выходной файл.
	cout << "Creating teams balance file..." << endl;
	string pairs_file = "Savich_task_1_team_pairs\\test_" + test + "_pairs.txt";
	ofstream pairs(pairs_file);
	for (int z = 0; z < last; z++)
	{
		pairs << vteams_id[z] << ' ';
		if ((z % 2) != 0) //проверка четности
			pairs << endl;
	}
	pairs << vteams_id[last]; //запись последнего элемента
	pairs.close();
	cout << "Teams balance file is created." << endl;
	cout << "Shutting down..." << endl;

	return 0;
}

// Функция быстрой сортировки.
void quick_sort(vector<int>& vrating, vector<int>& vid, int left, int right)
{
	srand(time(0));

	int i = left, j = right; //индексы граничных элементов отрезка
	int temp;
	int range = right - left + 1; //ширина выборки для рандомизации
	int pivot = vrating[left + rand() % range]; //опорный элемент, случайный на отрезке

	// Разбиение.
	while (i <= j)
	{
		while (vrating[i] < pivot) //поиск элемента больше опорного слева
			i++;
		while (vrating[j] > pivot) //поиск элемента меньше опорного справа
			j--;
		if (i <= j)
		{
			// Перестановка элементов вектора рейтинга.
			temp = vrating[i];
			vrating[i] = vrating[j];
			vrating[j] = temp;

			// Перестановка элементов вектора идентификаторов.
			temp = vid[i];
			vid[i] = vid[j];
			vid[j] = temp;

			i++;
			j--;
		}
	}

	// Рекурсия.
	if (left < j)
		quick_sort(vrating, vid, left, j); //сортировка левого отрезка
	if (i < right)
		quick_sort(vrating, vid, i, right); //сортировка правого отрезка
}