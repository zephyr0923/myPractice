#include "SeqList.h"

SeqList::SeqList() :length(0)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		this->Data[i] = 0;
	}
}

SeqList::SeqList(int pData[], int n)
{
	if (n > MAXSIZE)
	{
		cout << "元素数量超过最大容量！" << endl;
		n = MAXSIZE;
	}

	this->length = n;
	for (int i = 0; i < n; i++)
	{
		this->Data[i] = pData[i];
	}
}

SeqList::~SeqList()
{
	this->length = 0;
}

int SeqList::Length() const
{
	return this->length;
}

bool SeqList::Get(int i, int &val) const
{
	if (i < 0 || i >= this->length)
	{
		cout << "下标越界" << endl;
		return false;
	}
	val = this->Data[i];
	return true;
}

bool SeqList::Locate(int x, int& pos) const
{
	for (int i = 0; i < this->length; i++)
	{
		if (this->Data[i] == x)
		{
			pos = i;
			return true;
		}
	}
	pos = -1;
	return false;
}

bool SeqList::Insert(int i, int x)
{
	if (this->length == MAXSIZE)
	{
		cout << "已满" << endl;
		return false;
	}
	if (i < 0 || i > this->length)
	{
		cout << "下标越界" << endl;
		return false;
	}
	for (int j = this->length - 1; j >= i; j--)
	{
		this->Data[j + 1] = this->Data[j];
	}
	this->Data[i] = x;
	this->length++;
	return true;
}

bool SeqList::Delete(int i, int &e)
{
	if (i < 0 || i >= this->length)
	{
		cout << "下标越界" << endl;
		return false;
	}
	e = this->Data[i];
	for (int j = i; j < this->length - 1; j++)
	{
		this->Data[j] = this->Data[j + 1];
	}
	this->length--;
	return true;
}

bool SeqList::Empty() const
{
	return this->length == 0;
}

void SeqList::PrintList() const
{
	if (!Empty())
	{
		for (int i = 0; i < this->length; i++)
		{
			cout << this->Data[i] << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "顺序表为空" << endl;
	}
}