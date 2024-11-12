#include <iostream>

using namespace std;

bool CheckSorted(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return false;
    }

    return true;
}

void Print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void fn_bubbleSort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool flag = true;
        // i번 실행하면서 이미 한 번 가장 큰 숫자를 뒤로 뺏으니 i 번을 더 반복할 필요 없다.
        for (int j = 0; j < size - 1 - i; j++)
        // for (int j = 0; j < size - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                flag = false;
            }
            Print(arr, size);
        }
        if (flag) break;
        cout << endl;
    }
}

int main()
{
    int arr[] = {5, 1, 4, 2, 8}; // 위키피디아 예시
    // int arr[] = { 5, 4, 3, 2, 1 }; // Worst Case
    // int arr[] = { 1, 2, 3, 5, 4 }; // Best Case
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "before\n";
    Print(arr, n);
    cout << endl;

    // Bubble Sort
    {
        // 힌트: Print()로 진행상황 확인하면서 구현
        // 힌트: 2중 for 루프
        // 힌트: for 루프 범위 주의
        fn_bubbleSort(arr, n);
    }

    cout << "after\n";
    Print(arr, n);
    cout << endl;
}