#include "../shared/Queue.h"

#include <iostream>

using namespace std;

int main()
{
	int n = 7, k = 3; // set n and k to the desired values

	Queue<int> q(n + 1);
	q.SetDebugFlag(true);

	// 처음에 n명 추가 (1, 2, ..., n)
	for (int i = 1; i <= n; i++)
		q.Enqueue(i);
	q.Print();

	// 마지막 한 명이 남을 때까지 반복
	{
		while (q.Size() > 1)
		{
			// k 명은 맨 앞에서 뒤로 보내기
			for (int i = 0; i < k - 1; i++)
			{
				// 맨 앞에 있는 사람을 뒤로 보내기, 일종의 swap
				int temp = q.Front();
				q.Dequeue();
				q.Enqueue(temp);
			}

			q.Print();

			// 이제 k 번째가 인덱스 0이므로, 맨 앞에 있는 사람이 k 번째 사람
			cout << "Executed " << q.Front() << endl;
			q.Dequeue();

			q.Print();
		}
	}

	// 최후의 생존자 번호
	cout << "Survivor: " << q.Front() << endl;

	return 0;
}