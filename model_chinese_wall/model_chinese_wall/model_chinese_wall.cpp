// model_chinese_wall.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;

struct System_A
{
	vector<Permission> vect_A;
	set<int> set_del_subj;
	int count_subj;
	int count_obj;
};

struct Permission
{
	Permission()
	{

	}
	Permission(string p, int i, int j)
	{
		perm = p;
		sub = i;
		obj = j;
	}
	string perm;
	int sub;
	int obj;
};

System_A createA(int N, int M)
{
	vector<vector<Permission>>* A = new vector<vector<Permission>>(N, vector<Permission>(M));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			int r = rand() % 4;
			switch (r)
			{
			case 0:
			{
				Permission perm("-",i,j);
				A->at(i)[j] = perm;
				break;
			}
			case 1:
			{
				Permission perm("r", i, j);
				A->at(i)[j] = perm;
				break;
			}
			case 2:
			{
				Permission perm("w", i, j);
				A->at(i)[j] = perm;
				break;
			}
			case 3:
			{
				Permission perm("rw", i, j);
				A->at(i)[j] = perm;
				break;
			}
			default:
				break;
			}
		}

	cout << "Полученная матрица:" << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << A->at(i)[j].perm << "\t";
		cout << endl;
	}

	System_A myA;
	myA.count_subj = N;
	myA.count_obj = M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (A->at(i)[j].perm != "-")
			{
				myA.vect_A.push_back(A->at(i)[j]);
			}

	delete A;
	return myA;
}

void changeP(System_A& A,int i, int j)
{
	if (i<0 || i>A.count_subj || j<0 || j>A.count_obj) {
		cout << "Такой ячейки не существует" << endl;
		return;
	}

	for (auto it : A.set_del_subj)
		if (i == it && j == it)
			cout << "Такой ячейки не существует" << endl;

	for(auto it: A.vect_A)
		if (i == it.sub && j == it.obj)
		{
			cout << "Право доступа субъекта " + to_string(i) + " на объект " + to_string(j) + ": " + it.perm << endl;
			cout << "Введите новое правод доступа:";
			cin >> it.perm;
			cout << "Право доступа успешно изменено";
			return;
		}

	Permission per("-", i, j);
	cout << "Право доступа субъекта " + to_string(i) + " на объект " + to_string(j) + ": " + per.perm << endl;
	cout << "Введите новое правод доступа:";
	cin >> per.perm;
	cout << "Право доступа успешно изменено";
	A.vect_A.push_back(per);
}

void addSubj(System_A &A)
{
	A.count_subj++;
	if (A.set_del_subj.size() != 0)
	{
		cout << "Субъект добавлен под номером " + to_string(*A.set_del_subj.begin());
		A.set_del_subj.erase(A.set_del_subj.begin());
	}
	else
		cout << "Субъект добавлен под номером " + to_string(A.count_subj);
}

void delSubj(System_A& A, int i)
{
	if (i<0 || i>A.count_subj)
	{
		cout << "Такого субъекта не существует" << endl;
		return;
	}
	auto pos = A.set_del_subj.find(i);
	if (pos != A.set_del_subj.end())
	{
		cout << "Такой субъект уже был удален" << endl;
		return;
	}
	else
	{
		A.set_del_subj.insert(i);
		for (auto it = A.vect_A.begin(); it!=A.vect_A.end();++it)
			if ((*it).sub == i)
			{
				A.vect_A.erase(it);
			}
		A.count_subj--;
		cout << "Субъект " + to_string(i) + " успешно удален" << endl;
	}
}

void percentage_occupancy(System_A& A)
{
	int count_cells = A.count_subj * A.count_obj;
	cout << "Процент заполнености матрицы: " << int(A.vect_A.size() / count_cells * 100);
}

int main()
{
	srand(time(0));
	System_A A;

	setlocale(LC_ALL, "ru");
	bool end = false;
	while (!end)
	{
		int choice;
		
		cout << "1. Создать матрицу" << endl;
		cout << "2. Изменить право доступа" << endl;
		cout << "3. Добавить субъекта" << endl;
		cout << "4. Удалить субъекта" << endl;
		cout << "5. Процент заполнености матрицы" << endl;
		cout << "9. Выход" << endl;
		cout << "Введите номер действия:" << endl;

		cin >> choice;

		switch (choice)
		{
		case 9:
		{
			end = true;
			break;
		}
		case 1:
		{
			cout << "Введите N M" << endl;
			int N, M;
			cin >> N >> M;
			createA(N, M);
			break;
		}
		case 2:
		{
			cout << "Введите номер субъекта и объекта" << endl;
			int i, j;
			cin >> i >> j;
			changeP(A, i, j);
			break;
		}
		case 3:
		{
			addSubj(A);
		}
		case 4:
		{

		}
		default:
			break;
		}
		
	}
	cout << "Программа завершена";
}

