#include "LinkedList.h"

LinkedList::LinkedList()
{
	this->H = new Node;
	this->H->Next = nullptr;
}

LinkedList::LinkedList(int a[], int n)
{
	this->H = new Node;
	Node* r = this->H;
	for (int i = 0; i < n; i++)
	{
		Node* s = new Node;
		s->Data = a[i];
		s->Next = nullptr;
		r->Next = s;
		r = s;
	}
}

LinkedList::~LinkedList()
{
	Node* p = H;
	while (p != nullptr)
	{
		Node* q = p;
		p = p->Next;
		delete q;
	}
	H = nullptr;
}

int LinkedList::length() const
{
	int count = 0;
	Node* p = this->H->Next;
	while (p != nullptr)
	{
		count++;
		p = p->Next;
	}
	return count;
}

bool LinkedList::Get(int i, Node*& p) const
{
	p = nullptr;
	if (i <= 0)
	{
		return false;
	}
	Node* r = this->H;
	for (int j = 0; j < i; j++)
	{
		r = r->Next;
		if (r == nullptr)
		{
			return false;
		}
	}
	p = r;
	return true;
}

bool LinkedList::Locate(int x, int& pos) const
{
	pos = -1;
	Node* r = this->H;
	int count = 0;
	while (r->Next != nullptr)
	{
		count++;
		if (r->Next->Data == x)
		{
			pos = count;
			return true;
		}
		r = r->Next;
	}
	return false;
}

bool LinkedList::Insert(int i, int x)
{
	if (i == 1)
	{
		Node* r = new Node;
		r->Data = x;
		r->Next = this->H->Next;
		this->H->Next = r;
		return true;
	}
	Node* p = nullptr;
	if (Get(i - 1, p))
	{
		Node* r = new Node;
		r->Data = x;
		r->Next = p->Next;
		p->Next = r;
		return true;
	}
	return false;
}

bool LinkedList::Delete(int i)
{
	if (i == 1)
	{
		Node* p = this->H->Next;
		this->H->Next = this->H->Next->Next;
		delete p;
		p = nullptr;
		return true;
	}
	Node* pre = nullptr;
	if (Get(i - 1, pre))
	{
		Node* p = pre->Next;
		pre->Next = pre->Next->Next;
		delete p;
		p = nullptr;
		return true;
	}
	return false;
}

bool LinkedList::Empty() const
{
	return H->Next == nullptr;
}

void LinkedList::PrintList() const
{
	Node* p = H->Next;
	while (p != nullptr)
	{
		cout << p->Data << " ";
		p = p->Next;
	}
	cout << endl;
}