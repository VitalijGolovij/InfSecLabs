// Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<time.h>
#include<string>
#include<set>
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

struct Possabel
{
	int W = 0;
	int R = 0;

	friend bool operator< (const Possabel& l, const Possabel& r)
	{
		if (l.W > r.W && l.R < r.R)
			return true;
		if (l.W == r.W)
		{
			if (l.R < r.R)
				return true;
			else
				return false;
		}
		if (l.R == r.R)
		{
			if (l.W > r.W)
				return true;
			else
				return false;
		}
		return false;
	};
};

class CS
{
public:
	int N;
	int M;
	vector<vector<P>>* A;
	vector<Possabel>* LS;
	vector<Possabel>* LO;

	CS()
	{
		N = 3;
		M = 3;

		A = new vector<vector<P>>(N, vector<P>(M));

		A->at(0)[0] = P(0, 1); A->at(0)[1] = P(0, 1); A->at(0)[2] = P(1, 1);
		A->at(1)[0] = P(0, 1); A->at(1)[1] = P(1, 1); A->at(1)[2] = P(1, 0);
		A->at(2)[0] = P(1, 1); A->at(2)[1] = P(1, 0); A->at(2)[2] = P(1, 0);

		LS = new vector<Possabel>(N);
		LO = new vector<Possabel>(M);
	}

	CS(int n, int m)
	{
		N = n;
		M = m;

		A = new vector<vector<P>>(N, vector<P>(M));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				A->at(i)[j] = P(rand() % 2, rand() % 2);

		LS = new vector<Possabel>(N);
		LO = new vector<Possabel>(M);
	}

	void init_LS_and_LO()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				if (A->at(i)[j].w)
				{
					LO->at(j).W++;
				}
				if (A->at(i)[j].r)
				{
					LO->at(j).R++;
				}
				if (A->at(i)[j].w)
				{
					LS->at(i).W++;
				}
				if (A->at(i)[j].r)
				{
					LS->at(i).R++;
				}
			}



		vector<int> LOans;
		vector<int> LSans;
		set<Possabel> setLO = getCountUnique(*LO);
		set<Possabel> setLS = getCountUnique(*LS);

		if (!checkMatrix(*LO, setLO) || !checkMatrix(*LS, setLS))
			cout << " Данная матрица не валидна ";
		else
		{
			for (auto it : *LO) {
				LOans.push_back(distance(setLO.begin(), setLO.find(it)) + 1);
			}cout << endl;

			for (auto it : *LS) {
				LSans.push_back(setLS.size() - distance(setLS.begin(), setLS.find(it)));
			}
			cout << "Уровни доступа субъектов:" << endl;
			for (auto it : LSans) {
				cout << it << " ";
			}cout << endl;
			cout << "Уровни доступа объектов:" << endl;
			for (auto it : LOans) {
				cout << it << " ";
			}cout << endl;
		}
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
	}

	~CS()
	{
		delete A;
		delete LS;
		delete LO;
	}
private:

	set<Possabel> getCountUnique(vector<Possabel>& vect)
	{
		set<Possabel> temp;
		for (int i = 0; i < vect.size(); i++)
		{
			temp.insert(vect[i]);
		}
		return temp;
	}

	bool checkMatrix(vector<Possabel>& LO, set<Possabel>& setLO)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (A->at(i)[j].w == 0 && A->at(i)[j].r == 0)
					return false;

		for (auto it : LO)
		{
			bool flag = false;

			for (auto sit : setLO)
				if (it.W == sit.W && it.R == sit.R) flag = true;

			if (!flag)
				return false;
		}
		return true;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	CS myCS = CS();
	myCS.print();
	myCS.init_LS_and_LO();
}
