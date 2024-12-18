#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList() {}

	DoublyLinkedList(const DoublyLinkedList& list)
	{
		Node* current = list.first_;
		while (current)
		{
			this->PushBack(current->item);
			current = current->right;
		}
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
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

		Node* current = first_;
		while (current)
		{
			current = current->right;
			size++;
		}
		return size;
	}

	void Print()
	{
		// nullptr <- 3 -> nullptr
		// nullptr <- 3 <-> 4 -> nullptr
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			while (true)
			{
				cout << current->item << " ";
				if (!current->right) break;
				current = current->right;
			}
			cout << endl;

			cout << " Backward: ";
			while (true)
			{
				cout << current->item << " ";
				if (!current->left) break;
				current = current->left;
			}
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node* current = first_;
		while (current)
		{
			if (current->item == item)
				return current;
			current = current->right;
		}
		return current; // nullptr
	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty()) PushBack(item);
		else
		{
			Node* new_node = new Node;
			new_node->item = item;

			new_node->right = node->right;
			node->right = new_node;

			if (new_node->right)
				new_node->right->left = new_node;
			new_node->left = node;
		}
	}

	void PushFront(T item)
	{
		Node* new_node = new Node;
		new_node->item = item;

		new_node->right = first_;
		if (first_) first_->left = new_node;
		first_ = new_node;
	}

	void PushBack(T item)
	{

		if (first_)
		{
			Node* new_node = new Node;
			new_node->item = item;

			Node* current = first_;
			// while (current) // 해당 조건으로 반복문을 돌리면 current가 nullptr로 반환.
			while (current->right) // 해당 조건으로 반복문을 돌리면 current가 마지막 노드로 반환.
				current = current->right;
			
			new_node->left = current;
			current->right = new_node;
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
		first_ = first_->right;
		if (first_) first_->left = nullptr;
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

		// 맨 뒤에서 하나 앞의 노드를 찾아야 함.
		assert(first_);

		Node* current = first_;
		if (!current->right)
		{
			while (current->right->right)
				current = current->right;
			
			Node* temp = current->right;
			current->right = current->right->right; // nullptr

			delete temp;
		}
		else
		{
			delete first_;
			first_ = nullptr;
		}
	}

	void Reverse()
	{
		if (IsEmpty())
			return;
		else
		{
			Node* current = first_;
			while (current->right)
				current = current->right;

			first_ = current;

			while (current)
			{
				// left: [2] → nullptr (right로 변경)
				// right: nullptr → [2] (left로 변경)
				std::swap(current->left, current->right);
				current = current->right;
			}
		}
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
		while (current->right)
			current = current->right;
		return current->item;
	}

protected:
	Node* first_ = nullptr;
};