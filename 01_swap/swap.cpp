#include <iostream>

using namespace std;

int mySwapValue(int *a, int *b)
{
    // 귀찮음...
    return 0;
}

void mySwapPtr(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mySwapRef(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

bool checkSorted(int a, int b)
{
    return (a <= b);
}

int main()
{

    cout << "swap ===================================" << endl;
    // swap
    {
        int a = 3;
        int b = 2;

        cout << a << " " << b << endl;

        // code
        mySwapRef(a, b);

        cout << a << " " << b << endl;
    }

    cout << "order by asc ===================================" << endl;

    // order by asc
    {
        int arr[] = {9, 3};
        cout << arr[0] << " " << arr[1] << endl;

        if (arr[0] > arr[1])
        {
            mySwapRef(arr[0], arr[1]);
        }
        cout << arr[0] << " " << arr[1] << endl;
    }

    cout << "example 1 ===================================" << endl;

    // example 1
    {
        int ex1[] = {0, 1, 2, 3, 4};
        int arrLen = sizeof(ex1) / sizeof(int);

        for (int i = 0; i < arrLen; i++)
        {
            for (int j = 0; j < arrLen; j++)
            {
                cout << boolalpha;
                cout << ex1[j] << " " << ex1[i] << " " << checkSorted(ex1[j], ex1[i]) << endl;
            }
        }
        
    }

    cout << "example 2 ===================================" << endl;

    // example 2
    {
        int ex2[] = {0, 1, 2, 3, 4};
        int arrLen = sizeof(ex2) / sizeof(int);
        int tmp[2];

        int i = 0;
        while (i < arrLen)
        {
            for (int j = 0; j < arrLen; j++)
            {
                tmp[0] = i;
                tmp[1] = j;
                if (tmp[0] > tmp[1])
                {
                    swap(tmp[0], tmp[1]);
                }
                
                cout << boolalpha;
                cout << tmp[0] << " " << tmp[1] << " " << checkSorted(tmp[0], tmp[1]) << endl;
                
            }
            i++;
        }
    }

    return 0;
}