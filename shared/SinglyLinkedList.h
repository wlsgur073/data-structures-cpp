#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// 연결 리스트 복사
		Node* current = list.first_;
		while(current)
		{
			this->PushBack(current->item);
			current = current->next;
		}
	}

	~SinglyLinkedList()
	{
		// JVM 쓸때는 이런거 신경 안써도 됬는데, 편했찌? 시부럴 C++ 쓸때는 까먹지 말자.
		Clear();
	}

	void Clear() // 모두 지워야(delete) 함.
	{
		while (first_)
			PopFront();
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		// size를 하나하나 세어서 반환
		Node* current = first_;
		while(current)
		{
			current = current->next;
			size++;
		}

		return size;
	}

	T Front()
	{
		assert(first_);

		return first_->item;
	}

	T Back()
	{
		assert(first_);

		Node* current = first_;
		while (current->next)
			current = current->next;

		return current->item;
	}

	Node* Find(T item)
	{
		// item이 동일한 노드 포인터 반환
		Node* current = first_;
		while(current)
		{
			if (current->item == item)
				return current;
			current = current->next;			
		}
		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		// 새로운 노드 만들기
		Node* new_node = new Node;
		new_node->item = item;

		// 연결 관계 정리
		new_node->next = node->next;
		node->next = new_node;
	}

	void Remove(Node* n)
	{
		// 첫 노드를 삭제하는 경우에는 prev를 찾을 수가 없어서 아래와 같이 처리
		if(first_ == n)
		{
			first_ = first_->next;
			delete n;
			return;
		}

		assert(first_);

		// 하나 앞의 노드를 찾아야 합니다.
		Node* current = first_;
		while(current)
		{
			if (current->next == n)
			{
				current->next = n->next;
				delete n;
				break;
			}
			current = current->next;
		}
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)
		// 새로운 노드 만들기
		Node* new_node = new Node; // O(1)
		new_node->item = item;

		// 연결 관계 정리
		new_node->next = first_;
		first_ = new_node;
	}

	void PushBack(T item)
	{
		if (first_)
		{
			Node* new_node = new Node;
			new_node->item = item;

			Node* current = first_;
			while (current->next)
				current = current->next;
			current->next = new_node; // new_node->next는 nullptr이므로 마지막 노드가 됨.
		}
		else
			PushFront(item);
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// 메모리 삭제
		Node* temp = first_;
		first_ = first_->next;
		delete temp;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}
		
		if (first_->next == nullptr)
		{
			delete first_;
			first_ = nullptr;
			return;
		}
		
		assert(first_);

		// 맨 뒤에서 하나 앞의 노드를 찾아야 함.
		// 메모리 삭제
		Node* second_last = first_;
		while (second_last->next->next) // while이 종료되면 next의 next가 null임을 확인
			second_last = second_last->next;
		
		Node* temp = second_last->next;
		second_last->next = second_last->next->next;
		delete temp;
	}

	// https://www.geeksforgeeks.org/reverse-a-linked-list/
	void Reverse()
	{
		Node* current = first_;
		Node* prev = nullptr;
		
		while (current)
		{
			Node* temp = prev;
			prev = current;
			current = current->next;
			prev->next = temp;
		}
		first_ = prev;
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " ";

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};