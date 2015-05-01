// Assignment 1 Games Dev.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <fstream>
#include <string.h>
using namespace std;

bool isFound = false;
const int SIZE = 10;
struct Coords
{
	int x;
	int y;
	int score;
	Coords* parent;
};

struct num
{
	char Array[SIZE];
};

void Program();

void SetStartEnd(string filename, Coords* begin, Coords* finish);

void CalculateScore(string filename, Coords* tmp, int heuristic, num cost[], Coords* current);

void NewNode(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList);

int Comparison(Coords* List[], int right, int left);

void Sorter(Coords* List[], int right, int left);

void Search(Coords* current, int heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, Coords* tmp);

Coords* NewNorth(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile);

Coords* NewEast(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile);

Coords* NewSouth(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile);

Coords* NewWest(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile);

int _tmain(int argc, _TCHAR* argv[])
{
	Program();
	system("pause");
	return 0; 
}
//the main function in the program to allow for the stl to dealocate memory before the memory leak detection
void Program()
{
	int heuristic = 0;
	const int SIZE = 10;
	const int Size = 50;
	bool isOpenEmpty = false;
	num cost[SIZE];
	string mapFile;
	string coordsFile;
	char answer;
	cout << "would you like map d or m" << endl;
	cin >> answer;
	if(answer == 'm')
	{
		mapFile = "..\\Debug\\mMap.txt";
		coordsFile = "..\\Debug\\mCoords.txt";
	}
	else if( answer == 'd')
	{
		mapFile = "..\\Debug\\dMap.txt";
		coordsFile = "..\\Debug\\dCoords.txt";
	}
	else
	{
		cout << "invaild chose" << endl;

	}
	
	ifstream infile;
	infile.open(mapFile);
	//inputs the cost for each square into a char array
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			infile >> cost[i].Array[j];
			if(infile.eof())
			{
			
			}
		}
	}
	
	infile.close();
	Coords* start = new (Coords);
	Coords* end = new (Coords);
	Coords* current = new (Coords);
	Coords* tmp = new (Coords);
	deque <Coords*> openList;
	deque <Coords*> closedList;
	start->score = 0;
	SetStartEnd(coordsFile, start, end);

	CalculateScore(mapFile, start, heuristic,  cost, current);
	
	openList.push_back(start);

	if(openList.empty())
	{
		cout << "Failure" << endl;
		return;
	}
	else
	{
		//main loop for the algorithm
		while(!openList.empty())
		{
			current = openList.front();
			cout <<"Current: "<< current->x << current->y << endl;
			cout <<endl;
			cout <<"ClosedList: " << endl;
			cout << endl;
			for(int i = 0; i < closedList.size(); i++)
			{
				cout << closedList[i]->x << closedList[i]->y << " ";
			}
			cout << endl;
			cout << "OpenList: " << endl;
			cout << endl;
			openList.pop_front();
			for(int i = 0; i < openList.size(); i++)
			{
				cout << openList[i]->x << openList[i]->y << " ";
			}
			cout << endl;
			
			if(current->x == end->x && current->y == end->y)
			{
				cout << "Goal Found" << endl;
				ofstream outfile;
				outfile.open("..//Debug//Outfile.txt");
				for(int i = 0; i < closedList.size(); i++)
				{
					outfile << closedList[i]->x << closedList[i]->y << " ";
				}
				delete(current, end, start);
				outfile.close();
				return;
			}
			closedList.push_back(current);

			tmp = NewNorth(current, heuristic, cost, closedList, openList, mapFile);
			if(isFound)
			{

			}
			else
			{
				if(tmp->score == NULL)
				{
				
				}
				else
				{
					openList.push_back(tmp);
				}
			}
			tmp = NewEast(current, heuristic, cost, closedList, openList, mapFile);
			if(isFound)
			{

			}
			else
			{
				if(tmp->score == NULL)
				{
				}
				else
				{
					openList.push_back(tmp);
				}
			}
			tmp = NewSouth(current, heuristic, cost, closedList, openList, mapFile);
			if(isFound)
			{

			}
			else
			{
				if(tmp->score == NULL)
				{
				
				}
				else
				{
					openList.push_back(tmp);
				}
			}

			tmp = NewWest(current, heuristic, cost, closedList, openList, mapFile);
			if(isFound)
			{

			}
			else
			{
				if(tmp->score == NULL)
				{
				
				}
				else
				{
					openList.push_back(tmp);
				}
			}

			int right = openList.size() -1;
			int left = 0;
			Coords* List[Size];
			for(int i = 0; i < Size; i++)
			{
				List[i] = NULL;
			}
			for(int i = 0; i < openList.size(); i++)
			{
				List[i] = openList[i];
			}
			Sorter(List, right, left);
			for(int i = 0; i < Size; i++)
			{
				if(List[i] == NULL)
				{
					
				}
				else
				{
					openList[i] = List[i];
				}
			}
		}
	if(openList.empty())
	{
		cout << "Failure" << endl;
		return;
	}
	}
	delete(current, end, start);
	
}
// this function sets the start and end nodes for the map
void SetStartEnd(string filename, Coords* begin, Coords* finish)
{
	ifstream infile;
	infile.open(filename);
	
	if(infile.is_open())
	{
		infile >> begin->x; 
		infile >> begin->y; 
		infile >> finish->x; 
		infile >> finish->y;
	}
	else
	{
		cout << "ERROR opening input file" << endl;
	}
	infile.close();
}
//this function calculates the score and sets the parent to current
//each time a new node is generated
void CalculateScore(string filename, Coords* tmp, int heuristic, num cost[], Coords* current)
{
	int tmpCost;
	if(cost[tmp->y].Array[tmp->x] == '0')
	{
		tmpCost = NULL;
	}
	else if(cost[tmp->y].Array[tmp->x] == '1')
	{
		tmpCost = 1;
	}
	else if(cost[tmp->y].Array[tmp->x] == '2')
	{
		tmpCost = 2;
	}
	else if(cost[tmp->y].Array[tmp->x] == '3')
	{
		tmpCost = 3;
	}
	else
	{
		tmpCost = NULL;
	}

	if(tmp->x < 0 || tmp->y < 0)
	{
		tmpCost = NULL;
	}
	if(!tmpCost == NULL)
	{
		tmp->parent = current;
		tmp->score = (heuristic + tmpCost) + current->score;

	}
	

	
}
//generates the new north node
Coords* NewNorth(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile)
{
	heuristic++;
	Coords* tmp = new Coords;
	tmp->x = current->x;
	tmp->y = current->y +1;
	CalculateScore("..\\Debug\\mMap.txt", tmp, heuristic, cost, current);
	Search(current, heuristic, cost, closedList, openList, tmp);
	return tmp;
}

