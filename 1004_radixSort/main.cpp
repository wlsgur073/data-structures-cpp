#include <iostream>
#include "../shared/Queue.h"

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int GetMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);

	Queue<int> queues[10]; // 미리 10개의 큐를 만들어 놓는다. // FIFO이기에 원래 있던 숫자에 변화가 없어, stable sort

	int m = GetMax(arr, n); // 가장 큰 자리수를 찾기 위해서

	cout << "Max = " << m << endl;
	cout << "========================" << endl;

	for (int exp = 1; m / exp > 0; exp *= 10) 
	{
		for (int i = 0; i < n; i++)
			queues[(arr[i] / exp) % 10].Enqueue(arr[i]); // 자리수 기준으로 큐 분류.
		
		int idx = 0;
		for (int i = 0; i < 10; i++)
		{
			while (!queues[i].IsEmpty())
			{
				arr[idx] = queues[i].Front();
				queues[i].Dequeue();
				idx++;
			}
		}

		Print(arr, n);
	}

	return 0;
}


/*
1의 자리에 대해 정렬
10의 자리에 대해 정렬 -> 2같은 경우 앞에 0을 붙여 02로 만들어 주고 비교함.
100의 자리에 대해 정렬
*/