#include <iostream>

using namespace std;

int rec_count = 0;

int InterpolationSearch(int arr[], int low, int high, int x)
{
	rec_count++;

	if (low <= high && x >= arr[low] && x <= arr[high])
	{
		// int pos = (low + high) / 2; // 이진 탐색 (중간)

		int pos = low + (int)(((float)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));

		if (arr[pos] == x)
			return pos;

		if (arr[pos] < x)
			return InterpolationSearch(arr, pos + 1, high, x);

		if (arr[pos] > x)
			return InterpolationSearch(arr, low, pos - 1, x);
	}

	return -1;
}

// 인덱스가 증가를 하면 인덱스에 해당하는 값도 증가한다고 가정
// https://www.geeksforgeeks.org/interpolation-search/
int main()
{
	int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
	int n = sizeof(arr) / sizeof(arr[0]);

	for (auto x : { 10, 18, 33, 47, -1, 99 })
	{
		rec_count = 0;

		int index = InterpolationSearch(arr, 0, n - 1, x);

		if (index != -1)
			cout << x << " was found at index " << index << endl;
		else
			cout << x << " was not found." << endl;

		cout << "rec_count = " << rec_count << endl;
		cout << endl;
	}

	return 0;
}

// 보간 탐색 (Interpolation Search)
// 1. 이진 탐색과 유사하지만, 중간값을 찾을 때 중간값을 보간하여 찾는다.
// 2. 중간값을 찾을 때, 이진 탐색은 (low + high) / 2 로 찾는다.
// 3. 보간 탐색은 (low + (high - low) * (x - arr[low]) / (arr[high] - arr[low])) 로 찾는다.

// pos = low + (high - low ) / (arr[high] - arr[low]) * (x - arr[low])

/*
	1. 배열: [50, 51, 52, ..., 100] -> arr[low] = 50, arr[high] = 100
	2. 찾는 값: x = 60
	3. 값의 비율 계산: (60 - 50) / (100 - 50) = 0.2	->	대략 앞쪽 20% 지점에 위치한다.
	4. 인덱스 변환: pos = low + (high − low) * 0.2	->	0 + 99 * 0.2 = 19.8
	** 배열의 값이 고르게 분포되어 있을 때, 보간 탐색을 진행해야 한다. 아니면 정확도 떨어짐.
*/