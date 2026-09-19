#pragma once
#include <iostream>
using namespace std;
#define MAXSIZE 100

class SeqList
{
private:
	int Data[MAXSIZE];
	int length;

public:
	SeqList();
	SeqList(int pData[], int n);
	~SeqList();
	int Length() const;
	bool Get(int i, int &val) const;
	bool Locate(int x, int &pos) const;
	bool Insert(int i, int x);
	bool Delete(int i, int& e);
	bool Empty() const;
	void PrintList() const;

};
