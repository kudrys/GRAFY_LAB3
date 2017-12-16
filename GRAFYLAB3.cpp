// GRAFYLAB3.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class Graph
{
	
public:

	int liczbaWierzcholkow;
	list<int> *tablicaListKrawedzi;
	
	Graph(int Var)
	{
		liczbaWierzcholkow = Var;
		tablicaListKrawedzi = new list<int>[liczbaWierzcholkow];
	}
	~Graph() {}

	void dodajKrawedz(int u, int v) { tablicaListKrawedzi[u].push_back(v); tablicaListKrawedzi[v].push_back(u); }

	bool sprawdzCzyCykl(int start, bool odwiedzone[], int meta);

	bool czyMoznaDodacKrawedz(int u, int v);
	void WypelnijTabFalse(bool * krawedzieOdwiedzone);
};


bool Graph::czyMoznaDodacKrawedz(int start, int meta)
{

	bool *krawedzieOdwiedzone = new bool[liczbaWierzcholkow];

	WypelnijTabFalse(krawedzieOdwiedzone);
	return !sprawdzCzyCykl(start, krawedzieOdwiedzone, meta);

}

void Graph::WypelnijTabFalse(bool * krawedzieOdwiedzone)
{
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		krawedzieOdwiedzone[i] = false;
	}
}


bool Graph::sprawdzCzyCykl(int start, bool odwiedzone[], int meta)
{
	odwiedzone[start] = true;
	bool cykl = false;

	list<int>::iterator i;
	for (i = tablicaListKrawedzi[start].begin(); i != tablicaListKrawedzi[start].end(); ++i)
		if (*i != -1 && !odwiedzone[*i]) {
			cykl = sprawdzCzyCykl(*i, odwiedzone, meta);
			if (cykl)
				return cykl;
		}
	return cykl;
}

int main()
{
	bool odwiedzone[6];
	//freopen("ConsoleOutput.txt", "w", stdout);
	int testy;
	int liczbaWierzcholkow;
	int liczbaKrawedzi;
	string powiazania;
	vector<pair<int, pair<int,int>>> vectorKrawedzi;
	list<int> *krawedzieDodaneDoDrzewa;
	
	cin >> testy;
	for (int i = 0; i < testy; i++)
	{
		cin >> powiazania;
		int indexPrzecinek = powiazania.find(",");
		//input n,m
		liczbaWierzcholkow = atoi(powiazania.substr(2, indexPrzecinek).c_str());
		liczbaKrawedzi = atoi(powiazania.substr(indexPrzecinek + 3, powiazania.size() - indexPrzecinek + 3).c_str());

		bool *wierzcholkiOdwiedzone = new bool[liczbaWierzcholkow];
		for (int i = 0; i < liczbaWierzcholkow; i++)
		{
			wierzcholkiOdwiedzone[i] = false;
		}
		krawedzieDodaneDoDrzewa = new list<int>[liczbaWierzcholkow];
		Graph drzewo(liczbaWierzcholkow);

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

			pair<int, int> wierzcholki(u, v);
			pair<int, pair<int, int>> pairInsert(waga, wierzcholki);
			vectorKrawedzi.push_back(pairInsert);
		}

		sort(vectorKrawedzi.begin(), vectorKrawedzi.end());

		int counterDodanychKrawedzi = 1; //zawsze o 1 mniejszy niz liczbawierzchlkow
		int sumaWagKrawedzi = 0;

		for (vector<pair<int, pair<int, int>>>::iterator it = vectorKrawedzi.begin(); it != vectorKrawedzi.end(); ++it)
		{
			int start = it->second.first;
			int meta = it->second.second;
			int waga = it->first;

			if (drzewo.czyMoznaDodacKrawedz(start, meta)) {
				drzewo.dodajKrawedz(start, meta);
				counterDodanychKrawedzi++;
				sumaWagKrawedzi += waga;

				cout << "start: " << start << " meta: " <<meta<< " waga: " << waga << endl;


			}
			for (int i = 0; i < liczbaWierzcholkow; i++) {
				list<int>x = drzewo.tablicaListKrawedzi[i];
				cout << "i: " << i << endl;
				for (list<int>::iterator iterator = x.begin(); iterator != x.end(); ++iterator) {

					cout<< "  " << *iterator<< endl;
					
				}
			}

			if (counterDodanychKrawedzi == liczbaWierzcholkow)
				break;
		}
		cout << sumaWagKrawedzi<<endl;
	}

    return 0;
}

