#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

struct Element
{
    int key;
    char value;
};

void Print(Element *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i].key << " ";
    cout << endl;

    for (int i = 0; i < size; i++)
        cout << arr[i].value << " ";
    cout << endl;
}

void Print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

bool checkSorted(int *arr, int size)
{
    // return `true` if order by asc, else `false`
    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = i; j < size; j++)
    //     {
    //         if (arr[i] > arr[j])
    //         {
    //             return false;
    //         }
    //     }
    // }

    // 이게 더 깔끔함
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }

    return true;
}

void fn_swap(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            int temp;
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void example1()
{
    // 3개 정렬
    for (int k = 0; k < 3; k++)
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < 3; i++)
            {
                int arr[3] = {i, j, k};
                int size = sizeof(arr) / sizeof(int);

                // before sorting
                for (int e = 0; e < size; e++)
                {
                    cout << arr[e] << " " << flush;
                }

                cout << " -> " << flush;

                // after order by asc
                // TODO:
                fn_swap(arr, size);

                for (int e = 0; e < size; e++)
                {
                    cout << arr[e] << " " << flush;
                }

                cout << boolalpha;
                cout << checkSorted(arr, size);
                cout << endl;
            }
}

void example2()
{
    // 5개라면? 더 많다면?
    {
        // 8 4 2 8 3
        // TODO: ???

        // 8 3 2 5 1 1 2 5 8 9
        // TODO: ???

        // 100개라면?
    }

    // 가장 작은 수 찾기
    {
        int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9}; // 임의의 숫자들, 변경 가능
        int size = sizeof(arr) / sizeof(arr[0]);

        // TODO:
        int min_number = arr[0];
        for (int i = 0; i < size; i++)
        {
            min_number = min_number > arr[i] ? arr[i] : min_number;
        }
        cout << "Minimum number is " << min_number << endl;
    }

    // 가장 작은 수의 인덱스 찾기
    {
        int arr[] = {7, 3, 4, 5, 3, 1, 2, 0, 8, 9};
        int size = sizeof(arr) / sizeof(arr[0]);

        // TODO:
        int min_index = 0;
        for (int i = 0; i < size; i++)
        {
            min_index = arr[min_index] > arr[i] ? i : min_index;
        }

        cout << "The index of min is " << min_index << endl;
        cout << "Minimum number is " << arr[min_index] << endl;
    }

    // Selection Sort
    {
        int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9};
        // int arr[] = {8, 3, 2, 5};
        int size = sizeof(arr) / sizeof(arr[0]);

        int min_index;
        for (int i = 0; i < size - 1; i++)
        {
            // TODO:
            min_index = i;
            for (int j = i + 1; j < size; j++)
            {
                min_index = (arr[j] < arr[min_index]) ? j : min_index;
            }
            std::swap(arr[i], arr[min_index]);

            Print(arr, size);

            cout << boolalpha;
            cout << checkSorted(arr, size);
            cout << endl;
        }
    }
}

void example3()
{
    // 비교 횟수 세보기, 더 효율적인 방법은 없을까?
    // https://en.wikipedia.org/wiki/Sorting_algorithm
    {
        ofstream ofile("log.txt");
        for (int size = 1; size < 1000; size++)
        {
            int count = 0;
            int *arr = new int[size];
            for (int s = 0; s < size; s++)
            {
                arr[s] = size - s;
            }

            // TODO: count ++;
            int min_index;
            for (int i = 0; i < size - 1; i++)
            {
                min_index = i;
                for (int j = i + 1; j < size; j++)
                {
                    count++;
                    min_index = (arr[j] < arr[min_index]) ? j : min_index;
                }
                std::swap(arr[i], arr[min_index]);
            }

            // cout << size << ", " << count << endl;
            ofile << size << ", " << count << endl;
            // Print(arr, size);

            delete[] arr;
        }

        ofile.close();
    }
}

void example4()
{
    // [2, 2, 1]
    // [1, 2, 2] // 첫 2가 마지막으로 이동

    // 안정성 확인(unstable)
    {
        Element arr[] = {{2, 'a'}, {2, 'b'}, {1, 'c'}};
        int size = sizeof(arr) / sizeof(arr[0]);

        cout << "before" << endl;
        Print(arr, size); // arr이 Element의 배열

        // TODO:
        int min_index;
        for (int i = 0; i < size - 1; i++)
        {
            min_index = i;
            for (int j = i + 1; j < size; j++)
            {
                min_index = (arr[j].key < arr[min_index].key) ? j : min_index;
            }
            std::swap(arr[i], arr[min_index]);
            cout << "loop" << endl;
            Print(arr, size); // key값은 정렬이 됐지만, value가 정렬이 되지 않은 상태는 unstable한 정렬임. 둘 다 정렬되어야 함.
        }
    }
}

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}