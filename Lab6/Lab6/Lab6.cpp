// Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<time.h>
#include<string>
using namespace std;

class P
{
public:
	bool w = false;
	bool r = false;
	P()
	{

	}
	P(int r1, int r2)
	{
		if (r1 == 1)
			w = true;

		if (r2 == 1)
			r = true;
	}
};

class CS
{
public:
	int N;
	int M;
	vector<vector<P>>* A;
	vector<int>* LS;
	vector<int>* LO;

	CS()
	{
		N = 3;
		M = 3;

		A = new vector<vector<P>>(N, vector<P>(M));

		A->at(0)[0] = P(0, 1); A->at(0)[1] = P(0, 1); A->at(0)[2] = P(1, 1);
		A->at(1)[0] = P(0, 1); A->at(1)[1] = P(1, 1); A->at(1)[2] = P(1, 0);
		A->at(2)[0] = P(1, 1); A->at(2)[1] = P(1, 0); A->at(2)[2] = P(1, 0);

		LS = new vector<int>{ 1,2,3 };
		LO = new vector<int>{ 3,2,1 };
	}

	CS(int n, int m)
	{
		N = n;
		M = m;

		A = new vector<vector<P>>(N, vector<P>(M));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				A->at(i)[j] = P(rand() % 2, rand() % 2);

		LS = new vector<int>(N);
		LO = new vector<int>(M);

		for (int i = 0; i < N; i++) LS->at(i) = rand() % 4 + 1;
		for (int i = 0; i < M; i++) LO->at(i) = rand() % 4 + 1;
	}

	void print()
	{
		cout << "Матрица доступа:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
				cout << "(" << A->at(i)[j].w << "," << A->at(i)[j].r << ")" << "\t";
			cout << endl;
		}
		cout << "Матрицы уровня доступа субъектов:" << endl;

		for (int i = 0; i < N; i++)
			cout << LS->at(i) << " ";
		cout << endl;

		cout << "Матрицы уровня доступа объектов:" << endl;

		for (int i = 0; i < M; i++)
			cout << LO->at(i) << " ";
		cout << endl;
	}

	~CS()
	{
		delete A;
		delete LS;
		delete LO;
	}
private:


};

bool check_system(CS& myCS)
{
	for (int i = 0; i < myCS.N; i++)
		for (int j = 0; j < myCS.M; j++)
		{
			if (myCS.A->at(i)[j].w && myCS.LS->at(i) < myCS.LO->at(j))
			{
				cout << "Ошибка: " << "A[" + to_string(i) + "][" + to_string(j) + "]" << endl;
				return false;
			}
			if (myCS.A->at(i)[j].r && myCS.LO->at(j) < myCS.LS->at(i))
			{
				cout << "Ошибка: " << "A[" + to_string(i) + "][" + to_string(j) + "]" << endl;
				return false;
			}
			if (myCS.A->at(i)[j].w == false && myCS.LS->at(i) >= myCS.LO->at(j))
			{
				cout << "Ошибка: " << "A[" + to_string(i) + "][" + to_string(j) + "]" << endl;
				return false;
			}
			if (myCS.A->at(i)[j].r == false && myCS.LO->at(j) >= myCS.LS->at(i))
			{
				cout << "Ошибка: " << "A[" + to_string(i) + "][" + to_string(j) + "]" << endl;
				return false;
			}
		}
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	CS myCS = CS(5, 10);
	myCS.print();

	CS myCS_test;
	if (check_system(myCS_test))
		cout << "Система безопасна";
	else
		cout << "Система не безопасна";
}
