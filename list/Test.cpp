#include <iostream>
using namespace std;
#include "SeqList.h"
#include "LinkedList.h"

int main()
{
    /*
    int arr[] = { 11,22,33,44 };
    SeqList L(arr, 4);
    cout << "初始表：";
    L.PrintList();

    L.Insert(2, 99);
    cout << "下标2插入99：";
    L.PrintList();

    int e;
    L.Delete(1, e);
    cout << "删除下标1，删掉元素：" << e << endl;
    cout << "删除后：";
    L.PrintList();

    int pos;
    if (L.Locate(99, pos))
    {
        cout << "找到99，下标：" << pos << endl;
    }

    int val;
    L.Get(2, val);
    cout << "下标2元素：" << val << endl;
    */

    // 1. 用数组初始化链表：10 20 30 40
    int arr[] = { 10,20,30,40 };
    LinkedList list(arr, 4);
    cout << "【初始化后链表】:";
    list.PrintList();
    cout << "链表长度：" << list.length() << endl;
    cout << "是否为空？" << (list.Empty() ? "是" : "否") << endl << endl;

    // 2. 测试Get 获取第2个节点
    Node* nd = nullptr;
    if (list.Get(2, nd))
    {
        cout << "Get(2) 获取节点数据：" << nd->Data << endl << endl;
    }

    //3. 测试Locate查找值30的位置
    int pos = -1;
    if (list.Locate(30, pos))
    {
        cout << "Locate(30)，位置pos = " << pos << endl << endl;
    }

    //4. 在第2个位置插入99
    cout << "在位置2插入99:";
    list.Insert(2, 99);
    list.PrintList();
    cout << "长度：" << list.length() << endl << endl;

    //5. 删除第3号节点
    cout << "删除位置3:";
    list.Delete(3);
    list.PrintList();
    cout << "长度：" << list.length() << endl << endl;

    //6. 头插 5
    cout << "在位置1插入5:";
    list.Insert(1, 5);
    list.PrintList();
    cout << "长度：" << list.length() << endl << endl;

    //7. 删除头结点后面第一个元素（i=1）
    cout << "删除位置1:";
    list.Delete(1);
    list.PrintList();
    cout << "长度：" << list.length() << endl << endl;

    //8. 测试查找不存在元素
    pos = -1;
    if (list.Locate(999, pos))
        cout << "找到999" << endl;
    else
        cout << "Locate(999)：找不到，pos=" << pos << endl;
    return 0;
}
