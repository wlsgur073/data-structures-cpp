#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

/*
	농구할 때, 드리블하다가 공 잡으면 피벗 상태 되잖아.
	그거 떠올리면서 코드 작성하면 됨.

	1. 피벗을 정한다.
	2. 피벗을 기준으로 왼쪽은 작은 값, 오른쪽은 큰 값으로 정렬한다.
	3. 왼쪽과 오른쪽을 다시 정렬한다(반복).
	4. 교차를 하면 정렬이 끝난다.
	5. 다시 피벗을 정하고 반복한다.
*/

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}

// Hoare partition scheme
int Partition(int arr[], int low, int high, int n)
{
	int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
	int i = low - 1; // 왼쪽에서 오른쪽으로 이동
	int j = high + 1; // 오른쪽에서 왼쪽으로 이동

	while (true)
	{
		do
		{
			i++;
		} while (arr[i] < pivot);

		do
		{
			j--;
		} while (arr[j] > pivot);

		if (i >= j)
			return j;

		swap(arr[i], arr[j]);

		cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
		cout << "         ";
		Print(arr, low, high, n);
	}
}

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		int p = Partition(arr, low, high, n);

		QuickSort(arr, low, p, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}
