#include <iostream>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int x)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == x)
			return i;
	}

	return -1;
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int n = sizeof(arr) / sizeof(arr[0]);

	int keys[] = { 1, 13, 55 };
	int kn = sizeof(keys) / sizeof(keys[0]);

	int indices[] = { 0, 3, 6, n }; // 마지막에 n 하나 더 추가

	for (int x : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		if (x < arr[0] || x > arr[n - 1])
			cout << x << " was not found" << endl;
		else
		{
			// while (x > arr[indices[i]]) // 단순히 배열 테이블을 순차적으로 검색

			// 인덱스 테이블에서 검색할 범위 결정
            int k = 0;
            while (k < kn - 1 && keys[k + 1] <= x)
                k++;

            // 색인 표의 범위에 따라서 선형 탐색
            // indices[k] 이상 indices[k+1] 미만에 대해 검색
            // 이때 indices 배열 마지막에 추가로 n을 저장해뒀기 때문에 k+1 사용 가능
            int found = SequentialSearch(arr, indices[k], indices[k + 1], x);
            if (found >= 0)
                cout << x << " was found at " << found << endl;
            else
                cout << x << " was not found" << endl;
		}
	}

	return 0;
}

/*
	색인(index) 순차 탐색
*/