Coords* NewEast(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile)
{
	Coords* tmp = new Coords;
	tmp->x = current->x +1;
	tmp->y = current->y;
	CalculateScore("..\\Debug\\mMap.txt", tmp, heuristic, cost, current);
	Search(current, heuristic, cost, closedList, openList, tmp);
	return tmp;
}

Coords* NewSouth(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile)
{
	Coords* tmp = new Coords;
	tmp->x = current->x;
	tmp->y = current->y -1;
	CalculateScore("..\\Debug\\mMap.txt", tmp, heuristic, cost, current);
	Search(current, heuristic, cost, closedList, openList, tmp);
	return tmp;
}

Coords* NewWest(Coords* current, int& heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, string mapFile)
{
	Coords* tmp = new Coords;
	tmp->x = current->x -1;
	tmp->y = current->y;
	CalculateScore("..\\Debug\\mMap.txt", tmp, heuristic, cost, current);
	Search(current, heuristic, cost, closedList, openList, tmp);
	return tmp;
}
//comparison function that helps sorting the openlist
int Comparison(Coords* List[], int right, int left)
{
	int pivotValue = List[right]->score; 
	int stackTop = left; 
	
	for( int i = left; i < right ; i++)
	{
		if ( List[i]->score <= pivotValue )
		{
			swap(List[i], List[stackTop]);
			stackTop++;
		}
	}

	swap( List[stackTop], List[right] );
	return stackTop;
}
//partition function for sorting the openlist
void Sorter(Coords* List[], int right, int left)
{
	if ( right > left )
	{
		int pivot = Comparison(List, right, left);

		Sorter(List, pivot - 1,left );
		Sorter(List, right,pivot + 1 );
	}
}
// for searching the open and closed list
void Search(Coords* current, int heuristic, num cost[], deque <Coords*> closedList, deque <Coords*> openList, Coords* tmp)
{
	isFound = false;
	deque <Coords*>::iterator it;
	if(!closedList.empty())
	{
		for(it = closedList.begin(); it != closedList.end(); it++)
		{
			if((*it)->x == tmp->x && (*it)->y == tmp->y)
			{
				isFound = true;
				return;
			}
		}
		for(it = openList.begin(); it != openList.end(); it++)
		{
			if((*it)->x == tmp->x && (*it)->y == tmp->y)
			{
				isFound = true;
				return;
			}
		}
	}
	else
	{
		cout << "Closed List is empty" << endl;
	
	}
	if(!isFound)
	{
		if(cost[tmp->y].Array[tmp->x]  == 30)
		{
			isFound = true;	
		}
		else
		{
			isFound = false;
			return;
		}
	}
	else
	{

	}
}