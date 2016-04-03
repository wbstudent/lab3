// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sortBySex(Slav *, int);//zadanie na 5
void printAnswer();//drukuje odpowiedź do zadania na 5.5

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sortBySex(slavs, n);
	printAnswer();

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand(time(NULL));
	vectorOfSlavs.push_back(&slavs[0]);
	for(int i = 1; i < n; i++)
	{
		vectorOfSlavs.insert (vectorOfSlavs.begin()	+ rand()%(vectorOfSlavs.size()+1) ,&slavs[i]);
	}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector <Slav *>::iterator it_vec_slav = vectorOfSlavs.begin();
	for(;it_vec_slav != vectorOfSlavs.end(); ++it_vec_slav)	
		cout << (*it_vec_slav)->description() << endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(int i = n-1; i >= 0; i--)
	{
		setOfSlavs.insert(vectorOfSlavs[i]);
		vectorOfSlavs.pop_back();
	}

	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set <Slav *>::iterator it_set_slav = setOfSlavs.begin();
	while(it_set_slav != setOfSlavs.end())
	{
		mapOfSlavs[*it_set_slav] = *(it_set_slav = (setOfSlavs.erase(it_set_slav)));//przypisz jako klucz obecny iterator,(to, na co wskazuje)
																					// następnie przypisz do iteratora kolejny, zwracany przez funkcję erase
																					// a to, na co wskazuje, przypisz jako wartość
		it_set_slav = setOfSlavs.erase(it_set_slav);//czyści ze zbioru to, na co obecnie wskazuje iterator, przesuwa iterator o jeden dalej
	} 

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	map <Slav *, Slav *>::iterator it_map_slav = mapOfSlavs.begin();
	for(; it_map_slav != mapOfSlavs.end(); ++it_map_slav)
		cout << (it_map_slav->first)->description() << " : " << (it_map_slav->second)->description() << endl;

	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i  = 0; i < n; i++)
		queueOfSlavs.push(&slavs[i]);

	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while(!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}
	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	while(!stackOfSlavs.empty())
	{
		cout << (stackOfSlavs.top())->description() << endl;
		stackOfSlavs.pop();
	}
	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}

void sortBySex(Slav * slavs, int n)
{
	//Zadanie na 5
	map <sex, vector<Slav *> > mapBySex;
	for(int i=0; i < n; i++)
	{
		if(slavs[i].sex_ret() == male)
			mapBySex[male].push_back(&slavs[i]);
		else
			mapBySex[female].push_back(&slavs[i]);
	}

	vector <Slav *>::iterator it_vec_slav = mapBySex[male].begin();
	cout << endl <<"Mężczyźni: " << endl;
	it_vec_slav = mapBySex[male].begin();
	for(;it_vec_slav != mapBySex[male].end(); ++it_vec_slav)	
		cout << (*it_vec_slav)->description() << endl;

	cout << endl << "Kobiety: " << endl;
	it_vec_slav = mapBySex[female].begin();
	for(;it_vec_slav != mapBySex[female].end(); ++it_vec_slav)	
		cout << (*it_vec_slav)->description() << endl;
}

void printAnswer()
{
	cout << endl << "Odpowiedź do zadania na 5.5:" << endl;
	cout << "W tej linijce zmiennej amountOfNames przypisywana jest (tylko raz, jako że na początku jest 'static')"
			"ilość imion wczytanych Słowian. W nawiasie wywoływana jest funkcja inizjalizująca 'init()', a następnie"
			"amountOfNames przyjmuje wartość równą 'names.size()'. Ten proces nazywa się leniwym inicjowaniem" << endl;
}