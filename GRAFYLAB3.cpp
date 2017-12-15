// GRAFYLAB3.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
	bool odwiedzone[6];
	//freopen("ConsoleOutput.txt", "w", stdout);
	int testy;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	string powiazania;
	vector<pair<int, pair<int,int>>> vectorKrawedzi;


	cin >> testy;
	for (int i = 0; i < testy; i++)
	{
		cin >> powiazania;
		int indexPrzecinek = powiazania.find(",");
		//input n,m
		liczbaWierzcholkow = atoi(powiazania.substr(2, indexPrzecinek).c_str());
		liczbaKrawedzi = atoi(powiazania.substr(indexPrzecinek + 3, powiazania.size() - indexPrzecinek + 3).c_str());

		bool *krawedzieOdwiedzone = new bool[liczbaWierzcholkow];
		for (int i = 0; i < liczbaWierzcholkow; i++)
		{
			krawedzieOdwiedzone[i] = false;
		}

		for (int i = 0; i<liczbaKrawedzi; i++)
		{
			//input u,v
			int u;
			int v;
			int waga;

			string krawedzie;
			cin >> krawedzie;
			int indexPrzecinek = krawedzie.find(",");
			int indexNawias = krawedzie.find("}");

			u = atoi(krawedzie.substr(1, indexPrzecinek).c_str());

			int start = indexPrzecinek + 1;
			int length = indexNawias;
			string liczbaKrawedziStr = krawedzie.substr(start, length);
			v = atoi(liczbaKrawedziStr.c_str());

			start = indexNawias+1;
			length = krawedzie.size() - start;
			liczbaKrawedziStr = krawedzie.substr(start, length);
			waga = atoi(liczbaKrawedziStr.c_str());

			cout << "u " << u << endl;
			cout << "v " << v << endl;
			cout << "waga " << waga << endl;

			pair<int, int> wierzcholki(u, v);
			pair<int, pair<int, int>> pairInsert(waga, wierzcholki);
			vectorKrawedzi.push_back(pairInsert);
		}

		sort(vectorKrawedzi.begin(), vectorKrawedzi.end());
		for (vector<pair<int, pair<int, int>>>::iterator it = vectorKrawedzi.begin(); it != vectorKrawedzi.end(); ++it)
		{
			cout << it->first << endl;
		}
	}

	//wrzucic oba na gita

    return 0;
}

