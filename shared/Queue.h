#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>

template<typename T>
class Queue // Circular Queue
{
public:
	Queue(int capacity = 2)
	{
		assert(capacity > 0);

		capacity_ = capacity;
		queue_ = new T[capacity_];
		front_ = rear_ = 0;
	}

	~Queue()
	{
		if (queue_) delete[] queue_;
	}

	bool IsEmpty() const
	{
		return front_ == rear_;
	}

	bool IsFull() const
	{
		// 원형 큐에서 꽉 찼다의 기준
		return (rear_ + 1) % capacity_ == front_;
	}

	T& Front() const
	{
		assert(!IsEmpty());

		return queue_[(front_ + 1) % capacity_]; // 주의 + 1
	}

	T& Rear() const
	{
		assert(!IsEmpty());

		return queue_[rear_];
	}

	int Size() const
	{
		// 하나하나 세는 방법 보다는 경우를 따져서 바로 계산하는 것이 빠르다.
		if (front_ < rear_)
			return rear_ - front_;
		else
			return capacity_ - (front_ - rear_);
	}

	void Resize() 
	{
		// 이미 IsFull()에서 front_ == rear_가 성립이 안된다는 가정하에.
		// 경우를 나눠서 memcpy()로 블럭 단위로 복사하면 더 효율적.

		int new_capacity = capacity_ * 2;
		T* new_queue = new T[new_capacity];

		if (front_ < rear_) // front가 rear보다 앞에 있을 때
		{
			memcpy(new_queue, queue_ + front_, sizeof(T) * (rear_ - front_ + 1)); // front 다음부터 rear까지
		}
		else // front가 rear보다 뒤에 있을 때
		{
			int front_to_end = capacity_ - front_ - 1;
			int first_to_rear = rear_ + 1;

			memcpy(new_queue + front_to_end, queue_, sizeof(T) * first_to_rear); // 처음부터 rear까지
			memcpy(new_queue, queue_ + front_ + 1, sizeof(T) * front_to_end); // front 다음부터 끝까지
		}
		
		delete[] queue_;
		queue_ = new_queue;
		front_ = 0;
		rear_ = capacity_ - 1; // resize했다는건 현재 rear가 capacity - 1이라는 뜻
		capacity_ = new_capacity;
	}

	void Enqueue(const T& item) // 맨 뒤에 추가, Push()
	{
		if (IsFull())
			Resize();
		
		rear_ = (rear_ + 1) % capacity_; // 꽉 차면 다시 [0]으로 돌아가야 함
		queue_[rear_] = item;
	}

	void Dequeue() // 큐의 첫 요소 삭제, Pop()
	{
		assert(!IsEmpty());

		front_ = (front_ + 1) % capacity_;
	}

	void Print()
	{
		using namespace std;

		// front 다음부터 rear까지 출력
		 for (int i = (front_ + 1) % capacity_; i != (rear_ + 1) % capacity_; i = (i + 1) % capacity_)
		 	cout << queue_[i] << " ";
		 cout << endl;

		if (print_debug_)
			PrintDebug();
	}

	void PrintDebug()
	{
		using namespace std;

		cout << "Cap = " << capacity_ << ", Size = " << Size();
		cout << endl;

		// front와 rear 위치 표시
		for (int i = 0; i < capacity_; i++) {
			if (i == front_) cout << " F ";
			else if (i == rear_) cout << " R ";
			else cout << "   ";
		}
		cout << endl;

		// 0 based index
		for (int i = 0; i < capacity_; i++)
			cout << setw(2) << i << " ";
		cout << endl;

		if (front_ < rear_)
		{
			// front 앞 사용하지 않은 공간
			for (int i = 0; i < front_ + 1; i++)
				cout << " - ";

			// 저장된 내용물
			for (int i = front_ + 1; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear 뒤 사용하지 않은 공간
			for (int i = rear_ + 1; i < capacity_; i++)
				cout << " * ";

			cout << endl << endl;
		}
		else if (front_ > rear_)
		{
			// rear 이전에 저장된 내용물
			for (int i = 0; i <= rear_; i++)
				cout << setw(2) << queue_[i] << " ";

			// rear와 front 사이 사용하지 않은 공간
			for (int i = rear_ + 1; i <= front_; i++)
				cout << " * ";

			// front 뒤 내용물
			for (int i = front_ + 1; i < capacity_; i++)
				cout << setw(2) << queue_[i] << " ";

			cout << endl << endl;
		}
		else // 비었을 경우
		{
			for (int i = 0; i < capacity_; i++)
				cout << " - ";
			cout << endl << endl;
		}
	}

	void SetDebugFlag(bool flag)
	{
		print_debug_ = flag;
	}

protected: // 뒤에서 상속해서 사용
	T* queue_; // array for queue elements
	int front_ = 0; // 시작 인덱스보다 하나 작은 값
	int rear_ = 0; // 마지막 인덱스 (첫 값은 1에 추가)
	int capacity_; // 빈 칸을 하나 둬야 하기 때문에 필요 메모리는 최대 저장량 + 1
	bool print_debug_ = false;
};
