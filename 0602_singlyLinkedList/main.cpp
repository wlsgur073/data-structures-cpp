#include <iostream>

#include "../shared/SinglyLinkedList.h"

using namespace std;

int main()
{
	SinglyLinkedList<int> list;

	list.SetPrintDebug(true);

	list.PushFront(3);
	list.PushBack(4);
	list.PushFront(2);
	list.PushFront(1);
	list.PushBack(5);

	// list.Print();

	// copy constructor
	{
		SinglyLinkedList<int> list2 = list; // 새로 노드를 만들고 노드끼리의 연결고리고 만들어야 함.
		// list2.SetPrintDebug(true);
		// list2.Print();
	}

	// list.Reverse(); // 스택을 만들다거나, 임시 배열을 만들어서 뒤집는 방법이 아님.
	// list.Print();

	// SinglyLinkedList<int>::Node* temp = list.Find(3);
	// list.InsertBack(temp, 1000); // find한 노드 뒤에다가 새로운 노드를 넣는다. linkedList는 insert 한번만 하기에 O(1)
	// list.Print();

	// list.InsertBack(temp, 50);
	// list.Print();
	// list.Remove(temp);
	list.Print();

	// PopFront()/Back() 테스트
	for (int i = 0; i < list.Size(); i++)
	{
		list.PopFront();
		list.Print();

		list.PopBack();
		list.Print();

		if (!list.IsEmpty())
			cout << list.Front() << " " << list.Back() << endl;
	}

	// Edge case 테스트 주의
	// 맨 앞이나 맨 뒤에서 어떻게 해야할지. 노드에 비어있다면?

	return 0;
}
