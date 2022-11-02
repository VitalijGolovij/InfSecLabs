// Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

struct P
{
    char r = '-';
    char w = '-';
    char o = '-';
    char x = '-';
};

vector<string> split(string str)
{
    vector<string> ans;
    string el = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str.at(i) != ' ')
            el += str.at(i);
        if (str.at(i) == ' ')
        {
            ans.push_back(el);
            el = "";
        }

    }
    ans.push_back(el);
    return ans;
}

P fillCell(string el)
{
    P p;
    if (el.find('r') != -1)
        p.r = 'r';
    if (el.find('w') != -1)
        p.w = 'w';
    if (el.find('o') != -1)
        p.o = 'o';
    if (el.find('x') != -1)
        p.x = 'x';
    return p;
}

void printP(P p)
{
    string ans = "";
    if(p.r=='r')
        ans += 'r';
    if (p.w == 'w')
        ans += 'w';
    if (p.o == 'o')
        ans += 'o';
    if (p.x == 'x')
        ans += 'x';
    cout << ans;
}

vector<vector<P>>* createA()
{
    ifstream in("envior.txt");
    string str;
    getline(in, str);
    int N = stoi(split(str)[0]);
    int M = stoi(split(str)[1]);
    vector<vector<P>>* A = new vector<vector<P>>(N, vector<P>(M));
    
    int i = 0;
    while(getline(in, str))
    {
        vector<string> str_list = split(str);
        for (int j = 0; j < M; j++)
            A->at(i)[j] = fillCell(str_list[j]);
        i++;
    }
    for (int it = 0; it < N; it++)
    {
        for (int j = 0; j < M; j++)
        {
            printP(A->at(it)[j]);
            cout << "\t";
        }
        cout << endl;
    }
    in.close();
    return A;
}

void ran_command(vector<vector<P>>* A)
{

}

int main()
{
    
    vector<vector<P>>* A = createA();
   
}

