#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		// 연산 우선순위 조심
		Base::queue_[Base::front_] = item;
		Base::front_ = (Base::front_ - 1 + Base::capacity_) % Base::capacity_; // front_를 왼쪽으로 한칸 이동
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());

		Base::rear_ = (Base::rear_ - 1 + Base::capacity_) % Base::capacity_; // rear_를 왼쪽으로 한칸 이동
	}

private:
	// Queue와 동일
};
