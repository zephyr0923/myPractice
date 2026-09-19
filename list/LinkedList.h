#pragma once
#include <iostream>
using namespace std;

struct Node
{
	int Data;
	Node* Next;
};

class LinkedList
{
private:
	Node* H;
public:
	LinkedList();
	LinkedList(int a[], int n);
	~LinkedList();
	int length() const;
	bool Get(int i, Node* &p) const;
	bool Locate(int x, int &pos) const;
	bool Insert(int i, int x);
	bool Delete(int i);
	bool Empty() const;
	void PrintList() const;
};