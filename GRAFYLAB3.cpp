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
	int liczbaWierzcholkow;
	list<int> *tablicaListKrawedzi;
public:

	Graph(int Var)
	{
		liczbaWierzcholkow = Var;
		tablicaListKrawedzi = new list<int>[liczbaWierzcholkow];
	}
	~Graph() {}

	void dodajKrawedz(int u, int v) { tablicaListKrawedzi[u].push_back(v); tablicaListKrawedzi[v].push_back(u); }
	void usunKrawedz(int u, int v);

	void wypiszCykl();
	void wypiszCyklHelper(int s);

	int przeszukajWglabDFS(int v, bool visited[]);

	bool wybierzNastepnaKrawedz(int u, int v);
	void WypelnijTabFalse(bool * krawedzieOdwiedzone);
};

//.cpp
void Graph::wypiszCykl()
{
	int u = 0;
	for (int i = 0; i < liczbaWierzcholkow; i++)
		if (tablicaListKrawedzi[i].size())
		{
			u = i; break;
		}

	cout << u;
	wypiszCyklHelper(u);
	cout << endl;
}

void Graph::wypiszCyklHelper(int u)
{
	list<int>::iterator i;
	for (i = tablicaListKrawedzi[u].begin(); i != tablicaListKrawedzi[u].end(); ++i)
	{
		int v = *i;

		if (v != -1 && wybierzNastepnaKrawedz(u, v))
		{
			cout << " " << v;
			usunKrawedz(u, v);
			wypiszCyklHelper(v);
		}
	}
}

bool Graph::wybierzNastepnaKrawedz(int u, int v)
{
	//if 1
	int count = 0;
	list<int>::iterator i;
	for (i = tablicaListKrawedzi[u].begin(); i != tablicaListKrawedzi[u].end(); ++i)
		if (*i != -1)
			count++;
	if (count == 1)
		return true;

	//if more
	bool *krawedzieOdwiedzone = new bool[liczbaWierzcholkow];

	WypelnijTabFalse(krawedzieOdwiedzone);
	int przedUsunieciemCounter = przeszukajWglabDFS(u, krawedzieOdwiedzone);

	usunKrawedz(u, v);

	WypelnijTabFalse(krawedzieOdwiedzone);
	int poUsunieciuCounter = przeszukajWglabDFS(u, krawedzieOdwiedzone);

	dodajKrawedz(u, v);

	return (przedUsunieciemCounter > poUsunieciuCounter) ? false : true;
}

void Graph::WypelnijTabFalse(bool * krawedzieOdwiedzone)
{
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		krawedzieOdwiedzone[i] = false;
	}
}

void Graph::usunKrawedz(int u, int v)
{
	list<int>::iterator iv = find(tablicaListKrawedzi[u].begin(), tablicaListKrawedzi[u].end(), v);
	*iv = -1;

	list<int>::iterator iu = find(tablicaListKrawedzi[v].begin(), tablicaListKrawedzi[v].end(), u);
	*iu = -1;
}

int Graph::przeszukajWglabDFS(int v, bool odwiedzone[])
{
	odwiedzone[v] = true;
	int count = 1;

	list<int>::iterator i;
	for (i = tablicaListKrawedzi[v].begin(); i != tablicaListKrawedzi[v].end(); ++i)
		if (*i != -1 && !odwiedzone[*i])
			count += przeszukajWglabDFS(*i, odwiedzone);

	return count;
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

		bool *krawedzieOdwiedzone = new bool[liczbaWierzcholkow];
		for (int i = 0; i < liczbaWierzcholkow; i++)
		{
			krawedzieOdwiedzone[i] = false;
		}
		krawedzieDodaneDoDrzewa = new list<int>[liczbaWierzcholkow];
		Graph graf(liczbaWierzcholkow);

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



    return 0;
}

