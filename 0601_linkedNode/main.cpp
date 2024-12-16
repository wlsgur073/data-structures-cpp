#include <iostream>

using namespace std;

struct Node
{
	int item = 0;	  // <- 큰 데이터도 가능
	Node* next = nullptr;

	friend ostream& operator<<(ostream& os, const Node& n)
	{
		cout << "[" << &n << ", " << n.item << ", " << n.next << "]" << flush;
		return os;
	}
};

void RecurPrint(Node* node)
{
	if (node == nullptr)
		return;

	cout << *node << endl;
	RecurPrint(node->next);
	// cout << *node << endl; // stack에 쌓여있다가 pop되니까 역순으로 출력됨
}

void IterPrint(Node* node)
{
	while (node != nullptr)
	{
		cout << *node << endl;
		node = node->next;
	}
}

int main()
{
	// ListArray와 비교

	Node* first = nullptr;
	first = new Node;
	first->item = 1;
	first->next = nullptr;

	Node* second = nullptr;
	second = new Node;
	second->item = 2;
	second->next = nullptr;

	Node* third = nullptr;
	third = new Node;
	third->item = 3;
	third->next = nullptr;

	Node* fourth = nullptr;
	fourth = new Node;
	fourth->item = 4;
	fourth->next = nullptr;

	Node* fifth = nullptr;
	fifth = new Node;
	fifth->item = 5;
	fifth->next = nullptr;

	// 계속 추가 가능
	cout << *first << endl;
	cout << *second << endl;
	cout << *third << endl;
	cout << *fourth << endl;
	cout << *fifth << endl;
	cout << endl;

	// 배열로 관리할수도 있음. 근데 우리는 배열을 피하기 위해서 링크드 리스트를 사용할거임.
	// Node* nodes[] = { first, second, third, fourth, fifth };
	// cout << nodes[0] << endl;
	// 노드도 항상 첫 번째 주소는 가지고 있어야 함. 첫 번째 주소를 잃어버리면 모든 데이터를 잃어버림.

	// 연결 관계 만들어 주기
	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fifth;
	fifth->next = nullptr; // 마지막

	cout << *(first) << endl;
	cout << *(first->next) << endl;
	cout << *(first->next->next) << endl;
	cout << *(first->next->next->next) << endl;
	cout << *(first->next->next->next->next) << endl;
	// cout << *(first->next->next->next->next->next) << endl; // 마지막은 `nullptr`라서 NPE 발생
	cout << endl;

	// 임시 변수 사용
	{
		Node* current = first;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		cout << *current << endl;

		current = current->next;
		// cout << *current << endl; // 마지막은 `nullptr`라서 NPE 발생
		cout << endl;
	}

	// 재귀 호출 이용
	RecurPrint(first);
	cout << endl;

	// 반복문 이용
	IterPrint(first);
	cout << endl;

	// 데이터 삭제
	Node* current = first;
	while(current != nullptr)
	{
		Node* temp = current;
		cout << "Delete: " << *temp << endl;
		current = current->next;
		delete temp;
	}

	return 0;
}
