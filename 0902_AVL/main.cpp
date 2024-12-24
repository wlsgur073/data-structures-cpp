#include <iostream>

#include "../shared/AVL.h"

using namespace std;

int main()
{
	using Item = AVL<int, char>::Item;

	AVL<int, char> bst;

	for (int i : { 9, 8, 7, 6, 5, 4, 3, 2, 1 })
		//for (int i : { 1, 2, 3, 4, 5, 6, 7, 8, 9 })
	{
		bst.Insert(Item{ i, char('A' + i) });
		bst.Print2D();
	}

	// bst.Inorder(); // key에 대해 정렬

	// cout << bst.RecurGet(5)->value << endl;
	// cout << bst.RecurGet(3)->value << endl;
	// cout << bst.RecurGet(7)->value << endl;
	// cout << bst.RecurGet(1)->value << endl;
	// cout << bst.RecurGet(4)->value << endl;

	cout << "------------------------------------" << endl;
	for (int i : {5, 8, 9})
	{
		bst.Remove(i);
		bst.Print2D();
	}

	return 0;
}

/*
	트리의 왼쪽, 오른쪽의 균형이 맞지 않으면 좌우 트리의 높이를 비교한다.

	밸런스 = 왼쪽 서브트리의 높이 - 오른쪽 서브트리의 높이
	밸런스가 -1 이상 1이하이면 좋은 것으로 판단

	가시화 도구: https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

	1. LL -> Right Rotation
	왼쪽으로 노드가 치우쳐 있는 경우, 어떤 노드의 밸런스가 1보다 크고 왼쪽 자신 노드의 밸런스가 0이상.
	2. RR -> Left Rotation
	오른쪽으로 노드가 치우쳐 있는 경우, 어떤 노드의 밸런스가 -1보다 작고 오른쪽 자신 노드의 밸런스가 0이하.
	3. LR -> Left-Right Rotation
	어떤 노드의 밸런스가 1보다 크고, 왼쪽 자식 노드의 밸런스가 0보다 작을 경우.
	왼쪽 자식 노드에 대해 RotateLeft() 후에 RotateRight().
	4. RL -> Right-Left Rotation
	어떤 노드의 밸런스가 -1보다 작고, 오른쪽 자식 노드의 밸런스가 0보다 클 경우.
	오른쪽 자식 노드에 대해 RotateRight() 후에 RotateLeft().

	https://www.geeksforgeeks.org/introduction-to-avl-tree/
*/